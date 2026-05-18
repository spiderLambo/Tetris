#pragma once
#include <array>
#include <iostream>
#include <cstdlib>


//  ‧₊˚✧[ CONSTANTES ]✧˚₊‧
const int HAUTEUR = 20;
const int LARGEUR = 10;


//  ‧₊˚✧[ TYPES ]✧˚₊‧
using grille = std::array<std::array<char, LARGEUR>, HAUTEUR>;
struct plateau {
    grille gr;
    char next, nextPrecedent, reserve;
    int nbRotations, nbRotationsReserve;
};






//  ‧₊˚✧[ PROCEDURES ET FONCTIONS ]✧˚₊‧


// Procédure pour initialiser une grille
void initGrille (grille & g);
// Procédure de débug qui affiche une grille
void afficheGrille (grille g);



// ∘₊✧─── Apparition des tetrimonos ───✧₊∘
// Faire apparaitre un tetrimono d'un certain type
void apparait (grille & g, char type);
// Choisis un tetromino au hasard
void genereTetromino (plateau & g);



// Place le tetromino courant
void placer (grille & g);



// ∘₊✧─── Déplacements des tetrimonos ───✧₊∘
// Verifier si on peux déplacer le courant dans un direction
bool peuxGauche (grille g);
bool peuxDroite (grille g);
bool peuxDecendre (grille g);

// Procédures pour déplacer le courant
void gauche (grille & g);
void droite (grille & g);
void descendre (grille & g);

// Procédure plus générale pour simplifier les appels
void deplacer (grille & g, char dir);



// Verifie si il y a une collision avec le sol
bool collision (grille g);



// ∘₊✧─── Roatations des tetrimonos ───✧₊∘
// Procédures pour tourner a gauche et droite
void tournerGauche (plateau & G, int x, int y, int & nbrot);
void tournerDroite (plateau & G, int x, int y, int & nbrot);

// Procédure plus générale pour simplifier les appels
void tourner (plateau & g, bool sens);



// ∘₊✧─── Suppression des lignes ───✧₊∘
bool peuxSupprimerLigne (grille G, int l);
void supprimerLigne (grille & G, int l);


// Verifie si on arrete le programme
bool fini (grille G);


// ∘₊✧─── Réserver les tetrimonos ───✧₊∘
void reserver (plateau & G);