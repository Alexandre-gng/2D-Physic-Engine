#ifndef CLOTHES_CLASSCONSTRAINT_H
#define CLOTHES_CLASSCONSTRAINT_H

#include "ClassParticle.h"

class Constraint {
public:
    virtual ~Constraint() = default;

    virtual void apply() = 0;
};

#endif //CLOTHES_CLASSCONSTRAINT_H
