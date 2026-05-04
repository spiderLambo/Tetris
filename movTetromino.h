#pragma once
#include "grille.h"

// Tourner le tetromino courant
void tourner (grille & G, bool sens);

// Verifie si une colonne sur le tetromino courant est pleine
bool verifierColonneTetrominoVide (grille & G, int i);

// Deplacer le tetromino courant
void deplacer (grille & G, char dir);
