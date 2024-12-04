#include "ClassObject.h"

void Object::detect_Particle(sf::Vector2f mousePos) {
    for (const auto i : this->TABparticles) {
        for (const auto ptrP : i) {
            if (ptrP != nullptr) {
                if ((mousePos.x + 5.0 > ptrP->pos.x) && (mousePos.x - 5.0 < ptrP->pos.x)) {
                    if ((mousePos.y + 5.0 > ptrP->pos.y) && (mousePos.y - 5.0 < ptrP->pos.y)) {
                        if (this->object_type == CLOTH) {
                            this->supp_Particle(ptrP);
                        }
                        return;
                    }
                }
            }
        }
    }
}