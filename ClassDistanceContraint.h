//
// Created by alexa on 11/11/2024.
//

#ifndef CLOTHES_CLASSDISTANCECONTRAINT_H
#define CLOTHES_CLASSDISTANCECONTRAINT_H

#include "ClassConstraint.h"
#include "ClassParticle.h"

class DistanceConstraint : public Constraint {
    int distance;
    Particle* p1;
    Particle* p2;

    void apply() override {
        float w1 = 1 / p2->mass;
        float w2 = 1 / p1->mass;

        sf::Vector2f delta_pos = p2->pos - p1->pos;
        float current_distance = sqrt(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y);

        sf::Vector2f deltaP1 =
                (-(w1) * (current_distance - this->distance) / ((w1 + w2) * current_distance)) * delta_pos;
        sf::Vector2f deltaP2 =
                ((w2) * (current_distance - this->distance) / ((w1 + w2) * current_distance)) * delta_pos;

        if ((current_distance > 0) && (current_distance >= this->distance * 1.25f)) {
            p1->cutTwoParticles(p2);
        }

        if (!p1->moving && p2->moving) {
            p2->pos += deltaP1 * 2.0f;
        }
        if (p1->moving && !p2->moving) {
            p1->pos += deltaP2 * 2.0f;
        }
        if (p1->moving && p2->moving) {
            p1->pos += deltaP2;
            p2->pos += deltaP1;
        }
    }
};


#endif //CLOTHES_CLASSDISTANCECONTRAINT_H
