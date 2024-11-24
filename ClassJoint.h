#pragma once

#include "Common.h"

class Particle;

class Joint {
public:
    Joint();
    Joint(Particle* p1, Particle* p2);
    Particle* particle1;
    Particle* particle2;
    float distance;

    void deleteJoint() {

    }
};