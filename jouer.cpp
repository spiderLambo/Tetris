#include "jouer.h"

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y) {
    sf::Font font;
    font.loadFromFile(police);
    sf::Text text(texte, font, 50);
    text.setPosition(x, y);
    f.draw(text);
}

void initRect (regctangle & rec, float taillex, float tailley, float x, float y) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(sf::Color::Transparent);
    rec.setOutlineColor(sf::Color(255, 255, 255));
    rec.setOutlineThickness(10);
}

void dessinerGrille (sf::RenderWindow & f, grille G) {
    regctangle grilleRegctangle;

    // Afficher la grille
    initRect(grilleRegctangle, 240, 490, 10, 10);
    f.draw(grilleRegctangle);

    // Afficher les tetrominos
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (G[i][j] != ' ') {
                regctangle r;
                initRect(r, 15, 15, j*25+10, i*25+10);
                f.draw(r);
            }
        }
    }
}

void jouer(grille & G, int level, int score, int & interval, sf::RenderWindow & f) {
    std::chrono::time_point<std::chrono::system_clock> debut = std::chrono::system_clock::now();
    std::chrono::time_point<std::chrono::system_clock> fin = debut + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;
    char bouge = ' ';
    
    
    
    do { // Boucle pour avoir le temps de l'intervale
        maintenant = std::chrono::system_clock::now();
        std::chrono::milliseconds ecoule = std::chrono::duration_cast<std::chrono::milliseconds>(maintenant - debut);
        
        f.clear(sf::Color::Black);
        // Afficher les infos
        afficherTexte(f, "Level : " + std::to_string(level), "./chomsky/Chomsky.woff", 300, 50);
        afficherTexte(f, "Score : " + std::to_string(score), "./chomsky/Chomsky.woff", 300, 150);

        // Stocker la direction dans laquel bouger le tetromino
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) bouge = 'G';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) bouge = 'D';
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) bouge = 'B';
        deplacer(G, bouge);

        // Changer le courant si on eenvoie le courna en bas
        if (bouge == 'B') {
            placer(G);
            genereTetromino(G);
            maintenant == fin;
        }

        bouge = ' ';

        // On verifie si le joueur tourne la piece
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) tourner(G, false);
        // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) tourner(G, true);

        dessinerGrille(f, G);

        f.display();

    } while (maintenant < fin);
    // Faire decendre le tetromino
    deplacer(G, 'b');

    // Verifier les collision
    if (collision(G)) {
        placer(G);
        genereTetromino(G);
    }

    dessinerGrille(f, G);

    f.display();
}

int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(24);
    
    int level = 0, score = 0, intervalle = 1000;

    grille g;
    initGrille(g);
    apparait(g, 'T');
    while (fenetre.isOpen()) {
        sf::Event event;
        while (fenetre.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
            fenetre.close();
        }
        jouer(g, level, score, intervalle, fenetre);
    }
}