#include "jouer.h"

// Variable globale pour la 1ere réserve
bool premiereReserveEffectuee = false;

// Variable qui gere la pause
bool pause = false;





// Affiche du texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y) {
    sf::Font font;
    font.loadFromFile(police);
    sf::Text text(texte, font, 25);
    text.setPosition(x, y);
    f.draw(text);
}

// Initialise un rectangle
void initRect (regctangle & rec, float taillex, float tailley, float x, float y, sf::Color fond, sf::Color outline) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(fond);
    rec.setOutlineColor(outline);
    rec.setOutlineThickness(10);
}








// Afficher le sivant
void afficherNext (sf::RenderWindow & f, char next) {
    // Texte du "suivant"
    afficherTexte(f, "Suivant : ", "./font/chomsky/Chomsky.woff", 300, 100);


    // 4 Rectangles pour les carrés qui constituent le tetromino
    regctangle r1;
    regctangle r2;
    regctangle r3;
    regctangle r4;


    // En fonction du suivant on initialise différamment
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

    // Dessine les carrés
    f.draw(r1);
    f.draw(r2);
    f.draw(r3);
    f.draw(r4);
}


// Affiche la réserve
void afficherReserve (sf::RenderWindow & f, char reserve, int rotations) {
    // Affiche le texte "Reserve"
    afficherTexte(f, "Reserve : ", "./font/chomsky/Chomsky.woff", 300, 250);

    // 4 Rectangles pour les carrés qui constituent le tetromino
    regctangle r1;
    regctangle r2;
    regctangle r3;
    regctangle r4;


    // En fonction du réservé et de la rotation
    // on initialise différamment
    if (reserve == 'I' and (rotations == 0 or rotations == 2)) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r4, 15, 15, 425, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
    } else if (reserve == 'I' and (rotations == 1 or rotations == 3)) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(0, 245, 255));
        initRect(r4, 15, 15, 375, 400, sf::Color::Transparent, sf::Color(0, 245, 255));
    } else if (reserve == 'O') {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r2, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r3, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 0, 128));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 0, 128));
    } else if (reserve == 'T'  and rotations == 0) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (reserve == 'T'  and rotations == 1) {
        initRect(r1, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (reserve == 'T'  and rotations == 2) {
        initRect(r1, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (reserve == 'T'  and rotations == 3) {
        initRect(r1, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(123, 47, 255));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(123, 47, 255));
    } else if (reserve == 'L' and rotations == 0) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'L' and rotations == 1) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 400, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'L' and rotations == 2) {
        initRect(r1, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'L' and rotations == 3) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'J' and rotations == 0) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r3, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 230, 0));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 230, 0));
    } else if (reserve == 'J' and rotations == 1) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 350, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'J' and rotations == 2) {
        initRect(r1, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 400, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'J' and rotations == 3) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r2, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r3, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(57, 255, 20));
        initRect(r4, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(57, 255, 20));
    } else if (reserve == 'Z' and (rotations == 0 or rotations == 2)) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 400, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
    }  else if (reserve == 'Z' and (rotations == 1 or rotations == 3)) {
        initRect(r1, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 350, 375, sf::Color::Transparent, sf::Color(255, 106, 0));
    } else if (reserve == 'S' and (rotations == 0 or rotations == 2)) {
        initRect(r1, 15, 15, 375, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 400, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
    } else if (reserve == 'S' and (rotations == 1 or rotations == 3)) {
        initRect(r1, 15, 15, 350, 325, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r2, 15, 15, 375, 375, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r3, 15, 15, 350, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
        initRect(r4, 15, 15, 375, 350, sf::Color::Transparent, sf::Color(255, 106, 0));
    }

    // Dessine les carrés
    f.draw(r1);
    f.draw(r2);
    f.draw(r3);
    f.draw(r4);
}





// Afficher la grille
void dessinerGrille (sf::RenderWindow & f, plateau G) {
    regctangle grilleRegctangle;

    // Afficher la grille
    initRect(grilleRegctangle, 240, 490, 10, 10, sf::Color(28,28,46), sf::Color(64,64,96));
    f.draw(grilleRegctangle);

    // Afficher les lignes pour guider le joueur
    for (int i = 1; i<LARGEUR; ++i) {
        for (int j = 1; j<HAUTEUR; ++j) {
            if (G.gr[j][i] == 'C' or G.gr[j][i-1] == 'C') {
                regctangle ligne;
                ligne.setSize({10, static_cast<float>(500-j*25)});
                ligne.setPosition(25*i, j*25);
                ligne.setFillColor(sf::Color(136,136,170));
                f.draw(ligne);
            }
        }
    }

    // Afficher le next
    afficherNext(f, G.next);

    // Afficher la reserve
    afficherReserve(f, G.reserve, G.nbRotationsReserve);

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


// Jouer 1 tour
void jouer(plateau & G, int level, int score, int & interval, sf::RenderWindow & f, bool & peuxReserver) {
    // Calcul de quand est la fin
    std::chrono::time_point<std::chrono::system_clock> fin = std::chrono::system_clock::now() + std::chrono::milliseconds(interval);
    // Renvoie maintenant
    std::chrono::time_point<std::chrono::system_clock> maintenant;

    // Vérifie si on a arrêté la bouble manuellement
    bool stop = false;

    do {
        maintenant = std::chrono::system_clock::now();

        sf::Event event;
        while (f.pollEvent(event)) {
            // Clique sur la croix
            if (event.type == sf::Event::Closed) f.close();
            if (event.type == sf::Event::KeyPressed) {
                // Déplacement à gauche
                if (event.key.code == sf::Keyboard::Left)  deplacer(G.gr, 'G');
                // Déplacement à droite
                else if (event.key.code == sf::Keyboard::Right) deplacer(G.gr, 'D');
                // Déplacement encois en bas
                else if (event.key.code == sf::Keyboard::Enter) {
                        deplacer(G.gr, 'B');
                        placer(G.gr);
                        genereTetromino(G);
                        peuxReserver = true;
                        stop = true;
                // Toune à gauche
                } else if (event.key.code ==  sf::Keyboard::Up) tourner(G, true);
                // Tourne à droite
                else if (event.key.code == sf::Keyboard::Down) tourner(G, false);
                // Reserve le tetromino
                else if (event.key.code == sf::Keyboard::R and peuxReserver) {
                    reserver(G);
                    if (!premiereReserveEffectuee) {
                        premiereReserveEffectuee = true;
                        genereTetromino(G);
                    }
                    peuxReserver = false;
                }
                // Pause
                else if (event.key.code == sf::Keyboard::Space) pause = !pause;
            }
        }

        f.clear(sf::Color(19,19,31));
        afficherTexte(f, "Level : " + std::to_string(level), "./font/chomsky/Chomsky.woff", 300, 20);
        afficherTexte(f, "Score : " + std::to_string(score), "./font/chomsky/Chomsky.woff", 300, 60);
        dessinerGrille(f, G);
        f.display();

    } while (maintenant < fin and !stop);

    // On fais decendre le courant
    if (!stop) deplacer(G.gr, 'b');

    // On génère le prochain si on a touché le sol
    if (collision(G.gr)) {
        placer(G.gr);
        genereTetromino(G);
        peuxReserver = true;
    }

    // On arrête le programme si on a fini
    if (fini(G.gr)) {
        std::cout<<"Vous êtes allez au niveau "<<level<<" avec un score de "<<score<<std::endl;
        f.close();
    }

    // On affiche la grille
    dessinerGrille(f, G);
    f.display();
}



// Afficher le menu
void afficherMenuPause(sf::RenderWindow & f) {
    f.clear(sf::Color(0,0,0));
    sf::Font font;
    font.loadFromFile("./font/chomsky/Chomsky.woff");
    sf::Text text("Pause", font, 200);
    text.setPosition(20, 100);
    f.draw(text);
    f.display();
}



int main () {
    // Initialisation de tout
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(24);

    plateau g;
    initGrille(g.gr);
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    g.next = choix[std::rand()%7];
    genereTetromino(g);

    bool peuxReserver = true;

    int level = 1, Nouveaulevel = 1, nombreDeLignes = 10, score = 0, intervalle = 1000;

    // Boucle de jeu
    while (fenetre.isOpen()) {
        if (pause) {
            // On affiche le menu pause
            afficherMenuPause(fenetre);
            sf::Event event;
            while (fenetre.pollEvent(event)) {
                // Clique sur la croix
                if (event.type == sf::Event::Closed) fenetre.close();
                if (event.type == sf::Event::KeyPressed) {
                    // dépause
                    if (event.key.code == sf::Keyboard::Space) pause = !pause;
                }
            }
        } else 
            // On joue
            jouer(g, level, score, intervalle, fenetre, peuxReserver);

        // ꧁𓊈𒆜 Calcul du score 𒆜𓊉꧂

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
        Nouveaulevel = nombreDeLignes/10;
        if (ligneSupr == 1) score = score + level * 100;
        else if (ligneSupr == 2) score = score + level * 300;
        else if (ligneSupr == 3) score = score + level * 500;
        else if (ligneSupr == 4) score = score + level * 800;
        else if (ligneSupr > 4) score = score + 50*ligneSupr*level;
        if (Nouveaulevel != level) {
            if (level == 0) intervalle = 1000;
            else if (level < 15) intervalle = intervalle * 0.75;
            else intervalle = intervalle * 0.9;
        }
        level = Nouveaulevel;
    }
}