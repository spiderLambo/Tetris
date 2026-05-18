#pragma once
#include "grille.h"
#include <chrono>
#include <SFML/Graphics.hpp>
#include <cstdlib>


// Type pour simplifier les écritures
using regctangle = sf::RectangleShape;



// 𐔌   .  ⋮ PROCEDURES POUR AFFICHER DES ELEMENTS SIMPLES .ᐟ  ֹ   ₊ ꒱
// Texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, float x, float y);
// Rectangle 
// ! Initaialise le rectangle, l'affiche pas
void initRect (regctangle & rec, float taille, float x, float y);



// 𐔌   .  ⋮ PROCEDURES POUR AFFICHER LES TETRIMONOS SPECIAUX .ᐟ  ֹ   ₊ ꒱
// Le suivant
void afficherNext (sf::RenderWindow & f, char next);
// La réserve
void afficherReserve (sf::RenderWindow & f, char next, int rotation);



// 𐔌   .  ⋮ PROCEDURES POUR AFFICHER LA GRILLE .ᐟ  ֹ   ₊ ꒱
void dessinerGrille (sf::RenderWindow & f, plateau G);



// 𐔌   .  ⋮ PROCEDURES POUR JOUER 1 TOUR .ᐟ  ֹ   ₊ ꒱
void jouer(plateau & G, int level, int score, int & interval, sf::RenderWindow & f);