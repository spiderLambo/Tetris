#include "grille.h"

// Procédure pour initialiser une grille
void initGrille (grille & g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            g[i][j] = ' ';
        }
    }
}

// Procédure de débug qui affiche une grille
void afficheGrille (grille g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            std::cout<<g[i][j]<<'|';
        } std::cout<<std::endl;
    }
}

// Faire apparaitre un tetromini d'un certain type
void apparait (grille & g, char type) {
    if (type == 'I') {
        // . . . .
        // - - - -
        g[0][3] = 'C';
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
    } else if (type == 'O') {
        // . - - .
        // . - - .
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[1][4] = 'C';
        g[1][5] = 'C';
    } else if (type == 'T') {
        // . - - -
        // . . - .
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][5] = 'C';
    } else if (type == 'L') {
        // . - - -
        // . - . .
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][4] = 'C';
    } else if (type == 'J') {
        // . - - -
        // . . . -
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][6] = 'C';
    } else if (type == 'Z') {
        // . - - .
        // . . - -
        g[0][4] = 'C';
        g[0][5] = 'C';
        g[1][5] = 'C';
        g[1][6] = 'C';
    } else if (type == 'S') {
        // . . - -
        // . - - .
        g[0][5] = 'C';
        g[0][6] = 'C';
        g[1][4] = 'C';
        g[1][5] = 'C';
    }

    // Eviter les bugs de rotation avec le plafond
    deplacer(g, 'b');
}




// Choisis un tetromino au hasard
void genereTetromino (plateau & g) {
    std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    g.nextPrecedent = g.next;
    apparait(g.gr, g.next);
    g.next = choix[std::rand()%7];
    g.nbRotations = 0;
}
// /!\ Version de debug /!
// void genereTetromino (plateau & g) {
//     g.nextPrecedent = g.next;
//     apparait(g.gr, g.next);
//     g.next = 'I';
// }




// Place le tetromino courant
void placer (grille & g) {
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (g[i][j] == 'C') g[i][j] = 'P';
        }
    }
}





// Verifie si on peux déplacer le courant a gauche
bool peuxGauche(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (j == 0 or g[i][j-1] == 'P'))
                    return false;
    return true;
}

// Verifie si on peux déplacer le courant a droite
bool peuxDroite(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (j == LARGEUR-1 or g[i][j+1] == 'P'))
                    return false;
    return true;
}

// Verifie si on peux déplacer le courant en bas
bool peuxDecendre(grille g) {
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (g[i][j] == 'C' and (i == HAUTEUR-1 or g[i+1][j] == 'P'))
                    return false;
    return true;
}



// Déplace le courant a gauche
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

// Déplace le courant a droite
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

// Déplace le courant en bas
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



// Déplace le courant dans la direction donnée
void deplacer (grille & g, char dir) {
    if (dir == 'G' and peuxGauche(g)) {
        gauche(g);
    } else if (dir == 'D' and peuxDroite(g)) {
        droite(g);
    } else if (dir == 'b' and peuxDecendre(g)) {
        descendre(g);
    } else if (dir == 'B') {
        // On rajoute decendre au max
        while (peuxDecendre(g)) {
            descendre(g);
        }
    }
}







// Verifie si il y a une collision avec le sol
bool collision (grille g) {
    // Si on ne peux pas décendre, on touche le sol
    return !peuxDecendre(g); 
}









// On fais tourner a  gauche le courant au verifiant au cas par cas
void tournerGauche (plateau & G, int x, int y) {
    // On actualise la variable au cas où la piece vas à la réserve
    G.nbRotations = (G.nbRotations + 1) % 4;


    //  ⊹₊˚‧︵‿₊୨ Les pièces ୧₊‿︵‧˚₊⊹
    // ------- I -------
    if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y][x+3]=='C') {
        G.gr[y][x]=' '; G.gr[y][x+2]=' '; G.gr[y][x+3]=' ';
        G.gr[y-1][x+1]='C'; G.gr[y+1][x+1]='C'; G.gr[y+2][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+3][x]=='C') {
        G.gr[y][x]=' '; G.gr[y+2][x]=' '; G.gr[y+3][x]=' ';
        G.gr[y+1][x-1]='C'; G.gr[y+1][x+1]='C'; G.gr[y+1][x+2]='C';

    
    // ------- T -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y][x]=' ';
        G.gr[y-1][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y+2][x]=' ';
        G.gr[y+1][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y+1][x+1]=' ';
        G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+2][x]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y][x]=' ';
        G.gr[y+1][x+1]='C';



    // ------- L -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+2]=' ';G.gr[y+1][x]=' ';
        G.gr[y-1][x+1]='C';G.gr[y+1][x+1]='C';G.gr[y+1][x+2]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+2][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';G.gr[y][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x-2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x]=' ';G.gr[y+1][x-2]=' ';
        G.gr[y][x-2]='C';G.gr[y][x-1]='C';G.gr[y+2][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+2][x+1]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y+1][x]='C';G.gr[y+2][x]='C';G.gr[y+1][x+2]='C';



    // ------- J -------
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+2][x-1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x]=' ';G.gr[y+2][x-1]=' ';
        G.gr[y][x-1]='C';G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x+2]=' ';G.gr[y+1][x]=' ';
        G.gr[y][x+1]='C';G.gr[y+2][x+1]='C';G.gr[y][x+2]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';G.gr[y+2][x]=' ';
        G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';G.gr[y+2][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x+2]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+2]=' ';G.gr[y+1][x+2]=' ';
        G.gr[y-1][x+1]='C';G.gr[y+1][x+1]='C';G.gr[y+1][x]='C';



    // ------- Z -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x+2]=' ';
        G.gr[y+1][x]='C';G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+2][x-1]=='C') {
        G.gr[y+1][x-1]=' ';G.gr[y+2][x-1]=' ';
        G.gr[y+1][x+1]='C';G.gr[y][x-1]='C';



    // ------- S -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';
        G.gr[y][x-1]='C';G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+2][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y][x+1]='C';G.gr[y][x+2]='C';
    }
}

// On fais tourner a droite le courant au verifiant au cas par cas
void tournerDroite (plateau & G, int x, int y) {
    // On actualise la variable au cas où la piece vas à la réserve
    G.nbRotations = (G.nbRotations + 3) % 4;


    //  ⊹₊˚‧︵‿₊୨ Les pièces ୧₊‿︵‧˚₊⊹
    // ------- I -------
    if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y][x+3]=='C') {
        G.gr[y][x]=' '; G.gr[y][x+2]=' '; G.gr[y][x+3]=' ';
        G.gr[y-1][x+1]='C'; G.gr[y+1][x+1]='C'; G.gr[y+2][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+3][x]=='C') {
        G.gr[y][x]=' '; G.gr[y+2][x]=' '; G.gr[y+3][x]=' ';
        G.gr[y+1][x-1]='C'; G.gr[y+1][x+1]='C'; G.gr[y+1][x+2]='C';



    // ------- T -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y][x+2]=' ';
        G.gr[y-1][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y][x]=' ';
        G.gr[y+1][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y+1][x-1]=' ';
        G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+2][x]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y+2][x]=' ';
        G.gr[y+1][x+1]='C';



    // ------- L -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+2]=' ';G.gr[y+1][x]=' ';
        G.gr[y-1][x+1]='C';G.gr[y+1][x+1]='C';G.gr[y-1][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+2][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';G.gr[y+2][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x-2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x]=' ';G.gr[y+1][x-2]=' ';
        G.gr[y][x-1]='C';G.gr[y+2][x]='C';G.gr[y+2][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+2][x+1]=='C' && G.gr[y+1][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y+1][x]='C';G.gr[y][x+2]='C';G.gr[y+1][x+2]='C';



    // ------- J -------
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y+2][x-1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x]=' ';G.gr[y+2][x-1]=' ';
        G.gr[y+2][x+1]='C';G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x+2]=' ';G.gr[y+1][x]=' ';
        G.gr[y][x+1]='C';G.gr[y+2][x+1]='C';G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+2][x]=='C' && G.gr[y][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';G.gr[y+2][x]=' ';
        G.gr[y+1][x-1]='C';G.gr[y+1][x+1]='C';G.gr[y][x-1]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x+2]=='C' && G.gr[y][x+1]=='C' && G.gr[y][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+2]=' ';G.gr[y+1][x+2]=' ';
        G.gr[y-1][x+1]='C';G.gr[y+1][x+1]='C';G.gr[y-1][x+2]='C';



    // ------- Z -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+1][x+2]=='C') {
        G.gr[y][x]=' ';G.gr[y+1][x+2]=' ';
        G.gr[y+1][x]='C';G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+2][x-1]=='C') {
        G.gr[y+1][x-1]=' ';G.gr[y+2][x-1]=' ';
        G.gr[y+1][x+1]='C';G.gr[y][x-1]='C';



    // ------- S -------
    } else if (G.gr[y][x]=='C' && G.gr[y][x+1]=='C' && G.gr[y+1][x-1]=='C' && G.gr[y+1][x]=='C') {
        G.gr[y][x]=' ';G.gr[y][x+1]=' ';
        G.gr[y][x-1]='C';G.gr[y+2][x]='C';
    } else if (G.gr[y][x]=='C' && G.gr[y+1][x]=='C' && G.gr[y+1][x+1]=='C' && G.gr[y+2][x+1]=='C') {
        G.gr[y][x]=' ';G.gr[y+2][x+1]=' ';
        G.gr[y][x+1]='C';G.gr[y][x+2]='C';
    }
}

// On tourne la pièce
void tourner (plateau & g, bool sens) {
    grille copie = g.gr;

    // On compte le nombre de courant
    bool stop = false;
    int i = 0;
    while (i < HAUTEUR && !stop) {
        int j = 0;
        while (j < LARGEUR && !stop) {
            if (g.gr[i][j] == 'C') {
                stop = true;
                // On tourne Le courant
                if (sens) tournerGauche(g, j, i);
                else tournerDroite(g, j, i);
            }
            ++j;
        }
        ++i;
    }

    // On compte le nombre de courants sur la grille a avant et apès la rotation
    // privée de la 1ère ligne (au cas ou le courant aurait traversé la grille)
    int nbCAvant = 0, nbCApres = 0;
    for (int i = 0; i < HAUTEUR; ++i) {
        for (int j = 1; j < LARGEUR; ++j) {
            if (copie[i][j] == 'C') ++nbCAvant;
            if (g.gr[i][j] == 'C')  ++nbCApres;
        }
    }

    // Si on a pas le même nombre de courant avant et après
    // On annule la rotation
    if (nbCAvant != nbCApres) {
        g.gr = copie;
    }
}




// Verifie si on peux supprimer la ligne l
bool peuxSupprimerLigne (grille G, int l) {
    for (int i = 0; i<LARGEUR; ++i) {
        if (G[l][i] != 'P') return false;
    }
    return true;
}

// Supprime la ligne l
void supprimerLigne (grille & G, int l) {
    // On fais decendre tout ce qui est au dessus de l
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





// Verifie si on arrete le programme
bool fini (grille G) {
    // On vérifie qu'il n'y a aucun placé
    for (int i = 0; i<LARGEUR; ++i) {
        if (G[0][i] != ' ') return true;
    }
    return false;
}



// On reserve le courant
void reserver (plateau & G) {
    // On retire le courant
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (G.gr[i][j] == 'C') {
                G.gr[i][j] = ' ';
            }
        }
    }

    // On effectue l'échange
    apparait(G.gr, G.reserve);
    for (int i = 0; i<G.nbRotationsReserve; ++i) {
        tourner(G, true);
    }
    G.nbRotationsReserve = G.nbRotations;
    G.reserve = G.nextPrecedent;
}