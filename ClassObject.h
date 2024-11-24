#pragma once


#include "Common.h"
#include "ClassJoint.h"
#include "ClassTriangle.h"
#include "ClassConstraint.h"
#include "ClassStretchingConstraint.h"


class Triangle;
class Constraint;

using namespace std;

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
