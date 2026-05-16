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
    std::chrono::time_point<std::chrono::system_clock> fin = std::chrono::system_clock::now() + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;

    do {
        maintenant = std::chrono::system_clock::now();

        sf::Event event;
        while (f.pollEvent(event)) {
            if (event.type == sf::Event::Closed) f.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left)  deplacer(G, 'G');
                else if (event.key.code == sf::Keyboard::Right) deplacer(G, 'D');
                else if (event.key.code == sf::Keyboard::Enter) {
                        deplacer(G, 'B');
                        placer(G);
                        genereTetromino(G);
                        maintenant = fin;
                } else if (event.key.code ==  sf::Keyboard::Up) tourner(G, false);
                else if (event.key.code == sf::Keyboard::Down) tourner(G, true);
            }
        }

        f.clear(sf::Color::Black);
        afficherTexte(f, "Level : " + std::to_string(level), "./chomsky/Chomsky.woff", 300, 50);
        afficherTexte(f, "Score : " + std::to_string(score), "./chomsky/Chomsky.woff", 300, 150);
        dessinerGrille(f, G);
        f.display();

    } while (maintenant < fin);


    deplacer(G, 'b');


    if (collision(G)) {
        placer(G);
        genereTetromino(G);
    }

    if (fini(G)) f.close();


    dessinerGrille(f, G);
    f.display();
}


int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(24);
    
    grille g;
    initGrille(g);
    genereTetromino(g);

    int level = 0, nombreDeLignes = 0, score = 0, intervalle = 1000;
    while (fenetre.isOpen()) {
        // sf::Event event;
        // while (fenetre.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed)
        //     fenetre.close();
        // }
        jouer(g, level, score, intervalle, fenetre);

         // Supprimer les lignes completes
        int ligneSupr = 0;
        for (int i = 0; i<HAUTEUR; ++i) {
            if (peuxSupprimerLigne(g, i)) {
                supprimerLigne(g, i);
                ++ligneSupr;
                ++nombreDeLignes;
            }
        }

        // Calcul des valeurs a moidifier
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
}