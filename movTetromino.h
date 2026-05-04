#pragma once
#include "grille.h"

// Tourner le tetromino courant
void tourner (grille & G, bool sens);

// Verifie si une colonne sur le tetromino courant est pleine
bool verifierColonneTetrominoVide (grille G, int i);

// Renvoie les positions a verifier
std::array <std::array <int, 2>, 4> positionsAVerifier (grille G);

// Verifie si le tetromino courant peux decendre
bool peuxDecendre (grille G);

// Deplacer le tetromino courant
void deplacer (grille & G, char dir);
