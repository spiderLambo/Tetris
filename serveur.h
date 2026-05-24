#pragma once

#include "grille.h"
#include <SFML/Graphics.hpp>
#include <array>
#include <string>

// ─── Constantes ──────────────────────────────────────────────────────────────

constexpr int PORT = 63424;

// ─── Structures ──────────────────────────────────────────────────────────────

struct Plateau {
    char piece_courante;                              // 'I','O','T','L','J','S','Z'
    char piece_suivante;
    std::array<std::array<char, LARGEUR>, HAUTEUR> grille; // ' ' = vide, 'P' = placé
};

struct Action {
    bool reserve = false;
    int rotation = 0;
    int colonne = 0;
};

// ─── Fichiers ────────────────────────────────────────────────────────────────

// Écrit piece_courante, piece_suivante puis la grille dans `path`.
bool ecrire_grille(const std::string& path, const Plateau& p);

// Lit la dernière ligne de `path` et remplit `a` (format : "rot col").
bool lire_coup(const std::string& path, Action& a);

// ─── Réseau ──────────────────────────────────────────────────────────────────

// Crée et bind le socket serveur. Retourne le fd, ou -1 en cas d'erreur.
int creer_socket_serveur();

// Bloque jusqu'à l'arrivée d'un client. Retourne le fd client, ou -1.
int accepter_client(int servfd);

// Envoie "GO\n" et attend "OK\n". Retourne false si la connexion est perdue.
bool envoyer_go(int clifd);

// ─── Boucle de jeu ───────────────────────────────────────────────────────────

// Un tour complet : écriture grille → GO → OK → lecture coup.
// Retourne false si la connexion est perdue.
bool tour_de_jeu(int clifd, Plateau& plateau,
                 const std::string& chemin_grille,
                 const std::string& chemin_coup,
                 Action& action_calculee);


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



// 𐔌   .  ⋮ PROCEDURES POUR AFFICHER LA GRILLE .ᐟ  ֹ   ₊ ꒱
void afficherMenuPause(sf::RenderWindow & f);



// 𐔌   .  ⋮ PROCEDURES POUR JOUER 1 TOUR .ᐟ  ֹ   ₊ ꒱
void jouer(plateau & G, int level, int score, int & interval, sf::RenderWindow & f);