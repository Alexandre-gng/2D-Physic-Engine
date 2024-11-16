#pragma once

#include "ClassJoint.h"

using namespace std;

class Particle;
class Constraint;

class Object {
public:
    vector<shared_ptr<Constraint>> constraints_list;

    bool moving;

    enum type {
        CLOTH,
        ROPE,
        RECTANGLE,
    };

    // Destructor
    virtual ~Object() = default;

    // Update the position of the object
    virtual void update() = 0;
};
