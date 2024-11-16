#pragma once

class Particle;

class Joint {
public:
    Particle* particle1;
    Particle* particle2;
    float distance;

    Joint(Particle* p1, Particle* p2): particle1(p1), particle2(p2) {
        sf::Vector2f delta_pos = p2->pos - p1->pos;
        p1->list_joints.push_back(this);
        p2->list_joints.push_back(this);
        distance = sqrt((delta_pos.x)*(delta_pos.x) + (delta_pos.y*delta_pos.y));
    };

    void apply();
};