#pragma once

#include "ClassParticle.h"

class Constraint {
public:
    virtual ~Constraint() = default;

    virtual void apply() = 0;
};

