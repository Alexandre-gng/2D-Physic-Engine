#pragma once

#include "ClassParticle.h"

class Constraint {
public:
    Object* ptr_object{};

    explicit Constraint(Object* obj) : ptr_object(obj) {};

    virtual ~Constraint() = default;

    virtual void apply() = 0;
};

