#include "serveur.h"

#include <arpa/inet.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>

// ─────────────────────────────────────────────────────────────
// FICHIERS IA
// ─────────────────────────────────────────────────────────────

// Affiche du texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y) {
    sf::Font font;
    if (font.openFromFile(police)) {
        sf::Text text(font, texte, 25);
        text.setPosition({x, y});
        f.draw(text);
    }
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
                ligne.setPosition({static_cast<float>(25*i), static_cast<float>(j*25)});
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

// ─────────────────────────────────────────────────────────────
// LOGIQUE RESEAU / SYNCHRONISATION (CORRIGÉ)
// ─────────────────────────────────────────────────────────────

bool ecrire_grille(const std::string& path, const plateau& p) {
    std::ofstream f(path);
    if (!f) return false;

    f << p.nextPrecedent << "\n"; 
    f << p.next << "\n";          
    
    if (p.reserve == ' ' || p.reserve == '\0') f << "..........";
    else f << p.reserve;
    f << "\n";

    for (int i = 0; i < HAUTEUR; ++i) {
        for (int j = 0; j < LARGEUR; ++j) {
            if (p.gr[i][j] != ' ' && p.gr[i][j] != 'C')
                f << 'P';
            else
                f << '.';
        }
        f << "\n";
    }
    return true;
}

bool lire_coup(const std::string& path, Action& a) {
    std::ifstream f(path);
    if (!f) return false;

    int use_res, rot, col;
    if (!(f >> use_res >> rot >> col))
        return false;

    a.rotation = rot;
    a.colonne = col;
    a.reserve = (use_res == 1);

    return true;
}

int creer_socket_serveur() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1) {
        std::cerr << "socket erreur\n";
        return -1;
    }

    int opt = 1;
    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) == -1) {
        std::cerr << "bind erreur\n";
        close(fd);
        return -1;
    }

    if (listen(fd, 1) == -1) {
        std::cerr << "listen erreur\n";
        close(fd);
        return -1;
    }
    return fd;
}

int accepter_client(int servfd) {
    sockaddr_storage cliaddr{};
    socklen_t len = sizeof(cliaddr);
    int clifd = accept(servfd, reinterpret_cast<sockaddr*>(&cliaddr), &len);
    if (clifd == -1)
        std::cerr << "accept erreur\n";
    return clifd;
}

bool envoyer_go(int clifd) {
    const char* msg = "GO\n";
    if (send(clifd, msg, strlen(msg), 0) <= 0)
        return false;

    // Attente synchrone du message de retour de l'IA (OK\n)
    char buf[64];
    int r = recv(clifd, buf, sizeof(buf)-1, 0);
    if (r <= 0) return false;

    buf[r] = 0;
    return true;
}

bool tour_de_jeu(
    int clifd,
    const plateau& p,
    const std::string& chemin_grille,
    const std::string& chemin_coup,
    Action& action_calculee
) {
    if (!ecrire_grille(chemin_grille, p))
        return false;

    if (!envoyer_go(clifd))
        return false;

    if (!lire_coup(chemin_coup, action_calculee))
        return false;

    return true;
}

void jouer(
    plateau& G,
    int level,
    int score,
    int& interval,
    sf::RenderWindow& f,
    bool& peuxReserver,
    const Action& coup
) {
    for (int i = 0; i < coup.rotation; ++i)
        tourner(G, true);

    int xActuel = 0;
    for (int j = 0; j < LARGEUR; ++j) {
        bool trouve = false;
        for (int i = 0; i < HAUTEUR; ++i) {
            if (G.gr[i][j] == 'C') {
                xActuel = j;
                trouve = true;
                break;
            }
        }
        if (trouve) break;
    }

    int diff = coup.colonne - xActuel;
    if (diff > 0)
        for (int i = 0; i < diff; i++) deplacer(G.gr, 'D');
    else
        for (int i = 0; i < -diff; i++) deplacer(G.gr, 'G');

    deplacer(G.gr, 'B');
    placer(G.gr);

    for (int i = 0; i < HAUTEUR; ++i) {
        if (peuxSupprimerLigne(G.gr, i))
            supprimerLigne(G.gr, i);
    }

    genereTetromino(G);

    f.clear(sf::Color(19, 19, 31));

    afficherTexte(f, "Level : " + std::to_string(level), "./font/chomsky/Chomsky.woff", 300, 20);
    afficherTexte(f, "Score : " + std::to_string(score), "./font/chomsky/Chomsky.woff", 300, 60);

    dessinerGrille(f, G);
    f.display();

    if (fini(G.gr)) {
        std::cout << "GAME OVER\n";
        f.close();
    }
}

int main() {
    std::srand(std::time(nullptr));
    const std::string CHEMIN_GRILLE = "grille.txt";
    const std::string CHEMIN_COUP   = "coup.txt";

    int servfd = creer_socket_serveur();
    if (servfd == -1) return 1;

    std::cout << "Serveur attente...\n";
    system("python3 client.py &");

    int clifd = accepter_client(servfd);
    if (clifd == -1) {
        close(servfd);
        return 1;
    }

    std::cout << "Client connecté\n";

    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(24);

    plateau g;
    initGrille(g.gr);

    std::array<char, 7> choix = {'I','O','T','L','J','S','Z'};
    g.next = choix[std::rand()%7];
    g.reserve = ' ';

    genereTetromino(g);
    bool peuxReserver = true;

    int level = 1;
    int score = 0;
    int intervalle = 1000;

    while (fenetre.isOpen()) {
        while (const std::optional<sf::Event> event = fenetre.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                fenetre.close();
        }

        Action coup{};
        if (!tour_de_jeu(clifd, g, CHEMIN_GRILLE, CHEMIN_COUP, coup)) {
            std::cout << "connexion perdue\n";
            break;
        }

        std::cout << "rotation = " << coup.rotation << " col = " << coup.colonne << "\n";
        jouer(g, level, score, intervalle, fenetre, peuxReserver, coup);
        afficheGrille(g.gr);
    }

    close(clifd);
    close(servfd);
    return 0;
}