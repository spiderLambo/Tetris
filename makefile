MAKE: Menu

Menu: menu player
	g++ menu.o -o Tetris     -lsfml-graphics -lsfml-window -lsfml-system
	./Tetris

Player: player
	./tetris

player: grille jouer
	g++ grille.o jouer.o -o tetris     -lsfml-graphics -lsfml-window -lsfml-system

grille:
	g++ -Wall -c grille.cpp -o grille.o

jouer:
	g++ -Wall -c jouer.cpp -o jouer.o

menu:
	g++ -Wall -c menu.cpp -o menu.o

clean:
	rm -f grille.o jouer.o tetris Tetris menu.o