#include <string>
#include <array>
#include <SFML/Graphics.hpp>

// Affiche le texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, sf::Color couleur, int taille, float x, float y);

// Menu
void afficherMenu(sf::RenderWindow& f, int selection);
