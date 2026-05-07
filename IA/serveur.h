#pragma once
#include "../grille.h"
#include "../tetrominos.h"
#include <string>

#define PORT 63424

// Les actions a jouer
struct action {
	int rot;
	int depla;
};

// Ecrit la grille du jeu a chaque longueur avec le courant en haut (le fichier est sans arret réecrit
void ecrire (std::string & title, grille & G);

// Lit l'action optimal calculer par le client et la stock dans action (le fichier n'est jamais réinitialiser, ce qui permet un historique des coups)
void lire (std::string & title, action & a);

// Joue le coup calculer
void joue(grille & G, action & a);

// Faire tourner le serveur et donc jouer
int run(grille & G);
