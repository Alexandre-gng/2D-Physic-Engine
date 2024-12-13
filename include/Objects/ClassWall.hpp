#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "SFML/Graphics.hpp"
#include "ClassObject.hpp"
#include "../ClassParticle.hpp"
#include "../ClassJoint.hpp"

class Wall : public Object {
public:
    int a;
};