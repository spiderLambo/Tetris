#include "serveur.h"
#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

std::string converstring(tetromino & T) {
	if ((T[1][1] == true) && (T[2][1] == true) && (T[1][2] == true) && T[2][2] == true) {
		return "O";
	} else if ((T[2][1] == true) && (T[2][2] == true) && (T[2][3] == true) && (T[3][2] == true)) {
		return "T";
	} else if ((T[2][1] == true) && (T[2][2] == true) && (T[2][3] == true) && (T[3][1] == true)) {
		return "L";
	} else if ((T[2][1] == true) && (T[2][2] == true) && (T[2][3] == true) && (T[3][3] == true)) {
		return "J";
	} else if ((T[2][1] == true) && (T[2][2] == true) && (T[3][3] == true) && (T[3][2] == true)) {
		return "Z";
	} else if ((T[3][1] == true) && (T[2][2] == true) && (T[2][3] == true) && (T[3][2] == true)) {
		return "S";
	} else if ((T[2][0] == true) && (T[2][1] == true) && (T[2][2] == true) && (T[2][3] == true)) {
		return "I";
	} else {
		std::cout << "Rien retourner bzr" << std::endl;
	}
	return "";
}

std::string msg(grille & G) {
	std::string msg = "courant: " + converstring(G.courant->tetro) + "\n";
	for (int i = 0; i < G.nb; ++i) {
		std::string line = converstring(G.places[i].tetro) + "," + std::to_string(G.places[i].Positions[0]) + "," + std::to_string(G.places[i].Positions[1]) + "\n";
		msg += line;
	}
	return msg;
}

void decode(std::string & str, action & a) {
	int rot;
	int deplacement;
	rot = std::stoi(&str[13]);
	deplacement = std::stoi(&str[26]);
	a.rot = rot;
	a.depla = deplacement;
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
		std::string create = msg(G);
		char *msg = new char[create.length()+1];
		std::strcpy(msg, create.c_str());
		int envoyer = send(clifd, msg, sizeof(msg), 0);
		if (envoyer == -1) {
			std::cout << "[!]> send error" << std::endl;
			return -1;
		}
		char buffer[2048];
		int recu = recv(clifd, buffer, strlen(buffer), 0);
		if (recu == -1) {
			std::cout << "[!]> recv  error" << std::endl;
			return -1;
		} else {
			std::cout << buffer << std::endl;
			std::string buff(buffer, sizeof(buffer));
			decode(buff, a);
			joue(G, a);
		}
		delete[] msg;
	}

	close(clifd);
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
