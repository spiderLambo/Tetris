#include "serveur.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>

void initRect (regctangle & rec, float taillex, float tailley, float x, float y, sf::Color fond, sf::Color outline) {
    rec.setSize({taillex, tailley});
    rec.setPosition({x, y});
    rec.setFillColor(fond);
    rec.setOutlineColor(outline);
    rec.setOutlineThickness(10);
}

void dessinerGrille (sf::RenderWindow & f, plateau G) {
    regctangle grilleRegctangle;

    // Afficher la grille
    initRect(grilleRegctangle, 240, 490, 10, 10, sf::Color(28,28,46), sf::Color(64,64,96));
    f.draw(grilleRegctangle);

    // Afficher les lignes pour guider le joueur
    for (int i = 1; i<LARGEUR; ++i) {
        for (int j = 1; j<HAUTEUR; ++j) {
            if (G.gr[j][i] == 'C' or G.gr[j][i-1] == 'C') {
            regctangle ligne;
            ligne.setSize({10, static_cast<float>(500-j*25)});
            ligne.setPosition({25.f * i, 25.f * j});
            ligne.setFillColor(sf::Color(136,136,170));
            f.draw(ligne);}
        }
    }

    // Afficher les tetrominos
    for (int i = 0; i<HAUTEUR; ++i) {
        for (int j = 0; j<LARGEUR; ++j) {
            if (G.gr[i][j] != ' ') {
                regctangle r;
                initRect(r, 15, 15, j*25+10, i*25+10, sf::Color(0, 53, 69), sf::Color(0, 136, 160));
                f.draw(r);
            }
        }
    }
}

void ecrire (std::string & title, grille & g) {
	std::ofstream fic;
	fic.open(title);
	if (fic.is_open()) {
		if ((g[1][3] == 'C') and (g[1][4] == 'C') and (g[1][5] == 'C') and (g[1][6] == 'C')) {
			fic << 'I';
		} else if ((g[1][4] == 'C') and (g[1][5] == 'C') and (g[2][4] == 'C') and (g[2][5] == 'C')) {
			fic << 'O';
		} else if ((g[1][4] == 'C') and (g[1][5] == 'C') and (g[1][6] == 'C') and (g[2][5] == 'C')) {
			fic << 'T';
		} else if ((g[1][4] == 'C') and (g[1][5] == 'C') and (g[1][6] == 'C') and (g[2][4] == 'C')) {
			fic << 'L';
		} else if ((g[1][4] == 'C') and (g[1][5] == 'C') and (g[1][6] == 'C') and (g[2][6] == 'C')) {
			fic << 'J';
		} else if ((g[1][4] == 'C') and (g[1][5] == 'C') and (g[2][5] == 'C') and (g[2][6] == 'C')) {
			fic << 'Z';
		} else if ((g[1][5] == 'C') and (g[1][6] == 'C') and (g[2][4] == 'C') and (g[2][5] == 'C')) {
			fic << 'S';
		} else {
			std::cout << "[!]> Courant non détecter" << std::endl;
		}
		for (int i = 0; i < HAUTEUR; ++i) {
			for (int j = 0; j < LARGEUR; ++j) {
				fic << g[i][j];
			}
			fic << "\n";
		}
	} else {
		std::cout << "[!]> Ouverture en écriture n'a pas marcher" << std::endl;
	}
	fic.close();
}

void lire (std::string & title, action & a) {
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
        std::stringstream ss(derniere);
        ss >> a.rot >> a.depla;
	} else {
		std::cout << "[!]> Ouverture en lecture n'a pas marcher" << std::endl;
	}
	fic.close();
}

void joue(plateau & G, action & a, int & level, int & score, int & interval, sf::RenderWindow & f) {
	std::chrono::time_point<std::chrono::system_clock> fin = std::chrono::system_clock::now() + std::chrono::milliseconds(interval);
    	std::chrono::time_point<std::chrono::system_clock> maintenant;
	std::cout << a.rot <<  " " << a.depla << std::endl;
	int numligne = 0;
    int colactuel = LARGEUR;
	int nombreDeLignes = 10;
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (G.gr[i][j] == 'C' && j < colactuel)
                colactuel = j;
    for (int i = 0; i < a.rot; ++i) {
		tourner(G, true);
	}
    int colApresRot = LARGEUR;
    for (int i = 0; i < HAUTEUR; ++i)
        for (int j = 0; j < LARGEUR; ++j)
            if (G.gr[i][j] == 'C' && j < colApresRot)
                colApresRot = j;

    int delta = a.depla - colApresRot;
    if (delta > 0) {
        for (int j = 0; j < delta; ++j) deplacer(G.gr, 'D');
    } else if (delta < 0) {
        for (int k = 0; k < -delta; ++k) deplacer(G.gr, 'G');
    }

	deplacer(G.gr, 'B');
	do {
		maintenant = std::chrono::system_clock::now();
		f.clear(sf::Color(19,19,31));
        	dessinerGrille(f, G);
        	f.display();
	} while (maintenant < fin);

    if (f.isOpen()) {
        placer(G.gr);
        genereTetromino(G);
        for (int d = 0; d < HAUTEUR; ++d) {
            if (peuxSupprimerLigne(G.gr, d)) {
                supprimerLigne(G.gr, d);
		numligne++;
		nombreDeLignes++;
	    }
        }
	int Nouveaulevel = nombreDeLignes/10;
        if (numligne == 1) score = score + level * 100;
        else if (numligne == 2) score = score + level * 300;
        else if (numligne == 3) score = score + level * 500;
        else if (numligne == 4) score = score + level * 800;
        else if (numligne > 4) score = score + 50*numligne*level;
        if (Nouveaulevel != level) {
            if (level == 0) interval = 1000;
            else if (level < 15) interval = interval * 0.75;
            else interval = interval * 0.9;
        }
        level = Nouveaulevel;
        if (fini(G.gr)) {
		std::cout << "[SERVEUR]: client deconnecté" << std::endl;
            std::cout << "Fin de parrie — niveau " << level << " — score " << score << std::endl;
            f.close();
            return;
        }
        dessinerGrille(f, G);
        f.display();
    }
}

int run(plateau & P, int & level, int & score, int & interval, sf::RenderWindow & f) {
	int servfd, clifd;
	struct sockaddr_in servaddr;
	struct sockaddr_storage cliaddr;
	action a;
	std::string ficgrille = "IA/grille.txt";
	std::string ficcoup = "IA/coup.txt";

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

    	std::cout << "[SERVEUR]: en attente de connexion..." << std::endl;

	socklen_t size = sizeof(cliaddr);
	clifd = accept(servfd, (struct sockaddr *)&cliaddr, &size);
	if (clifd == -1) {
		std::cout << "[!]> accept error" << std::endl;
		return -1;
	}

    	std::cout << "[SERVEUR]: client connecté" << std::endl;

	while (f.isOpen()) {
		ecrire(ficgrille, P.gr);
        	const char* msg = "GO\n";
		int envoyer = send(clifd, msg, strlen(msg), 0);
		if (envoyer == -1) {
			std::cout << "[!]> send error" << std::endl;
			return -1;
		}
		system("cat IA/grille.txt");
		char buffer[1025];
		int recu = recv(clifd, buffer, sizeof(buffer), 0);
		if (recu == -1) {
			std::cout << "[!]> recv  error" << std::endl;
			return -1;
		} else if (recu == 0) {
            		std::cout << "[-]> client déconnecter" << std::endl;
        	} else {
            		buffer[recu] = '\0';
			system("cat IA/coup.txt");
			lire(ficcoup, a);
			joue(P, a, level, score, interval, f);
		}
	}

	close(clifd);
	close(servfd);
	return 0;
}

int main() {
	sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    	fenetre.setFramerateLimit(24);

	plateau P;
	initGrille(P.gr);
	std::array <char, 7> choix = {'I', 'O', 'T', 'L', 'J', 'S', 'Z'};
    	P.next = choix[std::rand()%7];
	genereTetromino(P);
	
	int level = 1, score = 0, interval = 1000;
	run(P, level, score, interval, fenetre);
	return 0;
}
