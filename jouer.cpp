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

void jouer(grille & G, int & interval, sf::RenderWindow & f) {
    std::chrono::time_point<std::chrono::system_clock> debut = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> fin = debut + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;
    char bouge = ' ';

    do { // Boucle pour avoir le temps de l'intervale
        maintenant = std::chrono::system_clock::now();
        std::chrono::milliseconds ecoule = std::chrono::duration_cast<std::chrono::milliseconds>(maintenant - debut);

        f.clear(sf::Color::Black);

        // Stocker la direction dans laquel bouger le tetromino
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bouge = 'G';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bouge = 'D';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) bouge = 'B';
        deplacer(G, bouge);

        // Changer le courant si on eenvoie le courna en bas
        if (bouge == 'B') {
            apparait(G);
            maintenant == fin;
        }

        bouge = ' ';

        // On verifie si le joueur tourne la piece
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) tourner(G, false);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) tourner(G, true);

        dessinerGrille(f, G);

        f.display();

    } while (maintenant < fin);
    deplacer(G, 'b');
    if (toucher(G)) {
        apparait(G);
    }

    dessinerGrille(f, G);

    f.display();
}

int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 520}), "Tetris");
    fenetre.setFramerateLimit(24);
    
    grille g;
    g.nb = 0;
    g.places = new tetrominoPlace[0];
    
    g.courant = new tetrominoPlace;
    g.next = new tetrominoPlace;
    
    choisisTetromino(*g.courant);
    g.courant->Positions[0] = 3;
    g.courant->Positions[1] = 0; 
    for (int i = 0; i < 4; ++i) {
        if (!verifierLigneTetrominoVide(g, i)) g.courant->Positions[1] = -i;
    }
    
    choisisTetromino(*g.next);
    g.next->Positions[0] = 3;
    g.next->Positions[1] = 0;

    int level = 0, nombreDeLignes = 0, score = 0, intervalle = 1000;

    while (fenetre.isOpen()) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                fenetre.close();
        }
        jouer(g, intervalle, fenetre);

        // Supprimer les lignes completes
        int ligneSupr = 0;
        for (int i = 0; i<20; ++i) {
            if (verifLigne(g, i)) {
                ++ligneSupr;
                ++nombreDeLignes;
            }
        }
        level = nombreDeLignes/10;
        if (ligneSupr == 1) score = score + level * 100;
        else if (ligneSupr == 2) score = score + level * 300;
        else if (ligneSupr == 3) score = score + level * 500;
        else if (ligneSupr == 4) score = score + level * 800;
        else if (ligneSupr > 4) score = score + 50*ligneSupr*level;
        if (ligneSupr != 0) {
            if (level == 0) intervalle = 1000;
            else if (level < 15) intervalle = intervalle * 0.75;
            else intervalle = intervalle * 0.9;
        }
    }

    // Libérer la mémoire
    delete g.courant;
    delete g.next;
    delete[] g.places;

    return 0;
}