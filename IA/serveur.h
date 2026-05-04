#pragma once
#include "grille.h"

#define PORT 63424

struct action {
	int rot;
	int deplacement;
};

int run();
