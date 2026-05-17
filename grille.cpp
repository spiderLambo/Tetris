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

void genereTetromino (plateau & g) {
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    g.nextPrecedent = g.next;
    apparait(g.gr, g.next);
    g.next = choix[std::rand()%7];
}

// Version de debug
// void genereTetromino (plateau & g) {
//     g.nextPrecedent = g.next;
//     apparait(g.gr, g.next);
//     g.next = 'I';
// }

void placer (grille & g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (g[i][j] == 'C') g[i][j] = 'P';
        }
    }
}

bool peuxGauche(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (j == 0 or g[i][j-1] == 'P'))
                    return false;
    return true;
}

bool peuxDroite(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (j == LARGEUR-1 or g[i][j+1] == 'P'))
                    return false;
    return true;
}

bool peuxDecendre(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (i == HAUTEUR-1 or g[i+1][j] == 'P'))
                    return false;
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

void tournerGauche (grille & g, int x, int y) {
    // ------- I -------
    if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y][x+3]=='C') {
        g[y][x]=' '; g[y][x+2]=' '; g[y][x+3]=' ';
        g[y-1][x+1]='C'; g[y+1][x+1]='C'; g[y+2][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+3][x]=='C') {
        g[y][x]=' '; g[y+2][x]=' '; g[y+3][x]=' ';
        g[y+1][x-1]='C'; g[y+1][x+1]='C'; g[y+1][x+2]='C';


    // ------- T -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y+1][x+1]=='C') {
        g[y][x]=' ';
        g[y-1][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+1][x+1]=='C') {
        g[y+2][x]=' ';
        g[y+1][x-1]='C';
    } else if (g[y][x]=='C' && g[y+1][x-1]=='C' && g[y+1][x+1]=='C' && g[y+1][x]=='C') {
        g[y+1][x+1]=' ';
        g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x-1]=='C' && g[y+2][x]=='C' && g[y+1][x]=='C') {
        g[y][x]=' ';
        g[y+1][x+1]='C';


    // ------- L -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y+1][x]=='C') {
        g[y][x]=' ';g[y][x+2]=' ';g[y+1][x]=' ';
        g[y-1][x+1]='C';g[y+1][x+1]='C';g[y+1][x+2]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+2][x+1]=='C') {
        g[y][x]=' ';g[y+2][x]=' ';g[y+2][x+1]=' ';
        g[y+1][x-1]='C';g[y+1][x+1]='C';g[y][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x-1]=='C' && g[y+1][x-2]=='C') {
        g[y][x]=' ';g[y+1][x]=' ';g[y+1][x-2]=' ';
        g[y][x-2]='C';g[y][x-1]='C';g[y+2][x-1]='C';
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+2][x+1]=='C' && g[y+1][x+1]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';g[y+2][x+1]=' ';
        g[y+1][x]='C';g[y+2][x]='C';g[y+1][x+2]='C';


    // ------- J -------
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+2][x-1]=='C') {
        g[y][x]=' ';g[y+2][x]=' ';g[y+2][x-1]=' ';
        g[y][x-1]='C';g[y+1][x-1]='C';g[y+1][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x+1]=='C' && g[y+1][x+2]=='C') {
        g[y][x]=' ';g[y+1][x+2]=' ';g[y+1][x]=' ';
        g[y][x+1]='C';g[y+2][x+1]='C';g[y][x+2]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y][x+1]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';g[y+2][x]=' ';
        g[y+1][x-1]='C';g[y+1][x+1]='C';g[y+2][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x+2]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C') {
        g[y][x]=' ';g[y][x+2]=' ';g[y+1][x+2]=' ';
        g[y-1][x+1]='C';g[y+1][x+1]='C';g[y+1][x]='C';


    // ------- Z -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+1][x+1]=='C' && g[y+1][x+2]=='C') {
        g[y][x]=' ';g[y+1][x+2]=' ';
        g[y+1][x]='C';g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x-1]=='C' && g[y+2][x-1]=='C') {
        g[y+1][x-1]=' ';g[y+2][x-1]=' ';
        g[y+1][x+1]='C';g[y][x-1]='C';


    // ------- S -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+1][x-1]=='C' && g[y+1][x]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';
        g[y][x-1]='C';g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x+1]=='C' && g[y+2][x+1]=='C') {
        g[y][x]=' ';g[y+2][x+1]=' ';
        g[y][x+1]='C';g[y][x+2]='C';
    }
}

void tournerDroite (grille & g, int x, int y) {
    // ------- I -------
    if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y][x+3]=='C') {
        g[y][x]=' '; g[y][x+2]=' '; g[y][x+3]=' ';
        g[y-1][x+1]='C'; g[y+1][x+1]='C'; g[y+2][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+3][x]=='C') {
        g[y][x]=' '; g[y+2][x]=' '; g[y+3][x]=' ';
        g[y+1][x-1]='C'; g[y+1][x+1]='C'; g[y+1][x+2]='C';


    // ------- T -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y+1][x+1]=='C') {
        g[y][x+2]=' ';
        g[y-1][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+1][x+1]=='C') {
        g[y][x]=' ';
        g[y+1][x-1]='C';
    } else if (g[y][x]=='C' && g[y+1][x-1]=='C' && g[y+1][x+1]=='C' && g[y+1][x]=='C') {
        g[y+1][x-1]=' ';
        g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x-1]=='C' && g[y+2][x]=='C' && g[y+1][x]=='C') {
        g[y+2][x]=' ';
        g[y+1][x+1]='C';



    // ------- L -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C' && g[y+1][x]=='C') {
        g[y][x]=' ';g[y][x+2]=' ';g[y+1][x]=' ';
        g[y-1][x+1]='C';g[y+1][x+1]='C';g[y-1][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+2][x+1]=='C') {
        g[y][x]=' ';g[y+2][x]=' ';g[y+2][x+1]=' ';
        g[y+1][x-1]='C';g[y+1][x+1]='C';g[y+2][x-1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x-1]=='C' && g[y+1][x-2]=='C') {
        g[y][x]=' ';g[y+1][x]=' ';g[y+1][x-2]=' ';
        g[y][x-1]='C';g[y+2][x]='C';g[y+2][x-1]='C';
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+2][x+1]=='C' && g[y+1][x+1]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';g[y+2][x+1]=' ';
        g[y+1][x]='C';g[y][x+2]='C';g[y+1][x+2]='C';


    // ------- J -------
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y+2][x-1]=='C') {
        g[y][x]=' ';g[y+2][x]=' ';g[y+2][x-1]=' ';
        g[y+2][x+1]='C';g[y+1][x-1]='C';g[y+1][x+1]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x+1]=='C' && g[y+1][x+2]=='C') {
        g[y][x]=' ';g[y+1][x+2]=' ';g[y+1][x]=' ';
        g[y][x+1]='C';g[y+2][x+1]='C';g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+2][x]=='C' && g[y][x+1]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';g[y+2][x]=' ';
        g[y+1][x-1]='C';g[y+1][x+1]='C';g[y][x-1]='C';
    } else if (g[y][x]=='C' && g[y+1][x+2]=='C' && g[y][x+1]=='C' && g[y][x+2]=='C') {
        g[y][x]=' ';g[y][x+2]=' ';g[y+1][x+2]=' ';
        g[y-1][x+1]='C';g[y+1][x+1]='C';g[y-1][x+2]='C';


    // ------- Z -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+1][x+1]=='C' && g[y+1][x+2]=='C') {
        g[y][x]=' ';g[y+1][x+2]=' ';
        g[y+1][x]='C';g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x-1]=='C' && g[y+2][x-1]=='C') {
        g[y+1][x-1]=' ';g[y+2][x-1]=' ';
        g[y+1][x+1]='C';g[y][x-1]='C';


    // ------- S -------
    } else if (g[y][x]=='C' && g[y][x+1]=='C' && g[y+1][x-1]=='C' && g[y+1][x]=='C') {
        g[y][x]=' ';g[y][x+1]=' ';
        g[y][x-1]='C';g[y+2][x]='C';
    } else if (g[y][x]=='C' && g[y+1][x]=='C' && g[y+1][x+1]=='C' && g[y+2][x+1]=='C') {
        g[y][x]=' ';g[y+2][x+1]=' ';
        g[y][x+1]='C';g[y][x+2]='C';
    }
}

void tourner (grille & g, bool sens) {
    bool stop = false;
    int i = 0;
    while (i<HAUTEUR && !stop) {
        int j = 0;
        while (j<LARGEUR && !stop) {
            if (g[i][j] == 'C') {
                stop = true;
                if (sens) tournerGauche(g, j, i);
                else tournerDroite(g, j, i);
            }
            ++j;
        }
        ++i;
    }
}

bool peuxSupprimerLigne (grille G, int l) {
    for (int i = 0; i<LARGEUR; ++i) {
        if (G[l][i] != 'P') return false;
    }
    return true;
}

void supprimerLigne (grille & G, int l) {
    for (int i = l; i>0; --i) {
        for (int j = 0; j<LARGEUR; ++j) {
            G[i][j] = G[i-1][j];
        }
    }

    // Vider la 1ere ligne
    for (int j = 0; j<LARGEUR; ++j) {
        G[0][j] = ' ';
    }
}

bool fini (grille G) {
    for (int i = 0; i<LARGEUR; ++i) {
        if (G[0][i] == 'P') return true;
    }
    return false;
}

void reserver (plateau & G) {
    // Retire le courant
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (G.gr[i][j] == 'C') {
                G.gr[i][j] = ' ';
            }
        }
    }

    // effectue l'échange
    apparait(G.gr, G.reserve);
    G.reserve = G.nextPrecedent;
}