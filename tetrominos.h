#pragma once
#include <array>

using tetromino = std::array <std::array <bool, 4>, 4>;

// Initialise un tetromino
void genereTetro (tetromino & tetro, char type);

void tournerTetro (tetromino & tetro, bool sens);