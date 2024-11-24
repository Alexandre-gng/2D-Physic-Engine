/*
 * ETAPES COURT TERME:
 *    -> problèmes de dépendances 
 *    -> Algorithme de suppression d'une seule Particle
 *    -> Algorithme de suppression d'un Joint (rupture car trop de distance)
 *
 * ETAPES LONG TERME:
 *    -> Implémenter les contraintes de base sur un Cloth (Bending)
 *    -> Détection des collisions internes avec une hash map (Muller)
 *          => Le généraliser à tout l'espace avec une Barnes-Hut ?
 *
 *    - Collision et réponse sur des surfaces plates le long des aces x et y.
 *
 *    - Ajout du "Separating Axis Theorem" afin de gérer les collisions sur des objets non parallèles aux axes
 *    - Lire "Robust Treatment of Collisions, Contact and Friction for Cloth Animation"
 *
 *
 *  AMELIORATIONS:
 *      - Enlever l'initialisation en programmation dynamique des triangles voisins
 *          => Utiliser la méthode Muller
 *          => Conclusion: méthode qui demande bcp de calculs ? autant les initialiser dès le début
 *      - Changer toutes les types de liste différents pour un seul même (idéalement convertir les vector en eigen)
 *      - Améliorer le CMakeList afin d'importer Eigen par github, ou alors de trier les fichiers pour que ce soit propre
 */


/*
 * Réorganisation:
 *      - Le PBD génére les contraintes à projeter, en fonction de l'objet et du contexte
 *          -> Contraintes absolues
 *          -> Contraintes occasionnelles (Proviennent de la détection de collisions)
 *              => Sont ajoutées en fonction de la situation: Grâce à Physic ?
 *
 *          -> Certaines contraintes impliquent un ensemble de particules
 *                 => YYY Problème: comment les objets doivent traiter les contraintes alors qu'elles requierent
 *                 différents type d'ensemble (triangles, particules seules...) ?
 *
 *                      -> Donner à chaque Contrainte un attribut qui décrit qu'elle type d'ensemble elle requiert ?
 *                          => Ds Physic: Pour chaque Objets:
 *                                          Pour chaque Contrainte de l'Object:
 *
 */

#include "ClassCloth.h"
#include "ClassParticle.h"
#include "ClassPhysic.h"

using namespace std;

int main() {
    cout << "STARTING..." << endl;

    const float DELTA_T_S = 0.005;
    const short DELTA_T_MS = DELTA_T_S*1000;


    Cloth* ptr_Cloth = new Cloth(250, 200, 18, 26, 15.f, 1.f, 0.01f);

    Physic* ptr_Physic = new Physic({ptr_Cloth}, 5000);

    sf::RenderWindow window(sf::VideoMode(800, 600), "cloth simulation");

    // Floor
    //Solid solid(sf::Vector2f(300, 500), 200, 50);  // Position et taille du solide


    while (window.isOpen()) {
        this_thread::sleep_for(chrono::milliseconds(DELTA_T_MS));
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                sf::Vector2f newMousePos = window.mapPixelToCoords(mousePos);
                ptr_Cloth->supp_Particle(newMousePos);
            }
        }
        window.clear(sf::Color::Black);
        ptr_Physic->PBD(DELTA_T_S, 0.f, 10);

        for (int i = 0; i < ptr_Cloth->height; i++) {
            for (int j = 0; j < ptr_Cloth->width; j++) {
                Particle *ptrP = ptr_Cloth->TABparticles[i][j];
                if (ptrP == nullptr) {
                    continue;
                }
                ptrP->shape.setPosition(ptrP->pos.x, ptrP->pos.y);
                window.draw(ptrP->shape);
            }
        }
        window.display();
    }

    return 0;
}
