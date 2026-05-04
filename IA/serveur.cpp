#include "serveur.h"
#include "../grille.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

char msg(grille & G) {
	std::string msg = "courant: " + G.courant->tetro + "\n";
	for (int i = 0; i < G.nb; ++i) {
		std::string line = G.places[i].tetro + "," + G.places[i].Positions[0] + "," + G.places[i].Positions[1] + "\n";
		msg += line;
	}
	return msg;
}

int run() {
	int servfd, clifd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage cliaddr;
	std::string Buffer = "";

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

	bool run = true;
	while (run) {
		socklen_t size = sizeof(cliaddr);
		clifd = accept(servfd, (struct sockaddr *)&cliaddr, &size);
		if (clifd == -1) {
			std::cout << "[!]> accept error" << std::endl;
			return -1;
		}
		char msg[] = "ca marche";
		int envoyer = send(clifd, msg, strlen(msg), 0);
		if (envoyer == -1) {
			std::cout << "[!]> send error" << std::endl;
			return -1;
		}
        close(clifd);
	}
    close(servfd);
	return 0;
}

int main() {
	int ru = run();
	if (ru == 0) {
		std::cout << "ca marche" << std::endl;
	}
	return 0;
}
