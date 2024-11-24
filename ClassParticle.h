#pragma once

#include "Common.h"
#include "ClassJoint.h"

using namespace std;

class Object;
class Triangle;

class Particle {
public:
    bool              moving       = true;
    float             mass         = 1.0f;
    float             inverse_mass = 1 /mass;
    float             friction;
    unsigned int      id;
    sf::Vector2f      pos;
    sf::Vector2f      prev_pos;
    sf::Vector2f      forces;
    sf::Vector2f      velocity;
    vector<Joint*>    list_joints;
    vector<Triangle*> list_triangles_friends;

    Object* ptr_Object;

    // To modify YYY
    sf::CircleShape shape;


    void applyFriction() {
        forces -= velocity * friction;
    }
    void applyGravity(float grav) {
        if (moving) {
            forces.y += mass * grav;
        }
    }

    void updateVelocity(float dt) {
        this->velocity = (pos - prev_pos) / dt;
    }


    void cutTwoParticles(Particle* Pa) {
        for (const auto j: this->list_joints) {
            if ((j->particle2 == Pa || j->particle1 == Pa) && (j->particle2 == this || j->particle1 == this)) {
                j->deleteJoint();
            }
        }
    }

    Particle(float x, float y, float m) : pos(sf::Vector2f {x,y}), prev_pos(sf::Vector2f {x,y}), mass(m), inverse_mass(1/m) {
        // SFML Shape creation
        sf::CircleShape ParticleShape(2.f);
        ParticleShape.setFillColor(sf::Color(255, 255, 255));
        this->shape = ParticleShape;
    }
    Particle(float xprev, float yprev, float x, float y) {
        this->pos = {x, y};
        this->prev_pos = {x, y};
    }
};