#pragma once
#include <array>
#include "tetrominos.h"

// Tetrominos avec sa position
struct tetrominoPlace {
    tetromino tetro; // le tetromino
    std::array <int, 2> Positions; // sa position
};

// Grille avec les tetrominos placés ou non
struct grille {
    int nb; // nombre de tetromino placer
    tetrominoPlace * places; // tableau dynamique de tetromino placer
    tetrominoPlace * courant; // tetromino jouer
    tetrominoPlace * next; // tetromino de réserve
};

// Initiliser un nouveau courant
void apparait (grille & G);

// Verifie si le tetromino courant dois s'arreter
bool toucher (grille G);

// Place le tetromino courant
void placer (grille & G);

// Supprime une ligne si elle est complete et fait descendre celles du dessus
bool verifLigne (grille & G, int l);

// Change le courant avec la réserve
void reserver (grille & G);
