#pragma once
#include <array>
#include "tetrominos.h"

// Tetrominos avec sa position
struct tetrominoPlace {
    tetromino tetro;
    std::array <int, 2> Positions;
};

// Grille avec les tetrominos placés ou non
struct grille {
    tetrominoPlace * places;
    tetrominoPlace * courant;
};

// Initiliser un nouveau courant
void apparait (grille & G);

// Verifie si le tetromino courant dois s'arreter
bool toucher (grille G);

// Supprime une ligne si elle est complete
void verifLigne (grille & G);

