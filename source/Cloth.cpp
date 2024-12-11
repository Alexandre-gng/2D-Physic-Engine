#include "../include/Objects/ClassCloth.hpp"
#include "../include/ClassParticle.hpp"




/*
* SUPRESSION 1 PARTICLE (ptr_p)
*      // Suppression de la référence des triangles voisins de ptr_p
*      // Pour tous les triangles que constituent ptr_p (Z1):
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
*      // Supprimer la référence de ptr_p dans les triangles voisins de ceux qu'il compose
*      // Pour tous les Joints qui contiennent ptr_p :
*      //          Surtout une étape afin d'éviter les fuites de mémoire
*     for (Joint ptr_j : ptr_p->list_joints) {
*          delete ptr_j;
*     }
*
*     // Particules voisines de ptr_p:
*          => Supprimer la référence aux Joint en communs
*          => Supprimer la référencee aux Triangles en commun
*
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
*      delete la prticle
*/

// Delete a Particle in the Cloth, and all of the Triangle and Joint that contain it
void Cloth::supp_Particle(Particle* ptr_P) {
    cout << "start supp particl"<< endl;
    // Delete all of the ptr_T concerned in the Cloth->TABtriangles
    for (auto& row_T: this->TAB_triangles) {
        for (auto& ptr_T: row_T) {
            if (ptr_T != nullptr) {
                for (auto it = ptr_P->list_triangles_friends.begin(); it != ptr_P->list_triangles_friends.end(); it++) {
                    if (*it == ptr_T) {
                        ptr_P->list_triangles_friends.erase(it);
                        break;
                    }
                }
            }
        }
    }

    // Delete the ptr_P in the Cloth->TABparticles
    for (auto it = this->LIST_particles.begin(); it != this->LIST_particles.end(); it++) {
        if (*it == ptr_P) {
            this->LIST_particles.erase(it);
            break;
        }
    }

    // Delete the reference of the neighbour triangles of ptr_P
    for (Triangle *ptr_T: ptr_P->list_triangles_friends) {
        int l1 = 0, l2 = 0, l3 = 0;
        for (Triangle *ptr_T_neighbour: ptr_T->list_nearest_triangles) {
            if (ptr_T_neighbour != nullptr) {
                int cpt = 0;
                // loop ? YYY
                for (int i = 0; i < ptr_T_neighbour->list_nearest_triangles.size(); i++) {
                    cpt ++;
                }
                for (auto it = ptr_T_neighbour->list_nearest_triangles.begin(); it != ptr_T_neighbour->list_nearest_triangles.end(); it++) {
                    if (*it == ptr_T) {
                        *it = nullptr;
                        ptr_T_neighbour->list_nearest_triangles.erase(it);
                        break;
                    }
                }
            }
        }
    }

    // Delete the dead joints of all ptr_P's neighbours particles
    for (auto ptr_J: ptr_P->list_joints) {
        if (ptr_J->particle1 == ptr_P) {
            for (auto it = ptr_J->particle2->list_joints.begin(); it != ptr_J->particle2->list_joints.end(); it++) {
                if (*it == ptr_J) {
                    *it = nullptr;
                    ptr_J->particle2->list_joints.erase(it);
                    break;
                }
            }
        } else {
            for (auto it = ptr_J->particle1->list_joints.begin(); it != ptr_J->particle1->list_joints.end(); it++) {
                if (*it == ptr_J) {
                    *it = nullptr;
                    ptr_J->particle1->list_joints.erase(it);
                    break;
                }
            }
        }
    }

    // Delete all dead Triangles of the ptr_P's neighbours Particle
    for (auto ptr_T: ptr_P->list_triangles_friends) {
        for (auto ptr_J: ptr_T->list_joints) {
            if (ptr_J->particle1 != ptr_P && ptr_J->particle2 != ptr_P) {
                if (ptr_J->particle1 != nullptr) {
                    for (auto it = ptr_J->particle1->list_triangles_friends.begin(); it != ptr_J->particle1->list_triangles_friends.end(); it++) {
                        if (*it == ptr_T) {
                            *it = nullptr;
                            ptr_J->particle1->list_triangles_friends.erase(it);
                            break;
                        }
                    }
                }
                if (ptr_J->particle2 != nullptr) {
                    for (auto it = ptr_J->particle2->list_triangles_friends.begin(); it != ptr_J->particle2->list_triangles_friends.end(); it++) {
                        if (*it == ptr_T) {
                            *it = nullptr;
                            ptr_J->particle2->list_triangles_friends.erase(it);
                            break;
                        }
                    }
                }
            }
        }
    }

    // Delete every Triangle that contain ptr_P
    for (auto ptr_T: ptr_P->list_triangles_friends) {
        if (ptr_T == nullptr) { continue;}
        delete ptr_T;
    }

    // Delete every joints that contain ptr_P
    for (auto ptr_J: ptr_P->list_joints) {
        if (ptr_J == nullptr) { continue;}
        delete ptr_J;
    }

    delete ptr_P;
}
