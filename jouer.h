#pragma once
#include "grille.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>

using regctangle = sf::RectangleShape;

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y);

void initRect (regctangle & rec, float taille, float x, float y);

void afficherNext (sf::RenderWindow & f, char next);

void afficherReserve (sf::RenderWindow & f, char next);

void dessinerGrille (sf::RenderWindow & f, plateau G);

void jouer(plateau & G, int level, int score, int & interval, sf::RenderWindow & f);