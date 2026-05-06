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

// Retrouve le type du tetromino
std::string converstring(tetromino & T);

// Encode la grille a l'instant t et le Tetromino courant
std::string msg(grille & G);

// Decode le coup a jouer envoyer par le client python
void decode(std::string & str, action & a);

// Joue le coup calculer
void joue(grille & G, action & a);

// Faire tourner le serveur et donc jouer
int run(grille & G);
