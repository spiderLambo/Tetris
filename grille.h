#pragma once
// #include "tetrominos.h"
#include <array>
#include <iostream>
#include <cstdlib>

const int HAUTEUR = 20;
const int LARGEUR = 10;

using grille = std::array<std::array<char, LARGEUR>, HAUTEUR>;

void initGrille (grille & g);

void afficheGrille (grille g);

void apparait (grille & g, char type);

void genereTetromino (grille & g);

void placer (grille & g);

bool peuxGauche (grille g);

bool peuxDroite (grille g);

bool peuxDecendre (grille g);

void gauche (grille & g);

void droite (grille & g);

void descendre (grille & g);

void deplacer (grille & g, char dir);

bool collision (grille g);

void tournerGauche (grille & g, int x, int y);

void tournerDroite (grille & g, int x, int y);

void tourner (grille & g, bool sens);
