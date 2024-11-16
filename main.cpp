/*
 * ETAPES:
 *
 *    -> Implémenter les contraintes de base sur un Cloth (Bending)
 *    -> Refaire tout le système de Classe en commencant par 'Cloth'
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
 *
 */


#include "ClassCloth.h"
#include "ClassObject.h"

using namespace std;

int main() {
    cout << "STARTING..." << endl;

    const float DELTA_T_S = 0.005;
    const short DELTA_T_MS = DELTA_T_S*1000;

    Cloth* ptrCloth;

    hash<float> a;

    const float MIN_DISTANCE_ROPE = 6.f;

    //ptrCloth = new Cloth(250,200,17, 25, 15.f, 2500.f, 0.05f);
    ptrCloth = new Cloth(250,200,18, 26, 15.f, 1.f, 5000.f, 0.01f);

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
                ptrCloth->suppParticle(newMousePos);
            }
        }
        window.clear(sf::Color::Black);
        //ptrCloth->PBD(DELTA_T_S, 0.f, 10);

        for (int i = 0; i < ptrCloth->height; i++) {
            for (int j = 0; j < ptrCloth->width; j++) {
                Particle *ptrP = ptrCloth->TABparticles[i][j];
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
