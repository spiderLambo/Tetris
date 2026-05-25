#include <string>
#include <array>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>


// Affiche le texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, sf::Color couleur, int taille, float x, float y);

// Menu
void afficherMenu(sf::RenderWindow & f, int selection);

// Paramètres
void afficherParametres(sf::RenderWindow & f, float & sliderX, bool & dragging);