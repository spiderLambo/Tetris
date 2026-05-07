#pragma once
#include "grille.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using regctangle = sf::RectangleShape;

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y);

void initRect (regctangle & rec, float taille, float x, float y);

void dessinerGrille (sf::RenderWindow & f, grille G);

void jouer(grille & G, int level, int score, int & interval, sf::RenderWindow & f);