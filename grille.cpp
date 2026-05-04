#include "grille.h"
#include <iostream>

bool verifierLigneTetrominoVide (grille & G, int i) {
	for (int j = 0; j<4; ++j) {
        if (G.courant->tetro[i][j]) return false;
    }
    return true;
}

void apparait(grille & G) {
	// Le Tetromino courant deviens le "next" Tetromino
	G.courant = G.next;

	// On place le "next" Tetromino sur le milieu le plus haut possible
	G.next->Positions[0] = 3;
	for (int i = 0; i<4; ++i) {
		if (!verifierLigneTetrominoVide(G, i)) G.next->Positions[1] = -i;
	}
}

bool toucher (grille G) {
    for (int z = 0; z < G.nb; ++z) {
        // pour chaque Tetromino déja placer on va parcourir chaqune de ses cases
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (G.places[z].tetro[y][x]) { // On prend les coordonnés de toutes les cases remplit et placer
                    int px = G.places[z].Positions[0] + x;
                    int py = G.places[z].Positions[1] + y;
		    for (int iy = 0; iy < 4; ++iy) {
                    	for (int ix = 0; ix < 4; ++ix) {
                             if (G.courant->tetro[iy][ix]) { // On prend les cordonnés de toutes les cases remplit du Tetronimo courant
                                int cx = G.courant->Positions[0] + ix;
                                int cy = G.courant->Positions[1] + iy;
                                if (px == cx && py == cy) // test finale
                                    return true;
			     }
			}
		    }
		}
	    }
	}
    }
    return false;
}

void placer (grille &G) {
    tetrominoPlace * T = new tetrominoPlace[G.nb + 1]; // dynamiquement on refait un tableau avec une case de plus
    // on copie les anciens
    for (int i = 0; i < G.nb; ++i) {
        T[i] = G.places[i];
    }
    // ajout du courant a la fin
    T[G.nb] = *G.courant;
    // suppression de l'ancien tableau
    delete[] G.places;
    // remplacer
    G.places = T;
    // incrémenter
    G.nb++;
}

bool verifLigne (grille & G, int l) {
	int sum = 0; // sum est le nombre de cube placer sur la ligne l
	for (int z = 0; z < G.nb; ++z) {
		for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (G.places[z].tetro[y][x]) {
                    int yy = G.places[z].Positions[1] + yy;
                    if (yy == l)
                        sum++;
                }
            }
		}
	}
	if (sum == 10) { // si la sum = 10 alors la ligne est complète il faut la supprimer et placer celle du dessus sur l
		for (int t = 0; t < G.nb; ++t) {
			for (int y = 0; y < 0; ++y) {
				// si le tetromino a une ligne qui correspond a la ligne on supprime la ligne du Tetromino et on fait descendre celle du dessus, sinon si l'ordonnée du Tetromino est plus grande on fait descendre l'ordonnée de 1
				if (G.places[t].Positions[1] + y == l) {
					supprdescLigneTetro(G.places[t].tetro, y);
				} else if (G.places[t].Positions[1] > l) {
					--(G.places[t].Positions[1]);
				}
			}
		}
		return true;
	}
	return false;
}

void reserver (grille & G) {
	tetrominoPlace *tmp = G.courant;
	G.courant = G.next;
	G.next = tmp;
}
