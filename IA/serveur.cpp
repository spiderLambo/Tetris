#include "serveur.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void ecrire (std::string & title, grille & G) {
	std::ofstream fic;
	fic.open(title);
	if (fic.is_open()) {
		fic << ;
		for (int i = 0; i < HAUTEUR; ++i) {
			for (int j = 0; j < LARGEUR, ++j) {
				fic << G[i][j];
			}
			fic << "";
		}
	} else {
		std::cout << "[!]> Ouverture en écriture n'a pas marcher" << std::endl;
	}
}

void lire (std::string & title, action & a) {
	int rot;
	int depla;
	std::ifstream fic;
	fic.open(title);
	if (fic.is_open()) {
		
	} else {
		std::cout << "[!]> Ouverture en lecture n'a pas marcher" << std::endl;
	}
}

void joue(grille & G, action & a) {
	
}

int run(grille & G) {
	int servfd, clifd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage cliaddr;
	action a;

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

	bool run = true;
	while (run) {
		ecrire("grille.txt", G);
		int envoyer = send(clifd, , , 0);
		if (envoyer == -1) {
			std::cout << "[!]> send error" << std::endl;
			return -1;
		}
		int recu = recv(clifd, , , 0);
		if (recu == -1) {
			std::cout << "[!]> recv  error" << std::endl;
			return -1;
		} else {
			lire(coup.txt, a);
			joue(G, a);
		}
	}

	close(clifd);
	close(servfd);
	return 0;
}
