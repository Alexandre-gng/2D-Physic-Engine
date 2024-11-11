#include "ClassCloth.h"

void Cloth::updateAllAccelerations() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            Particle* ptrP = this->TABparticles[i][j];
            if (ptrP != nullptr) {
                ptrP->updateAcceleration(this->gravity);
            }
        }
        return;
    }
}

// Verlet integration, good but not polyvalent
void Cloth::simulateVerlet(float dt) {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            Particle *ptrP = this->TABparticles[i][j];
            if (ptrP != nullptr) {
                ptrP->updateAcceleration(gravity);
                ptrP->velocity = ptrP->velocity + ptrP->acc*dt;
                ptrP->prev_pos = ptrP->pos;
                ptrP->pos = ptrP->pos + ptrP->velocity*dt;
            }
        }
    }
    return;
}

// Classic Jakobsen method
void Cloth::JakobsenMethod() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            Particle* ptrP = this->TABparticles[i][j];
            if (ptrP != nullptr) {
                for (auto nearestP: ptrP->nearestParticles) {
                    if (nearestP != nullptr) {
                        sf::Vector2f delta_pos = nearestP->pos - ptrP->pos;

                        float current_distance = sqrt(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y);

                        sf::Vector2f direction = delta_pos / current_distance;

                        float deltaDistance = current_distance - this->distance;

                        if ((deltaDistance > 0) && (deltaDistance >= this->distance*0.75)) {
                            ptrP->cutTwoParticles(nearestP);
                            continue;
                        }

                        sf::Vector2f correction = direction * (deltaDistance / 2.0f);

                        if (!ptrP->moving && nearestP->moving) {
                            nearestP->pos -= correction * 2.0f;
                        }
                        if (ptrP->moving && !nearestP->moving) {
                            ptrP->pos += correction * 2.0f;
                        }
                        if (ptrP->moving && nearestP->moving) {
                            ptrP->pos += correction;
                            nearestP->pos -= correction;
                        }
                    }
                }
            }
        }
    }
    return;
}

// PBD distance constraint solver
void Cloth::PBD_distance_constraint() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            Particle *p1 = this->TABparticles[i][j];
            if (p1 != nullptr) {
                for (auto p2: p1->nearestParticles) {
                    if (p2 == nullptr) {
                        continue;
                    }
                    float w1 = 1/p2->mass;
                    float w2 = 1/p1->mass;

                    sf::Vector2f delta_pos = p2->pos - p1->pos;
                    float current_distance = sqrt(delta_pos.x * delta_pos.x + delta_pos.y * delta_pos.y);

                    sf::Vector2f deltaP1 = (-(w1) * (current_distance - this->distance) / ((w1 + w2) * current_distance)) * delta_pos;
                    sf::Vector2f deltaP2 = ((w2) * (current_distance - this->distance) / ((w1 + w2) * current_distance)) * delta_pos;

                    if ((current_distance > 0) && (current_distance >= this->distance*1.25f)) {
                        p1->cutTwoParticles(p2);
                        continue;
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
            }
        }
    }
    return;
}


// PBD distance constraint solver
void Cloth::solid_collision_constraint() {
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            Particle *p1 = this->TABparticles[i][j];
            if (p1 == nullptr) {
                continue;
            }
            //if (p1->pos.y > )
        }
    }
    return;
}

void Cloth::suppParticle(sf::Vector2f mousePos) {
    bool stop = false;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (stop) break;
            Particle* ptrP = this->TABparticles[i][j];
            if (ptrP != nullptr) {
                if ((mousePos.x + 5.0 > ptrP->pos.x) && (mousePos.x - 5.0 < ptrP->pos.x)) {
                    if ((mousePos.y + 5.0 > ptrP->pos.y) && (mousePos.y - 5.0 < ptrP->pos.y)) {

                        for (auto pNearest: this->TABparticles[i][j]->nearestParticles) {
                            if (pNearest == nullptr) continue;
                            for (auto &p: pNearest->nearestParticles) {
                                Particle** ptrp = &p;
                                if (p == ptrP) {
                                    p = nullptr;
                                }
                            }
                        }
                        this->TABparticles[i][j]= nullptr;
                        stop = true;
                        break;
                    }
                }
            }
        }
    }
}
