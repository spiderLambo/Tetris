#include "grille.h"

void apparait(grille & G, tetrominoPlace & next) {
	// On place le "next" Tetromino sur le milieu en haut
	next.Positions[0] = 3;
	next.Positions[1] = 20;
	// Le Tetromino courant deviens le "next" Tetromino
	G->courant = next;
}

bool toucher (grille G, int l) {
	for (int z = 0; i < G.nb; ++z) {
		for (int i = 0; i < 4; ++i) {
			if (G->places[z].Positions[1] - i == l) {
				for (int j = 0; j < 4; ++j) {
					if (G->places[z].Positions[0] + j == G->courant.Positions[0])
						if ((G->courant.tetro[0][i]) && (G->places[z].tetro[j][i])) {
							return true;
						}
					} else if (G->places[z].Positions[0] + j == G->courant.Positions[0] + 1) {
						if ((G->courant.tetro[1][i]) && (G->places[z].tetro[j][i])) {
							return true;
						}
					} else if (G->places[z].Positions[0] + j == G->courant.Positions[0] + 2) {
						if ((G->courant.tetro[2][i]) && (G->places[z].tetro[j][i])) {
							return true;
						}
					} else if (G->places[z].Positions[0] + j == G->courant.Positions[0] + 3) {
						if ((G->courant.tetro[3][i]) && (G->places[z].tetro[j][i])) {
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

void verifLigne (grille & G, int l) {
	sum = 0; // sum est le nombre de cube placer sur la ligne l
	for (int z = 0; z < G.nb; z++) {
		for (int i = 0; i < 4; i++) {
			if (G->places[z].Positions[1] - i == l) { //parmis tous les tetrominos placer on regarde pour quel i il est sur la ligne l
				for (int j = 0; j < 4; ++j) {
					if (G->places[z].tetro[j][3-i] == true)
						sum++; // on parcours donc la ligne pour regarder si un cube est placer si oui on fait sum + 1
				}
			}
		}
	}
	if (sum == 10) { // si la sum = 10 alors la ligne est complète il faut la supprimer et placer celle du dessus sur l
		
	}
}
