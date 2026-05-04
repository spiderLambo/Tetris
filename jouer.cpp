#include "jouer.h"
#include <iostream>


void initRect (regctangle & rec, float taillex, float tailley, float x, float y) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineColor(sf::Color(255, 255, 255));
    rec.setOutlineThickness(10);
}

void afficherTetromino (sf::RenderWindow & f, tetrominoPlace t) {
    for (int i = 0; i<4; ++i) {
        for (int j = 0; j<4; ++j) {
            if (t.tetro[i][j]) {
                regctangle r;
                initRect(r, 15, 15, (t.Positions[0]+j)*25+10, (t.Positions[1]+i)*25+10);
                f.draw(r);
            }
        }
    }
}

void dessinerGrille (sf::RenderWindow & f, grille G) {
    regctangle grilleRegctangle;
    initRect(grilleRegctangle, 250, 500, 10, 10);
    f.draw(grilleRegctangle);

    // Afficher les tetrominos placées
    for (int i = 0; i<G.nb; ++i) {
        afficherTetromino(f, G.places[i]);
    }

    // Afficher le courant
    afficherTetromino(f, *G.courant);
}

void choisisTetromino (tetrominoPlace & T) {
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    genereTetro(T.tetro, choix[std::rand()%7]);
}

void jouer(grille & G, int & level, int & interval, sf::RenderWindow & f) {
    std::chrono::time_point<std::chrono::system_clock> debut = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> fin = debut + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;
    char bouge = ' ';

    do { // Boucle pour avoir le temps de l'intervale
        maintenant = std::chrono::system_clock::now();
        std::chrono::milliseconds ecoule = std::chrono::duration_cast<std::chrono::milliseconds>(maintenant - debut);

        f.clear(sf::Color::Black);
        // char sens;
        // std::cin>>sens;
        // if (sens) {
        //     tourner(G, sens);
            // sens = is null
        // }
        // Stocker la direction dans laquel bouger le tetromino
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bouge = 'G';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bouge = 'D';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) bouge = 'b';
        deplacer(G, bouge);
        bouge = ' ';

        dessinerGrille(f, G);

        f.display();

    } while (maintenant < fin);
}

int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 520}), "Tetris");
    fenetre.setFramerateLimit(24);
    grille g;
    g.next = new tetrominoPlace;
    choisisTetromino(*g.next);
    apparait(g);
    choisisTetromino(*g.next);

    int l, i = 1000;

    while (fenetre.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetre.close();
        }

        // if (toucher(g)) {
        //     apparait(g);
        //     choisisTetromino(*g.next);
        // }

        jouer(g, l, i, fenetre);



    }

    return 0;
}