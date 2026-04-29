#pragma once
#include <array>
#include "tetrominos.h"

// Tetrominos avec sa position
struct tetrominoPlace {
    tetromino tetro; // le tetromino
    std::array <unsigned int, 2> Positions; // sa position
};

// Grille avec les tetrominos placés ou non
struct grille {
    int nb; // nombre de tetromino placer
    tetrominoPlace * places; // tableau dynamique de tetromino placer
    tetrominoPlace * courant; // tetromino
};

// Initiliser un nouveau courant
void apparait (grille & G, tetrominoPlace & next);

// Verifie si le tetromino courant dois s'arreter
bool toucher (grille G, int l);

// Place le tetromino courant
void placer (grille & G);

// Supprime une ligne si elle est complete et fait descendre celles du dessus
bool verifLigne (grille & G, int l);

