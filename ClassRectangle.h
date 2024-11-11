//
// Created by alexa on 10/11/2024.
//

#ifndef CLOTHES_CLASSRECTANCLE_H
#define CLOTHES_CLASSRECTANCLE_H

#include "ClassObject.h"

class Rectangle: public Object {
    sf::Vector2f corner_top_left;
    sf::Vector2f corner_bottom_right;
    int height;
    int width;

    Rectangle(const sf::Vector2f& topLeft, int w, int h)
            : corner_top_left(topLeft), width(w), height(h) {
        corner_bottom_right = sf::Vector2f(topLeft.x + w, topLeft.y + h);
    }

    sf::RectangleShape getRectangleShape() const {
        sf::RectangleShape rectangle(sf::Vector2f(width, height));
        rectangle.setPosition(corner_top_left);
        rectangle.setFillColor(sf::Color::Green);  // Couleur du solide
        return rectangle;
    }
};

#endif //CLOTHES_CLASSRECTANCLE_H
