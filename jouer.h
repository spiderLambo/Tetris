#pragma once
#include "movTetromino.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <array>

using regctangle = sf::RectangleShape;

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y);

void initRect (regctangle & rec, float taille, float x, float y);

void afficherTetromino (sf::RenderWindow & f, tetrominoPlace t);

void dessinerGrille (sf::RenderWindow & f, grille G);

void jouer(grille & G, int level, int score, int & interval, sf::RenderWindow & f);