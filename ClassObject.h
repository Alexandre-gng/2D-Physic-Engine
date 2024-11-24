/*
 * Object comporte une liste de ptr Particle,
 */

#pragma once

using namespace std;

class Joint;
class Particle;
class Constraint;

class Object {
public:
    enum type {
        CLOTH,
        ROPE,
        RECTANGLE,
    };
    type                            object_type;
    bool                            moving;

    vector<vector<Particle*>>                 TABparticles;
    vector<vector<Triangle*>>                 TABtriangles;
    vector<shared_ptr<Constraint>>            constraints_list;


    Object() = default;
    Object(type t, int h_P, int w_P, int h_T, int w_T) : object_type(t) {
        TABparticles.resize(h_P, std::vector<Particle*>(w_P, nullptr));
        TABtriangles.resize(h_T, std::vector<Triangle*>(w_T, nullptr));
    }


    // Destructor
    virtual ~Object() = default;

    // Update the position of the object
    virtual void update() = 0;
};
