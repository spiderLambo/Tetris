#include "movTetromino.h"
#include <iostream>


// Tourner le tetromino courant
void tourner (grille & G, bool sens) {
    tournerTetro(G.courant->tetro, sens);
}

// Verifie si une ligne sur le tetromino courant est pleine
bool verifierColonneTetrominoVide (grille G, int i) {
    for (int j = 0; j<4; ++j) {
        if (G.courant->tetro[j][i]) return false;
    }
    return true;
}

std::array <std::array <int, 2>, 4> positionsAVerifierBas (grille G) {
    std::array <std::array <int, 2>, 4> positions;
    for (int i = 0; i<4; ++i) {
        if (!verifierColonneTetrominoVide(G, i)) {
            int j = 3;
            while (j>=0 and !G.courant->tetro[j][i]) {
                --j;
            }
            positions[i] = {i + G.courant->Positions[0], j + G.courant->Positions[1]};
        }
        else positions[i] = {-4, -4};
    }
    return positions;
}

bool peuxDecendre (grille G) {
    std::array <std::array <int, 2>, 4> pos = positionsAVerifierBas(G);
    for (int i = 0; i<4; ++i) {
        if (pos[i][1]>=19 or posEtat(G, pos[i][0], pos[i][1] + 1)) return false;
    }
    return true;
}

std::array <std::array <int, 2>, 4> positionsAVerifierGauche (grille G) {
    std::array <std::array <int, 2>, 4> positions;
    for (int i = 0; i<4; ++i) {
        if (!verifierLigneTetrominoVide(G, i)) {
            int j = 3;
            while (j>=0 and !G.courant->tetro[i][j]) {
                --j;
            }
            positions[i] = {j + G.courant->Positions[0], i + G.courant->Positions[1]};
        }
        else positions[i] = {-4, -4};
    }
    return positions;
}

bool verifierGaucheDeplacer(grille G) {
    std::array <std::array <int, 2>, 4> pos = positionsAVerifierBas(G);
    for (int i = 0; i<4; ++i) {
        if (pos[i][0]>=10 or posEtat(G, pos[i][0], pos[i][1] + 1)) return false;
    }
    return true;
}

// Deplacer le tetromino courant
void deplacer (grille & G, char dir) {
    if (dir == 'D') { // Avance le courant vers la droite
        // Verifie si le courant touche un mur
        if (G.courant->Positions[0] < 6 or verifierColonneTetrominoVide(G, 9-G.courant->Positions[0]))
            ++G.courant->Positions[0];
    } else if (dir == 'G') { // Avance le courant vers la gauche
        // Verifie si le courant touche un mur
        if (G.courant->Positions[0] > 0 or verifierColonneTetrominoVide(G, -G.courant->Positions[0]))
            --G.courant->Positions[0];
    } else if (dir == 'b') { // fait decendre de 1
        if (peuxDecendre(G)) 
            ++G.courant->Positions[1];
    } else if (dir == 'B') {
        while (peuxDecendre(G)) {
            ++G.courant->Positions[1];
        }
    }
}
