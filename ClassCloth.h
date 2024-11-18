#pragma once

#include "ClassParticle.h"
#include "ClassObject.h"
#include "ClassTriangle.h"
#include "ClassConstraint.h"
#include "ClassStretchingConstraint.h"

using Eigen::MatrixXd;
/*
 * Contraintes:
 *      => Strecthing OK
 *      => Bending TO_DO
 *      => Self_collision
 *      => With rigid body
 *      => External and pressurized forces ?
 *
 * SUPRESSION 1 PARTICLE (ptr_p)
 *      // Pour tous les triangles que constitue ptr_p (Z1):
 *      for (Triangle ptr_t : ptr_p->list_triangles_friends) {
 *          // Pour tous les triangles de Z2:
 *          for (Triangle t_voisin: ptr_t->list_nearest_triangles) {
 *              if (t_voisin != nullptr) {
 *                  if (t_voisin == ptr_t) {
 *                      TYPE *var = t_voisin->list_nearest_triangles // ASSIGNER PTR POUR MODIFIER
 *                      var = nullptr
 *                  }
 *              }
 *          }
 *      }
 *
 *      // Pour tous les Joints qui contiennent ptr_p :
 *      //          Surtout une étape afin d'éviter les fuites de mémoire
 *     for (Joint ptr_j : ptr_p->list_joints) {
 *          delete ptr_j;
 *     }
 *
 *     // Supprimer les triangles liés à la ptr_p dans Cloth->list_triangles
 *     for (Triangle ptr_t: Cloth->list_triangles) {
 *          for (Triangle ptr_t2: ptr_p->list_triangles_friends) {
 *              if (ptr_t == ptr_t2) {
 *                  // SUPPRESSION PAR PTR A FAIRE
 *                  ptr_t = nullptr
 *              }
 *          }
 *     }
 *
 *     // Suprimer le ptr_p dans Cloth->TABparticles
 *     for (int i = 0; i < this->height; i++) {
 *          for (int j = 0; j < this->width; j++) {
 *              if (ptr_p == Cloth->TABparticles[i][j]) {
 *                  // SUPPRESSION PAR PTR A FAIRE
 *                  Cloth->TABparticles[i][j] = nullptr;
 *              }
 *          }
 *      }
 *
 *      delete la prticle
 */
class Cloth : public Object {
public:
    int          width;
    int          height;
    int          default_lenght;
    int          mass_particles;
    unsigned int number_p;

    void updateAllAccelerations();
    void simulateVerlet(float);
    void JakobsenMethod();



    void update() override {
        cout << "heheh "<< endl;
    }

    // REFAIRE AVEC L'ALGO YYY
    void suppParticle(sf::Vector2f);

    // TO_SUPP AND MOVE YYY
    // PBD constraint solver of the distance between particles
    void PBD_distance_constraint();
    // Constraint solver of the collision solid/ Cloth
    void solid_collision_constraint();


    Cloth(int x, int y, int w, int h, float d,int m_p, float frict)
    : width(w), height(h), default_lenght(d), mass_particles(m_p), number_p(w*h), Object(CLOTH) {

        // Adding the Stretching constraint
        constraints_list.push_back(std::make_shared<StretchingConstraint>(default_lenght, this));

        // Create all of the Particle in the Cloth_TAB
        sf::Vector2f last_pos = {float(x), float(y)};
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                if (i != 0) {
                    last_pos = this->TABparticles[i - 1][j]->pos;
                } else {
                    last_pos = {float(x + i*default_lenght), float(y)};
                }
                Particle *ptr_NewP;
                if (j%2 == 0) {
                    if (i == h-1) {
                        ptr_NewP = new Particle(last_pos.x + default_lenght - default_lenght/2, y + j * (default_lenght * sqrt(3) / 2), 5.f);
                        last_pos = ptr_NewP->pos;
                    } else {
                        ptr_NewP = new Particle(last_pos.x + default_lenght, y + j * (default_lenght * sqrt(3) / 2), 5.f);
                        last_pos = ptr_NewP->pos;
                    }
                } else {
                    if (i == 1) {
                        ptr_NewP = new Particle(last_pos.x + default_lenght - default_lenght/2, y + j * (default_lenght * sqrt(3) / 2), 5.f);
                        last_pos = ptr_NewP->pos;
                    } else {
                        ptr_NewP = new Particle(last_pos.x + default_lenght, y + j * (default_lenght * sqrt(3) / 2), 5.f);
                        last_pos = ptr_NewP->pos;
                    }
                }
                ptr_NewP->prev_pos = ptr_NewP->pos;
                TABparticles[i][j] = ptr_NewP;
                ptr_NewP->friction = frict;
                if (j == 0) {
                    ptr_NewP->moving = false;
                } else {
                    ptr_NewP->moving = true;
                }
            }
        }

        // Create Joint in Cloth
        Joint *ptr_NewJoint1, *ptr_NewJoint2, *ptr_NewJoint3, *ptr_exception;
        for (int i = 0; i < h-1; i++) {
            for (int j = 0; j < w-1; j++) {
                Particle *ptr_P = TABparticles[i][j];
                if (j % 2 == 0) {
                    ptr_NewJoint1 = new Joint(TABparticles[i][j], TABparticles[i+1][j]);
                    ptr_NewJoint2 = new Joint(TABparticles[i][j], TABparticles[i+1][j+1]);
                    ptr_NewJoint3 = new Joint(TABparticles[i][j], TABparticles[i][j+1]);
                    if (j == w-2) {
                        ptr_exception = new Joint(TABparticles[i][j+1], TABparticles[i+1][j+1]);
                    }
                } else {
                    ptr_NewJoint1 = new Joint(TABparticles[i][j], TABparticles[i+1][j]);
                    ptr_NewJoint2 = new Joint(TABparticles[i+1][j], TABparticles[i][j+1]);
                    ptr_NewJoint3 = new Joint(TABparticles[i][j], TABparticles[i][j+1]);
                    if (i == h-2) {
                        ptr_exception = new Joint(TABparticles[i+1][j], TABparticles[i+1][j+1]);
                    }
                }
            }
        }
        // Create Triangle with Joint in Cloth
        int h_number_triangle=0;
        int w_number_triangle=0;
        for (int i = 0; i < h-1; i++) {
            for (int j = 0; j < w-1; j++) {
                Joint *AB, *BD, *AC, *CD, *AD, *BC;
                /*         AB
                 *      A ---- B
                 *  AC  | \AD  |  BD
                 *      |   \  |
                 *      C ---- D
                 *         CD
                 */
                if (j % 2 == 0) {
                    for (auto joint: TABparticles[i][j]->list_joints) {
                        if ((joint->particle1 == TABparticles[i+1][j] || joint->particle2 == TABparticles[i+1][j])
                        && (joint->particle1 == TABparticles[i][j] || joint->particle2 == TABparticles[i][j])) {
                            AB = joint;
                        }
                        if ((joint->particle1 == TABparticles[i+1][j+1] || joint->particle2 == TABparticles[i+1][j+1])
                        && (joint->particle1 == TABparticles[i][j] || joint->particle2 == TABparticles[i][j])) {
                            AD = joint;
                        }
                        if ((joint->particle1 == TABparticles[i][j+1] || joint->particle2 == TABparticles[i][j+1])
                        && (joint->particle1 == TABparticles[i][j] || joint->particle2 == TABparticles[i][j])) {
                            AC = joint;
                        }
                    }
                    for (auto joint: TABparticles[i+1][j+1]->list_joints) {
                        if ((joint->particle1 == TABparticles[i + 1][j] || joint->particle2 == TABparticles[i + 1][j])
                        && (joint->particle1 == TABparticles[i + 1][j + 1] || joint->particle2 == TABparticles[i + 1][j + 1])) {
                            CD = joint;
                        }
                        if ((joint->particle1 == TABparticles[i][j + 1] || joint->particle2 == TABparticles[i][j + 1])
                            && (joint->particle1 == TABparticles[i + 1][j + 1] || joint->particle2 == TABparticles[i + 1][j + 1])) {
                            BD = joint;
                        }
                    }
                    Triangle* ptr_NewT1 = new Triangle(AB, AD, BD);
                    Triangle* ptr_NewT2 = new Triangle(AC, AD, CD);
                    w_number_triangle += 2;
                    this->TABtriangles[i][j*2] = ptr_NewT1;
                    this->TABtriangles[i][j*2+1] = ptr_NewT2;
                }
                 /*        AB
                 *      A ---- B
                 *  AC  |  BC/ |  BD
                 *      |  /   |
                 *      C ---- D
                 *         CD
                 */
                else {
                    for (auto joint: TABparticles[i+1][j]->list_joints) {
                        if ((joint->particle1 == TABparticles[i+1][j] || joint->particle2 == TABparticles[i+1][j])
                            && (joint->particle1 == TABparticles[i][j] || joint->particle2 == TABparticles[i][j])) {
                            AB = joint;
                        }
                        if ((joint->particle1 == TABparticles[i+1][j] || joint->particle2 == TABparticles[i+1][j])
                            && (joint->particle1 == TABparticles[i+1][j+1] || joint->particle2 == TABparticles[i+1][j+1])) {
                            BD = joint;
                        }
                        // YYY Problem: BC is NULL because condition never true
                        if ((joint->particle1 == TABparticles[i+1][j] || joint->particle2 == TABparticles[i+1][j])
                            && (joint->particle1 == TABparticles[i][j+1] || joint->particle2 == TABparticles[i][j+1])) {
                            BC = joint;
                        }
                    }
                    for (auto joint: TABparticles[i][j+1]->list_joints) {
                        if ((joint->particle1 == TABparticles[i][j+1] || joint->particle2 == TABparticles[i][j+1])
                            && (joint->particle1 == TABparticles[i + 1][j + 1] || joint->particle2 == TABparticles[i + 1][j + 1])) {
                            CD = joint;
                        }
                        if ((joint->particle1 == TABparticles[i][j + 1] || joint->particle2 == TABparticles[i][j + 1])
                            && (joint->particle1 == TABparticles[i][j] || joint->particle2 == TABparticles[i][j])) {
                            AC = joint;
                        }
                    }
                    Triangle* ptr_NewT1 = new Triangle(AB, BC, AC);
                    Triangle* ptr_NewT2 = new Triangle(BD, CD, BC);
                    w_number_triangle += 2;
                    this->TABtriangles[i][j*2] = ptr_NewT1;
                    this->TABtriangles[i][j*2+1] = ptr_NewT2;
                }
            }
        }
        // Assign each Triangle its neighbours
        for (int j = 0; j < (w-1)*2-1; j++) {
            for (int i = 0; i < h-1; i++) {
                Triangle *ptr_T = TABtriangles[i][j];
                if (j != 0) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i][j-1]);
                } if (j != w*2-1) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i][j+1]);
                }
                if (j%4==0 && j != w*2-1 && i != h-1) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i+1][j+1]);
                }if (j%4==1 && j != 0 && i != 0) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i-1][j-1]);
                }if (j%4==2 && j != w*2-1 && i != 0) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i-1][j+1]);
                }if (j%4==3 && j != 0 && i != h-1) {
                    ptr_T->list_nearest_triangles.push_back(TABtriangles[i+1][j-1]);
                }
            }
        }
    };
};
