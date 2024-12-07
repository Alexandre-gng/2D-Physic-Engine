#include "ClassObject.h"

/*
 * Suppression des deux Triangles concernés:
 *      Triangle *ptr_TA_save, ptr_TB_save;
 *      bool found_TA = false;
 *      => Parmi tous les triangles de ptr_J->P1:
 *             Parmi tous les triangles de ptr_J->P2:
 *                  Si ptr_TA == ptr_TB:
 *                      found_TA = true
 *                      if (found_TA = true) {
 *                          ptr_TA_save = ptr_TA;
 *                      } else {
 *                          ptr_TB_save = ptr_TB;
 *                      }
 *                      // Suppression de la référence dans les listes de triangles voisins
 *                      Parmi les voisins de ptr_TA:
 *                          Parmi les voisins de (voisin_ptr_TA):
 *                              Si voisin_ptr_TA == ptr_TA:
 *                                  Suppression de la référence avec erase
 *
 *                      // Suppression de la référence des deux Triangle TA et TB dans les Particle qui constituent TA et TB
 *                      Parmi tout Joint de ptr_TA: (temp_J)
 *                          Si temp_J != ptr_J:
 *                              Si temp_J->PA != ptr_J->P1 && temp_J->PA != ptr_J->P2:
 *                                  temp_J->PA->list_triangles_friends.erase(ptr_TA)
*                               Si temp_J->PB != ptr_J->P1 && temp_J->PB != ptr_J->P2:
 *                                  temp_J->PB->list_triangles_friends.erase(ptr_TA)
 *
 *      // Suppression de ptr_TA et ptr_TB dans Cloth->list_triangles
 *      for (auto x: TABtriangles) {
 *          for (auto y: x) {
 *              // Suppression de la référence dans le TAB
 *              y = nullptr;
 *          }
 *      }
 *
 *      Suppression de ptr_TA et ptr_TB (delete)
 *      delete ptr_TA_save;
 *      delete ptr_TB_save;
 *      delete ptr_J;
 *
 */
// YYY : Faire que la fonction retourne un " Particle* ", et que l'appel de la suppression se fasse dans le main
void Object::detect_Particle(sf::Vector2f mousePos) {
    for (const auto i : this->LIST_particles) {
        Particle* ptr_P = i;
        if (ptr_P != nullptr) {
            if ((mousePos.x + 5.0 > ptr_P->pos.x) && (mousePos.x - 5.0 < ptr_P->pos.x)) {
                if ((mousePos.y + 5.0 > ptr_P->pos.y) && (mousePos.y - 5.0 < ptr_P->pos.y)) {
                    if (this->object_type == CLOTH) {
                        this->supp_Particle(ptr_P);
                    }
                    return;
                }
            }
        }
    }
}

void Object::deleteJoint(Joint* ptr_J) {
    return;
}