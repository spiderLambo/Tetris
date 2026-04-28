#include "tetrominos.h"
#include <iostream>


// Initialise un tetromino
void genereTetro (tetromino & tetro, char type) {
    // Tetromino vide
    for (int i = 0; i<4; ++i) {
        tetro[0][i] = false;
        tetro[1][i] = false;
        tetro[2][i] = false;
        tetro[3][i] = false;
    }
    if (type == 'I') {
        // - - - -
        // . . . .
        for (int i = 0; i<4; ++i) {
            tetro[2][i] = true;
        }
    } else if (type == 'O') {
        // . - - .
        // . - - .
        tetro[1][1] = true;
        tetro[2][1] = true;
        tetro[1][2] = true;
        tetro[2][2] = true;
    } else if (type == 'T') {
        // . - - -
        // . . - .
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][2] = true;
    } else if (type == 'L') {
        // . - - -
        // . - . .
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][1] = true;
    } else if (type == 'J') {
        // . - - -
        // . . . -
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][3] = true;
    } else if (type == 'Z') {
        // . - - .
        // . . - -
        tetro[2][1] = true;
        tetro[2][2] = true;
        tetro[3][3] = true;
        tetro[3][2] = true;
    } else if (type == 'S') {
        // . . - -
        // . - - .
        tetro[3][1] = true;
        tetro[2][2] = true;
        tetro[2][3] = true;
        tetro[3][2] = true;
    }
}