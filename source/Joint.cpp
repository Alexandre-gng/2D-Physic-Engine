#include "../include/ClassJoint.hpp"
#include "../include/ClassParticle.hpp"
// Fix the error in the constructor

Joint::Joint(Particle* ptr_P1, Particle* ptr_P2): particle1(ptr_P1), particle2(ptr_P2) {
    sf::Vector2f delta_pos = ptr_P2->pos - ptr_P1->pos;
    ptr_P1->list_joints.push_back(this);
    ptr_P2->list_joints.push_back(this);
    distance = sqrt((delta_pos.x)*(delta_pos.x) + (delta_pos.y*delta_pos.y));
};
