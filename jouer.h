#pragma once
#include "movTetromino.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using regctangle = sf::RectangleShape;

void initRect (regctangle & rec, float taille, float x, float y);

void afficherTetromino (sf::RenderWindow & f, tetrominoPlace t);

void dessinerGrille (sf::RenderWindow & f, grille G);

void choisisTetromino (tetrominoPlace & T);

void jouer(grille & G, int & level, int & interval, sf::RenderWindow & f);