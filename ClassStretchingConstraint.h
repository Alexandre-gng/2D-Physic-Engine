#pragma once

#include "ClassConstraint.h"

class StretchingConstraint : public Constraint {
public:
    int distance{};

     StretchingConstraint(int d, Object* ptr_o)
    : distance(d), Constraint(ptr_o){};

    void apply() override {
        for (const auto& row_particle: ptr_object->TABparticles) {
            for (const auto& ptr_p1: row_particle) {
                for (auto j: ptr_p1->list_joints) {
                    Particle *ptr_p2;
                    if (j->particle2 == ptr_p1) {
                        ptr_p2 = j->particle1;
                    } else {
                        ptr_p2 = j->particle2;
                    }
                    sf::Vector2f delta_pos = ptr_p2->pos - ptr_p1->pos;
                    float current_distance = sqrt(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y);

                    sf::Vector2f deltaP1 = (-(ptr_p2->inverse_mass) * (current_distance - j->distance) /
                                            ((ptr_p2->inverse_mass + ptr_p1->inverse_mass) * current_distance)) *
                                           delta_pos;
                    sf::Vector2f deltaP2 = ((ptr_p1->inverse_mass) * (current_distance - j->distance) /
                                            ((ptr_p2->inverse_mass + ptr_p1->inverse_mass) * current_distance)) *
                                           delta_pos;

                    if ((current_distance > 0) && (current_distance >= j->distance * 1.25f)) {
                        ptr_p1->cutTwoParticles(ptr_p2);
                        continue;
                    }

                    if (!ptr_p1->moving && ptr_p2->moving) {
                        ptr_p2->pos += deltaP1 * 2.0f;
                    }
                    if (ptr_p1->moving && !ptr_p2->moving) {
                        ptr_p1->pos += deltaP2 * 2.0f;
                    }
                    if (ptr_p1->moving && ptr_p2->moving) {
                        ptr_p1->pos += deltaP2;
                        ptr_p2->pos += deltaP1;
                    }
                }
            }
        }
    }
};

