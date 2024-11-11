/*
 * ETAPES:
 *    - Collision et réponse sur des surfaces plates le long des aces x et y.
 *
 *    - Ajout du "Separating Axis Theorem" afin de gérer les collisions sur des objets non parallèles aux axes
 *    - Lire "Robust Treatment of Collisions, Contact and Friction for Cloth Animation"
 *
 * Comment faire en sorte que la classe Constraint stocke une liste de method ?
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
    ptrCloth = new Cloth(250,200,17, 25, 15.f, 5000.f, 0.01f);

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
        ptrCloth->PBD(DELTA_T_S, 1.0, 10);

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
        //window.draw(solid.getRectangleShape());
        /*
        ptrCloth->updateAllAccelerations();
        ptrCloth->simulateVerlet(DELTA_T_S);
        ptrCloth->JakobsenMethod();
        //ptrP->velocity = (ptrP->pos - ptrP->prev_pos) / DELTA_T_S;

        for (int i = 0; i < ptrCloth->height; i++) {
            for (int j = 0; j < ptrCloth->width; j++) {
                Particle *ptrP = ptrCloth->TABparticles[i][j];
                if (ptrP == nullptr) continue;
                ptrP->velocity = (ptrP->pos - ptrP->prev_pos) / DELTA_T_S;
                float forceTOT = sqrt(ptrP->forces.x*ptrP->forces.x + ptrP->forces.y*ptrP->forces.y);
                ptrP->shape.setPosition(ptrP->pos.x, ptrP->pos.y);
                window.draw(ptrP->shape);
            }
        }
         */
        window.display();
    }

    return 0;
}
