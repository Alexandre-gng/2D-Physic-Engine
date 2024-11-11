#ifndef CLOTHES_CLASSCLOTH_H
#define CLOTHES_CLASSCLOTH_H

#include "ClassParticle.h"

using Eigen::MatrixXd;

class Cloth {
public:
    int         width;
    int         height;
    int         distance;
    unsigned int number_p;
    float       gravity;
    Particle*   TABparticles[40][40];

    void updateAllAccelerations();
    void simulateVerlet(float);
    void JakobsenMethod();

    // PBD constraint solver of the distance between particles
    void PBD_distance_constraint();
    // Constraint solver of the collision solid/ Cloth
    void solid_collision_constraint();

    void suppParticle(sf::Vector2f);

    // Damping managment
    void damping_velocities(float k_damping) {
        sf::Vector2f x_center = {0.f, 0.f};
        sf::Vector2f v_center = {0.f, 0.f};
        float total_mass = 0.f;

        // Center of mass and velocity
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                total_mass += ptrP->mass;
                x_center += ptrP->pos * ptrP->mass;
                v_center += ptrP->velocity * ptrP->mass;
            }
        }
        x_center = x_center * (1 / total_mass);
        v_center = v_center * (1 / total_mass);

        // Angular movement
        float L = 0.f;
        // Inertia tensor
        Eigen::Matrix2f I;
        I << 0, 0,
             0, 0;
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                float r_x = ptrP->pos.x - x_center.x;
                float r_y = ptrP->pos.y - x_center.y;
                //float r_z = ptrP->pos.z - x_center.z;

                // r~ * r~T:
                Eigen::Matrix2f r_result;
                r_result << r_x*r_x, 0,
                     0,  r_x*r_x;
                I = I + r_result * ptrP->mass;

                // cross product calcul and angular moment
                float r_x_v = ((r_x * ptrP->velocity.y) - (r_y - ptrP->velocity.x));
                L += r_x_v * ptrP->mass;
            }
        }
        Eigen::Matrix2f I_inverse;
        I_inverse = I.inverse();

        // angluar velocity
        Eigen::Matrix2f w;
        w = I_inverse * L;

        Eigen::Vector2f delta_velocity;
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr || j == 0) {
                    continue;
                }
                Eigen::Vector2f r(ptrP->pos.x - x_center.x, ptrP->pos.y - x_center.y);
                Eigen::Vector2f v_center_eigen(v_center.x, v_center.y);
                Eigen::Vector2f velocity_eigen(ptrP->velocity.x, ptrP->velocity.y);
                delta_velocity = v_center_eigen + w * r - velocity_eigen;
                ptrP->velocity = ptrP->velocity + k_damping * sf::Vector2f(delta_velocity.x(), delta_velocity.y());
            }
        }
    }

    // Position base dynamic
    void PBD(float dt, float k_damping, int constraints_iter) {
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                ptrP->forces = {0.f, 0.f};
                ptrP->applyGravity(this->gravity);
                ptrP->applyFriction();
                ptrP->velocity = ptrP->velocity + ptrP->forces * (1 / ptrP->mass) * dt;
            }
        }
        //damping_velocities(k_damping);
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                ptrP->pos = ptrP->prev_pos + dt * ptrP->velocity;
            }
        }
        // Constraints detections (collisions...)
        /* In the rope context the only constraint is a distance one so no specific detection
        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
            }
        }
        */

        // Solving constraints
        for (int i = 0; i < constraints_iter; i++) {
            this->PBD_distance_constraint();
        }

        for (int i = 0; i < this->height; i++) {
            for (int j = 0; j < this->width; j++) {
                Particle *ptrP = this->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                ptrP->velocity = (ptrP->pos - ptrP->prev_pos) / dt;
                ptrP->prev_pos = ptrP->pos;
            }
        }
    }

    Cloth(int x, int y, int w, int h, float d, float grav, float frict): width(w), height(h), distance(d), gravity(grav) {
        int id = 0;
        number_p = w * h;
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                id++;
                Particle* ptrNewP = new Particle(i*distance + x, j*distance + y, 5.f);
                // CReating initial velocity
                ptrNewP->prev_pos = ptrNewP->pos - sf::Vector2f {0.f, 0.f};
                TABparticles[i][j] = ptrNewP;
                ptrNewP->friction = frict;
                ptrNewP->id = id;
                if (j == 0) {
                    ptrNewP->moving = false;
                } else {
                    ptrNewP->moving = true;
                }
            }
        }

        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                Particle* ptrP = TABparticles[i][j];
                if (i != 0) {
                    ptrP->nearestParticles.push_back(TABparticles[i-1][j]);
                    //ptrP->nearParticle
                } if (i != h-1) {
                    ptrP->nearestParticles.push_back(TABparticles[i+1][j]);
                } if (j != 0) {
                    ptrP->nearestParticles.push_back(TABparticles[i][j-1]);
                } if (j != w-1) {
                    ptrP->nearestParticles.push_back(TABparticles[i][j+1]);
                }
            }
        }
    }
};

#endif //CLOTHES_CLASSCLOTH_H