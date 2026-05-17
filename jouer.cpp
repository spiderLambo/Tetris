#include "jouer.h"

bool premiereReserveEffectuee = false;

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y) {
    sf::Font font;
    font.loadFromFile(police);
    sf::Text text(texte, font, 25);
    text.setPosition(x, y);
    f.draw(text);
}

void initRect (regctangle & rec, float taillex, float tailley, float x, float y, sf::Color fond, sf::Color outline) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(fond);
    rec.setOutlineColor(outline);
    rec.setOutlineThickness(10);
}

void afficherNext (sf::RenderWindow & f, char next) {
    afficherTexte(f, "Suivant : ", "./chomsky/Chomsky.woff", 300, 100);

    regctangle r1;
    regctangle r2;
    regctangle r3;
    regctangle r4;


    if (next == 'I') {
        initRect(r1, 15, 15, 350, 175, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r2, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r3, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r4, 15, 15, 425, 175, sf::Color::Transparent, sf::Color(0, 245, 255));
    } else if (next == 'O') {
        initRect(r1, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r2, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r3, 15, 15, 375, 200, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r4, 15, 15, 400, 200, sf::Color::Transparent, sf::Color(255, 0, 128));
    } else if (next == 'T') {
        initRect(r1, 15, 15, 350, 175, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 200, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (next == 'L') {
        initRect(r1, 15, 15, 350, 175, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 350, 200, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (next == 'J') {
        initRect(r1, 15, 15, 350, 175, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r2, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r3, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r4, 15, 15, 400, 200, sf::Color::Transparent, sf::Color(255, 230, 0));
    } else if (next == 'Z') {
        initRect(r1, 15, 15, 350, 175, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 375, 200, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 400, 200, sf::Color::Transparent, sf::Color(255, 106, 0));
    } else if (next == 'S') {
        initRect(r1, 15, 15, 375, 175, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 400, 175, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 350, 200, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 375, 200, sf::Color::Transparent, sf::Color(255, 106, 0));
    }

    f.draw(r1);
    f.draw(r2);
    f.draw(r3);
    f.draw(r4);
}

void afficherReserve (sf::RenderWindow & f, char reserve) {
    afficherTexte(f, "Reserve : ", "./chomsky/Chomsky.woff", 300, 250);

    regctangle r1;
    regctangle r2;
    regctangle r3;
    regctangle r4;


    if (reserve == 'I') {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r4, 15, 15, 425, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
    } else if (reserve == 'O') {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r2, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r3, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 0, 128));
    } else if (reserve == 'T') {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (reserve == 'L') {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'J') {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 230, 0));
    } else if (reserve == 'Z') {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
    } else if (reserve == 'S') {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
    }

    f.draw(r1);
    f.draw(r2);
    f.draw(r3);
    f.draw(r4);
}

void dessinerGrille (sf::RenderWindow & f, plateau G) {
    regctangle grilleRegctangle;

    // Afficher la grille
    initRect(grilleRegctangle, 240, 490, 10, 10, sf::Color(28,28,46), sf::Color(64,64,96));
    f.draw(grilleRegctangle);

    // Afficher le next
    afficherNext(f, G.next);

    // Afficher la reserve
    afficherReserve(f, G.reserve);

    // Afficher les tetrominos
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (G.gr[i][j] != ' ') {
                regctangle r;
                initRect(r, 15, 15, j*25+10, i*25+10, sf::Color(0, 53, 69), sf::Color(0, 136, 160));
                f.draw(r);
            }
        }
    }
}

void jouer(plateau & G, int level, int score, int & interval, sf::RenderWindow & f, bool & peuxReserver) {
    std::chrono::time_point<std::chrono::system_clock> fin = std::chrono::system_clock::now() + std::chrono::milliseconds(interval);
    std::chrono::time_point<std::chrono::system_clock> maintenant;

    do {
        maintenant = std::chrono::system_clock::now();

        sf::Event event;
        while (f.pollEvent(event)) {
            if (event.type == sf::Event::Closed) f.close();
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Left)  deplacer(G.gr, 'G');
                else if (event.key.code == sf::Keyboard::Right) deplacer(G.gr, 'D');
                else if (event.key.code == sf::Keyboard::Enter) {
                        deplacer(G.gr, 'B');
                        placer(G.gr);
                        genereTetromino(G);
                        peuxReserver = true;
                        maintenant = fin;
                } else if (event.key.code ==  sf::Keyboard::Up) tourner(G.gr, false);
                else if (event.key.code == sf::Keyboard::Down) tourner(G.gr, true);
                else if (event.key.code == sf::Keyboard::R and peuxReserver) {
                    reserver(G);
                    if (!premiereReserveEffectuee) {
                        premiereReserveEffectuee = true;
                        genereTetromino(G);
                    }
                    peuxReserver = false;
                }
            }
        }

        f.clear(sf::Color(19,19,31));
        afficherTexte(f, "Level : " + std::to_string(level), "./chomsky/Chomsky.woff", 300, 20);
        afficherTexte(f, "Score : " + std::to_string(score), "./chomsky/Chomsky.woff", 300, 60);
        dessinerGrille(f, G);
        f.display();

    } while (maintenant < fin);



    deplacer(G.gr, 'b');


    if (collision(G.gr)) {
        placer(G.gr);
        genereTetromino(G);
        peuxReserver = true;
    }

    if (fini(G.gr)) f.close();


    dessinerGrille(f, G);
    f.display();
}


int main () {
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(24);
    
    plateau g;
    initGrille(g.gr);
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    g.next = choix[std::rand()%7];
    genereTetromino(g);

    bool peuxReserver = true;

    int level = 1, nombreDeLignes = 10, score = 0, intervalle = 1000;
    while (fenetre.isOpen()) {
        // sf::Event event;
        // while (fenetre.pollEvent(event)) {
        //     if (event.type == sf::Event::Closed)
        //     fenetre.close();
        // }
        jouer(g, level, score, intervalle, fenetre, peuxReserver);

         // Supprimer les lignes completes
        int ligneSupr = 0;
        for (int i = 0; i<HAUTEUR; ++i) {
            if (peuxSupprimerLigne(g.gr, i)) {
                supprimerLigne(g.gr, i);
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