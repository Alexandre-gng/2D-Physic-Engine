#ifndef CLOTHES_CLASSPARTICLE_H
#define CLOTHES_CLASSPARTICLE_H

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

class Particle {
public:
    bool         moving      = true;
    int          id;
    float        friction;
    float        mass        = 1.0f;
    sf::Vector2f pos;
    sf::Vector2f prev_pos;
    sf::Vector2f forces;
    sf::Vector2f velocity;
    sf::Vector2f acc;

    // To modify ?
    std::vector<Particle*> nearestParticles;
    sf::CircleShape shape;


    void applyFriction() {
        forces -= velocity * friction;
    }
    void applyGravity(float grav) {
        if (moving) {
            forces.y += mass * grav;
        }
    }
    void updateAcceleration(float grav) {
        forces = {0.f, 0.f};
        applyGravity(grav);
        applyFriction();
        // velocity = (forces * (1/mass)) * dt;
        acc = (forces * (1/mass));
    }
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


    /*
     * PBD algorithm
     *     // DANS UNE METHODE DE PARTICULE
     *      v = v + (dt * forces) * 1/m;
     *      damping_velocities() => damping_particle()
     *      nextPos = currentX + v*dt
     *      Génerer toutes les contraintes à gérer;
     *      Modifier la position selon les contraintes
     *
     *      // Recalculer la vitesse après la nouvelle position
     *      v = (currentX - previousX) / dt
     *      current = previous;
     *
     *      // Mettre à jour la vitesse en fonction des coefficients de friction/ resitution
     *      updatevelocity (friction/ restitution)
     *
     */

    /*
    void updateVerlet (float dt) {
        if (this->moving) {
            sf::Vector2f posCopy = this->pos;
            this->pos = 2.f*this->pos - this->prev_pos + (dt * dt) * this->acc;
            this->prev_pos = posCopy;
        }
    }
    */
    Particle(float x, float y, float m) : pos(sf::Vector2f {x,y}), prev_pos(sf::Vector2f {x,y}), mass(m) {
        // SFML Shape creation
        sf::CircleShape ParticleShape(2.f);
        ParticleShape.setFillColor(sf::Color(255, 255, 255));
        this->shape.setPosition(x, y);
        this->shape = ParticleShape;
    }
    Particle(float xprev, float yprev, float x, float y) {
        this->pos = {x, y};
        this->prev_pos = {x, y};
    }
};

#endif //CLOTHES_CLASSPARTICLE_H

