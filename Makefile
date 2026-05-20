MAKE: Menu
	./Tetris


# Robot
Robot: robot
	./robot

robot: grille serveur
	g++ -Wall serveur.o grille.o -o robot     -lsfml-graphics -lsfml-window -lsfml-system

# Menu
Menu: menu player
	g++ menu.o -o Tetris     -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio


# Jeu
Player: player
	./tetris

player: grille jouer
	g++ grille.o jouer.o -o tetris     -lsfml-graphics -lsfml-window -lsfml-system



# .o
grille:
	g++ -Wall -c grille.cpp -o grille.o

jouer:
	g++ -Wall -c jouer.cpp -o jouer.o

menu:
	g++ -Wall -c menu.cpp -o menu.o

serveur:
	g++ -Wall -c IA/serveur.cpp -o serveur.o



# Clean
clean:
	rm -f grille.o jouer.o tetris Tetris menu.o serveur.o grille.o robot