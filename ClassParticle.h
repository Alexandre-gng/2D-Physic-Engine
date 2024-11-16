#pragma once

#include <vector>
#include <math.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Vector2.hpp>

#include "include/Eigen/Eigen"

using namespace std;

class Triangle;
class Joint;
class Object;

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
    vector<Particle*> nearestParticles;
    sf::CircleShape shape;


    void applyFriction() {
        forces -= velocity * friction;
    }
    void applyGravity(float grav) {
        if (moving) {
            forces.y += mass * grav;
        }
    }
    /*
    void updateAcceleration(float grav) {
        forces = {0.f, 0.f};
        applyGravity(grav);
        applyFriction();
        acc = (forces * inverse_mass);
    }
     */
    void updateVelocity(float dt) {
        this->velocity = (pos - prev_pos) / dt;
    }
    void update(float dt) {
    }

    void cutTwoParticles(Particle* Pa) {
        for (auto &PaNearest: Pa->nearestParticles) {
            if (PaNearest == this) {
                PaNearest = nullptr;
            }
        }
        for (auto &PbNearest: this->nearestParticles) {
            if (PbNearest == Pa) {
                PbNearest = nullptr;
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

