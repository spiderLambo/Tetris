#pragma once
#include <array>

using tetromino = std::array <std::array <bool, 4>, 4>

void tournerTetro (tetromino & tetro, bool sens)