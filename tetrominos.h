#pragma once
#include <array>



// Initialise un tetromino
void genereTetro (tetromino & tetro, char type);

// Tourne un tetromino
// False : Droite
// True : Gauche
void tournerTetro (tetromino & tetro, bool sens);