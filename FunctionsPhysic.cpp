#include "ClassPhysic.h"

// Position Based Dynamic algorithm
void Physic::PBD(float dt, float k_damping, int constraints_iter) {
    int i = 0, j = 0;
    for (const auto ptr_O: this->objects_list) {
        for (const auto &row_p: ptr_O->TABparticles) {
            i++;
            j = 0;
            for (const auto &ptr_P: row_p) {
                j++;
                if (ptr_P == nullptr) {continue;}
                ptr_P->forces = {0.f, 0.f};
                ptr_P->applyGravity(this->gravity);
                ptr_P->applyFriction();
                ptr_P->velocity = ptr_P->velocity + ptr_P->forces * (1 / ptr_P->mass) * dt;
            }
        }
        cout << "eh" << endl;
        damping_velocities(k_damping, ptr_O);
        cout << "eh2" << endl;
        for (const auto &row_p: ptr_O->TABparticles) {
            for (const auto &ptr_P: row_p) {
                ptr_P->pos = ptr_P->prev_pos + dt * ptr_P->velocity;
            }
        }

        // Constraints detections (collisions...) YYY
        // HASH MAP OR BARNES-HUT ?

        // Solving constraints
        for (int i = 0; i < constraints_iter; i++) {
            for (const auto &constraint: ptr_O->constraints_list) {
                constraint->apply();
            }
        }

        for (const auto &row_p: ptr_O->TABparticles) {
            for (const auto &ptr_P: row_p) {
                ptr_P->velocity = (ptr_P->pos - ptr_P->prev_pos) / dt;
                ptr_P->prev_pos = ptr_P->pos;
            }
        }
    }
}


// Damping velocities to reduce energy accumulation
void Physic::damping_velocities(float k_damping, Object* ptr_O) {
    sf::Vector2f x_center = {0.f, 0.f};
    sf::Vector2f v_center = {0.f, 0.f};
    float total_mass = 0.f;
    cout << "eh1" << endl;
    // Center of mass and velocity
    for (int i = 0; i < ptr_O->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (ptr_P == this->TABparticles[i][j]) {
                this->TABparticles[i][j] = nullptr;
            }
        }
    }
    for (const auto& row_p: ptr_O->TABparticles) {
        for (const auto &ptr_P: row_p) {
            total_mass += ptr_P->mass;
            x_center += ptr_P->pos * ptr_P->mass;
            v_center += ptr_P->velocity * ptr_P->mass;
        }
    }
    x_center = x_center * (1 / total_mass);
    v_center = v_center * (1 / total_mass);
    cout << "eh3" << endl;
    // Angular movement
    float L = 0.f;
    // Inertia tensor
    Eigen::Matrix2f I;
    I << 0, 0,
            0, 0;
    for (const auto& row_p: ptr_O->TABparticles) {
        for (const auto& ptr_P: row_p) {
            float r_x = ptr_P->pos.x - x_center.x;
            float r_y = ptr_P->pos.y - x_center.y;
            //float r_z = ptrP->pos.z - x_center.z;

            // r~ * r~T:
            Eigen::Matrix2f r_result;
            r_result << r_x*r_x, 0,
                    0,  r_x*r_x;
            I = I + r_result * ptr_P->mass;

            // cross product and angular moment
            float r_x_v = ((r_x * ptr_P->velocity.y) - (r_y - ptr_P->velocity.x));
            L += r_x_v * ptr_P->mass;
        }
    }
    Eigen::Matrix2f I_inverse;
    I_inverse = I.inverse();
    cout << "eh4" << endl;
    // angluar velocity
    Eigen::Matrix2f w;
    w = I_inverse * L;

    Eigen::Vector2f delta_velocity;
    for (const auto& row_p: ptr_O->TABparticles) {
        for (const auto& ptr_P: row_p) {
            Eigen::Vector2f r(ptr_P->pos.x - x_center.x, ptr_P->pos.y - x_center.y);
            Eigen::Vector2f v_center_eigen(v_center.x, v_center.y);
            Eigen::Vector2f velocity_eigen(ptr_P->velocity.x, ptr_P->velocity.y);
            delta_velocity = v_center_eigen + w * r - velocity_eigen;
            ptr_P->velocity = ptr_P->velocity + k_damping * sf::Vector2f(delta_velocity.x(), delta_velocity.y());
        }
    }
}