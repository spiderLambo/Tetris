#include "grille.h"

void initGrille (grille & g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            g[i][j] = ' ';
        }
    }
}

void afficheGrille (grille g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            std::cout<<g[i][j]<<'|';
        } std::cout<<std::endl;
    }
}

void apparait (grille & g, char type) {
    if (type == 'I') {
        g[0][3] = 'C';
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
    } else if (type == 'O') {
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[1][4] = 'C';
        g[1][5] = 'C';
    } else if (type == 'T') {
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][5] = 'C';
    } else if (type == 'L') {
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][4] = 'C';
    } else if (type == 'J') {
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][6] = 'C';
    } else if (type == 'Z') {
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[1][5] = 'C';
        g[1][6] = 'C';
    } else if (type == 'S') {
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][4] = 'C';
        g[1][5] = 'C';
    }
}

void genereTetromino (grille & g) {
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    apparait(g, choix[std::rand()%7]);
}

void placer (grille & g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (g[i][j] == 'C') g[i][j] = 'P';
        }
    }
}

bool peuxGauche (grille g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        int j = 0;
        while (j<LARGEUR - 1 and g[i][j] != 'C') {
            ++j;
        }
        if (g[i][j-1] != ' ') return false;
    }
    return true;
}

bool peuxDroite (grille g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        int j = LARGEUR-1;
        while (j>0 and g[i][j] != 'C') {
            --j;
        }
        if (g[i][j+1] != ' ' or j == LARGEUR-1) return false;
    }
    return true;
}

bool peuxDecendre (grille g) {
    for (int j = 0; j<LARGEUR; ++j) {
        int i = HAUTEUR - 1;
        while (i>0 and g[i][j] != 'C') {
            --i;
        }
        if (g[i+1][j] != ' ') return false;
    }
    return true;
}

void gauche (grille & g) {
    for (int j = 0; j<LARGEUR-1; ++j) {
        for (int i = 0; i<HAUTEUR-1;++i) {
            if (g[i][j+1] == 'C') {
                g[i][j+1] = ' ';
                g[i][j] = 'C';
            }
        }
    }
}

void droite (grille & g) {
    for (int j = LARGEUR-1; j>0; --j) {
        for (int i = 0; i<HAUTEUR-1; ++i) {
            if (g[i][j-1] == 'C') {
                g[i][j-1] = ' ';
                g[i][j] = 'C';
            }
        }
    }
}

void descendre (grille & g) {
    for (int i = HAUTEUR-1; i>0; --i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (g[i-1][j] == 'C') {
                g[i][j] = 'C';
                g[i-1][j] = ' ';
            }
        } 
    }
}

void deplacer (grille & g, char dir) {
    if (dir == 'G' and peuxGauche(g)) {
        gauche(g);
    } else if (dir == 'D' and peuxDroite(g)) {
        droite(g);
    } else if (dir == 'b' and peuxDecendre(g)) {
        descendre(g);
    } else if (dir == 'B') {
        while (peuxDecendre(g)) {
            descendre(g);
        }
    }
}

bool collision (grille g) {
    return !peuxDecendre(g);
}