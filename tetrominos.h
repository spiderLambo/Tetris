#pragma once
#include <array>

using tetromino = std::array <std::array <bool, 4>, 4>;

// Initialise un tetromino
void genereTetro (tetromino & tetro, char type);

// Tourne un tetromino
// False : Droite
// True : Gauche
void tournerTetro (tetromino & tetro, bool sens);