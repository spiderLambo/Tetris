#include "serveur.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void ecrire (std::string & title, grille & g) {
	std::ofstream fic;
	fic.open(title);
	if (fic.is_open()) {
		if ((g[0][3] = 'C') and (g[0][4] = 'C') and (g[0][5] = 'C') and (g[0][6] = 'C')) {
			fic << 'I';
		} else if ((g[0][4] = 'C') and (g[0][5] = 'C') and (g[1][4] = 'C') and (g[1][5] = 'C')) {
			fic << 'O';
		} else if ((g[0][4] = 'C') and (g[0][5] = 'C') and (g[0][6] = 'C') and (g[1][5] = 'C')) {
			fic << 'T';
		} else if ((g[0][4] = 'C') and (g[0][5] = 'C') and (g[0][6] = 'C') and (g[1][4] = 'C')) {
			fic << 'L';
		} else if ((g[0][4] = 'C') and (g[0][5] = 'C') and (g[0][6] = 'C') and (g[1][6] = 'C')) {
			fic << 'J';
		} else if ((g[0][4] = 'C') and (g[0][5] = 'C') and (g[1][5] = 'C') and (g[1][6] = 'C')) {
			fic << 'Z';
		} else if ((g[0][5] = 'C') and (g[0][6] = 'C') and (g[1][4] = 'C') and (g[1][5] = 'C')) {
			fic << 'S';
		} else {
			std::cout << "[!]> Courant non détecter" << std::endl;
		}
		for (int i = 0; i < HAUTEUR; ++i) {
			for (int j = 0; j < LARGEUR; ++j) {
				fic << g[i][j];
			}
			fic << "";
		}
	} else {
		std::cout << "[!]> Ouverture en écriture n'a pas marcher" << std::endl;
	}
	fic.close();
}

void lire (std::string & title, action & a) {
	int rot;
	int depla;
	std::ifstream fic;
	fic.open(title);
	if (fic.is_open()) {
		std::string ligne;
		std::string derniere;
		while(std::getline(fic, ligne)) {
			if (!ligne.empty()) {
				derniere = ligne;
			}
		}
		derniere >> a.rot;
		derniere >> a.depla;
	} else {
		std::cout << "[!]> Ouverture en lecture n'a pas marcher" << std::endl;
	}
	fic.close();
}

void joue(grille & G, action & a) {
	
}

int run(grille & G) {
	int servfd, clifd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage cliaddr;
	action a;
	std::string grille = "grille.txt";
	std::string coup = "coup.txt";

	servfd = socket(AF_INET, SOCK_STREAM, 0);
	if (servfd == -1) {
		std::cout << "[!]> socket error" << std::endl;
		return -1;
	}
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	if (bind(servfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == -1) {
		std::cout << "[!]> bind error" << std::endl;
		return -1;
	}

	if (listen(servfd, 1) == -1) {
		std::cout << "[!]> listen error" << std::endl;
		return -1;
	}
	
	socklen_t size = sizeof(cliaddr);
	clifd = accept(servfd, (struct sockaddr *)&cliaddr, &size);
	if (clifd == -1) {
		std::cout << "[!]> accept error" << std::endl;
		return -1;
	}

    	std::cout << "[SERVEUR]: client connecté\n";

	bool run = true;
	while (run) {
		ecrire(grille, G);
        	const char* msg = "GO";
		int envoyer = send(clifd, msg, strlen(msg), 0);
		if (envoyer == -1) {
			std::cout << "[!]> send error" << std::endl;
			return -1;
		}
		char buffer[1024];
		int recu = recv(clifd, buffer, sizeof(buffer), 0);
		if (recu == -1) {
			std::cout << "[!]> recv  error" << std::endl;
			return -1;
		} else {
			lire(coup, a);
			joue(G, a);
		}
	}

	close(clifd);
	close(servfd);
	return 0;
}
