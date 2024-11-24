#pragma once

#include "ClassConstraint.h"

class Object;

class StretchingConstraint : public Constraint {
public:
    int distance{};

    void apply() override;

     StretchingConstraint(int d, Object* ptr_o)
    : distance(d), Constraint(ptr_o){};
};

