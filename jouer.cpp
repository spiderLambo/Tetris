#include "jouer.h"

// #include <iostream>

void genereTetro (tetromino & tetro, char type) {
    // Tetromino vide
    for (int i = 0; i<4; ++i) {
        tetro[0][i] = false;
        tetro[1][i] = false;
        tetro[2][i] = false;
        tetro[3][i] = false;
    }
    if (type == 'I') {
        // - - - -
        // . . . .
        for (int i = 0; i<4; ++i) {
            tetro[2][i] = true;
        }
    } else if (type == 'O') {
        // . - - .
        // . - - .
        tetro[1][1] = true;
        tetro[2][1] = true;
        tetro[1][2] = true;
        tetro[2][2] = true;
    } else if (type == 'T') {
        // . - - -
        // . . - .
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][2] = true;
    } else if (type == 'L') {
        // . - - -
        // . - . .
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][1] = true;
    } else if (type == 'J') {
        // . - - -
        // . . . -
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][3] = true;
    } else if (type == 'Z') {
        // . - - .
        // . . - -
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[3][3] = true;
        tetro[3][2] = true;
    } else if (type == 'S') {
        // . . - -
        // . - - .
        tetro[3][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][2] = true;
    }
}


void initRect (regctangle & rec, float taillex, float tailley, float x, float y) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineColor(sf::Color(255, 255, 255));
    rec.setOutlineThickness(10);
}

void afficherTetromino (sf::RenderWindow & f, tetrominoPlace t) {
    for (int i = t.Positions[0]; i<t.Positions[0]+4; ++i) {
        for (int j = t.Positions[1]; j<t.Positions[1]+4; ++j) {
            if (t.tetro[i][j]) {
                regctangle r;
                initRect(r, 15, 15, i*25+10, j*25+10);
                f.draw(r);
            }
        }
    }
}

void dessinerGrille (sf::RenderWindow & f, grille G) {
    regctangle grilleRegctangle;
    initRect(grilleRegctangle, 250, 500, 10, 10);
    f.draw(grilleRegctangle);

    // afficher les tetrominos placées
    for (int i = 0; i<G.nb; ++i) {
        afficherTetromino(f, G.places[i]);
    }
}

void jouer(grille & G, int & level, int & interval) {
    std::chrono::time_point<std::chrono::system_clock> debut = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> fin = debut + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;

    do { // Bouchle pour avoir le temps de l'intervale
        maintenant = std::chrono::system_clock::now();
        std::chrono::milliseconds ecoule = std::chrono::duration_cast<std::chrono::milliseconds>(maintenant - debut);
        // char sens;
        // std::cin>>sens;
        // if (sens) {
        //     tourner(G, sens);
            // sens = is null
        // }

    } while (maintenant < fin);
}

int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 520}), "Tetris");
    fenetre.setFramerateLimit(24);
    grille g;
    tetrominoPlace S, T;
    genereTetro(S.tetro, 'S');
    genereTetro(T.tetro, 'T');
    S.Positions = {3, 4};
    T.Positions = {5, 15};
    g.places = new tetrominoPlace [2];
    g.places[0] = T;
    g.places[1] = S;
    g.nb = 2;

    while (fenetre.isOpen()) {
        // Gestion des événements
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetre.close();
        }

        fenetre.clear(sf::Color::Black);


        dessinerGrille(fenetre, g);


        fenetre.display();
    }

    return 0;
}