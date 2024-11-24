#include "ClassCloth.h"
#include "ClassTriangle.h"
#include "ClassParticle.h"

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

// YYY
void Cloth::detect_Particle(sf::Vector2f mousePos) {
    bool stop = false;
    for (int i = 0; i < this->height; i++) {
        for (int j = 0; j < this->width; j++) {
            if (stop) break;
            Particle *ptrP = this->TABparticles[i][j];
            if (ptrP != nullptr) {
                if ((mousePos.x + 5.0 > ptrP->pos.x) && (mousePos.x - 5.0 < ptrP->pos.x)) {
                    if ((mousePos.y + 5.0 > ptrP->pos.y) && (mousePos.y - 5.0 < ptrP->pos.y)) {
                        // SUPP PARTICLE
                        stop = true;
                        break;
                    }
                }
            }
        }
    }
}
/*
* SUPRESSION 1 PARTICLE (ptr_p)
*      // Pour tous les triangles que constitue ptr_p (Z1):
*      for (Triangle ptr_t : ptr_p->list_triangles_friends) {
*          // Pour tous les triangles de Z2:
*          for (Triangle t_voisin: ptr_t->list_nearest_triangles) {
*              if (t_voisin != nullptr) {
*                  if (t_voisin == ptr_t) {
*                      TYPE *var = t_voisin->list_nearest_triangles // ASSIGNER PTR POUR MODIFIER
*                      var = nullptr
*                  }
*              }
*          }
*      }
*
*      // Pour tous les Joints qui contiennent ptr_p :
*      //          Surtout une étape afin d'éviter les fuites de mémoire
*     for (Joint ptr_j : ptr_p->list_joints) {
*          delete ptr_j;
*     }
*
*     // Supprimer les triangles liés à la ptr_p dans Cloth->list_triangles
*     for (Triangle ptr_t: Cloth->list_triangles) {
*          for (Triangle ptr_t2: ptr_p->list_triangles_friends) {
*              if (ptr_t == ptr_t2) {
*                  // SUPPRESSION PAR PTR A FAIRE
*                  ptr_t = nullptr
*              }
*          }
*     }
*
*     // Suprimer le ptr_p dans Cloth->TABparticles
*     for (int i = 0; i < this->height; i++) {
*          for (int j = 0; j < this->width; j++) {
*              if (ptr_p == Cloth->TABparticles[i][j]) {
*                  // SUPPRESSION PAR PTR A FAIRE
*                  Cloth->TABparticles[i][j] = nullptr;
*              }
*          }
*      }
*
*      delete la prticle
*/

// YYY YYY TO DO !
/*
void Cloth::supp_Particle(Particle* ptr_P) {
    // Pour tous les triangles que constitue ptr_p (Z1):
    for (Triangle *ptr_T: ptr_P->list_triangles_friends) {
        // Pour tous les triangles de Z2:
        for (Triangle *ptr_T_neighbour: ptr_T->list_nearest_triangles) {
            if (ptr_T_neighbour != nullptr) {
                if (ptr_T_neighbour == ptr_T) {
                    Triangle *var = ptr_T_neighbour->list_nearest_triangles
                    var = nullptr;
                }
            }
        }
    }
}
 */