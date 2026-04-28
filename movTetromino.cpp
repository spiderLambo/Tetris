#include "movTetromino.h"
#include "tetrominos.cpp"

// Tourner le tetromino courant
void tourner (grille & G, bool sens) {
    tournerTetro(G.courant->tetro, sens);
}

// Verifie si une ligne sur le tetromino courant est pleine
bool verifierColonneTetrominoVide (grille & G, int i) {
    for (int j = 0; j<4; ++j) {
        if (G.courant->tetro[j][i]) return false;
    }
    return true;
}

// Deplacer le tetromino courant
void deplacer (grille & G, char dir) {
    if (dir == 'D') { // Avance le courant vers la droite
        // Verifie si le courant touche un mur
        if (G.courant->Positions[0] < 6 or verifierColonneTetrominoVide(G, 9-G.courant->Positions[0]))
            G.courant->Positions[0] = G.courant->Positions[0] + 1;
    } else if (dir == 'G') { // Avance le courant vers la gauche
        // Verifie si le courant touche un mur
        if (G.courant->Positions[0] > 0 or verifierColonneTetrominoVide(G, -G.courant->Positions[0]))
            --G.courant->Positions[0];
    }else if (dir == 'B') { // Avance le courant vers le bas
        // Verifie si le courant peux decendre
        if (!toucher(G))
            ++G.courant->Positions[1];
    }
}