#ifndef CLOTHES_CLASSOBJECT_H
#define CLOTHES_CLASSOBJECT_H

#include "ClassParticle.h"
#include "ClassConstraint.h"

using namespace std;

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


#endif //CLOTHES_CLASSOBJECT_H
