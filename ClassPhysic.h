#pragma once

#include "ClassParticle.h"
#include "ClassObject.h"

using namespace std;

/*
 * collision_detection:
 *      Hashmap: si particule à côté:
 *          Ajouter les contraintes aux particules concernées
 *
 * solving_constraints():
 *      Pour tous les objets:
 *          Pour toutes les contraintes:
 *              Pour tous les Triangles de l'objets:
 *                  Constraint->apply();
 */
class Physic {
public:
    float gravity;

    vector<Object*> objects_list;

    void solving_constraints();

    // Position base dynamic method
    void PBD(float dt, float k_damping, int constraints_iter, Object* ptr_o);
    // Reduce the velocity to keep only the global movement
    static void damping_velocities(float k_damping, Object* ptr_O);

    Physic(vector<Object*> vec, float g): objects_list(vec), gravity(g) {}
};

