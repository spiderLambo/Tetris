#include "grille.h"

void apparait(grille & G, tetrominoPlace & next) {
	// On place le "next" Tetromino sur le milieu en haut
	next.Positions[0] = 3;
	next.Positions[1] = 20;
	// Le Tetromino courant deviens le "next" Tetromino
	G->courant = next;
}

bool toucher (grille G, int l) {
    for (int z = 0; z < G.nb; ++z) {
        // pour chaque Tetromino déja placer on va parcourir chaqune de ses cases
        for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (G->places[z].tetro[x][y]) { // On prend les coordonnés de toutes les cases remplit et placer
                    int px = G->places[z].tetro[0] + x;
                    int py = G->places[z].tetro[1] + y;
                    if (py = l) { 
                        // si l'ordonnée y est correspond bien a la ligne, on va parcourir chaqune des cases du courant
                        for (int iy = 0; iy < 4; ++iy) {
                            for (int ix = 0; ix < 4; ++ix) {
                                if (G.courant.tetro[iy][ix]) { // On prend les cordonnés de toutes les cases remplit du Tetronimo courant
                                    int cx = G->courant.Position[0] + ix;
                                    int yx = G->courant.Position[1] + iy;
                                    if (px == cx && py == cy) // test finale
                                        return true;
                                }
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
        T[i] = G->places[i];
    }
    // ajout du courant a la fin
    T[G.nb] = G->courant;
    // suppression de l'ancien tableau
    delete[] G->places;
    // remplacer
    G->places = T;
    // incrémenter
    G.nb++;
}

void verifLigne (grille & G, int l) {
	sum = 0; // sum est le nombre de cube placer sur la ligne l
	for (int z = 0; z < G.nb; ++z) {
		for (int y = 0; y < 4; ++y) {
            for (int x = 0; x < 4; ++x) {
                if (G->places[z].tetro[x][y]) {
                    int yy = G->places[z].Positions[1] + yy;
                    if (yy == l)
                        sum++;
                }
            }
		}
	}
	if (sum == 10) { // si la sum = 10 alors la ligne est complète il faut la supprimer et placer celle du dessus sur l
		
	}
}
