#pragma once

using namespace std;

class Joint;
class Particle;
class Constraint;

/*
 * Trouver une manière adapté de traiter les contraintes une à une
 *      => Tansfèrer les TABParticles, Liste_Joints et list Particle dans Object
 *              => plus logique vu que tous les objets quasiment auront ses données
 *      => mettre Gravity dans PhysicClass
 *      et ça devrait être bon
 *
 */

class Object {
public:
    vector<shared_ptr<Constraint>>  constraints_list;
    Particle*                       TABparticles[40][40];
    Triangle*                       TABtriangles[40][80];

    bool moving;

    enum type {
        CLOTH,
        ROPE,
        RECTANGLE,
    };
    type object_type;

    Object() = default;
    Object(type t) : object_type(t){}

    // Destructor
    virtual ~Object() = default;

    // Update the position of the object
    virtual void update() = 0;
};
