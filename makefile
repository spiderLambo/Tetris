Make: tetris
	./tetris

tetris: grille jouer
	g++ grille.o jouer.o -o tetris     -lsfml-graphics -lsfml-window -lsfml-system


grille:
	g++ -Wall -c grille.cpp -o grille.o

jouer:
	g++ -Wall -c jouer.cpp -o jouer.o

clean:
	rm -f grille.o jouer.o tetris