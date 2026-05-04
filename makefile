Make: tetris
	./tetris

tetris: tetrominos grille movTetromino jouer
	g++ tetrominos.o grille.o movTetromino.o jouer.o -o tetris     -lsfml-graphics -lsfml-window -lsfml-system

tetrominos:
	g++ -Wall -c tetrominos.cpp -o tetrominos.o

grille:
	g++ -Wall -c grille.cpp -o grille.o

movTetromino:
	g++ -Wall -c movTetromino.cpp -o movTetromino.o

jouer:
	g++ -Wall -c jouer.cpp -o jouer.o

clean:
	rm -f tetrominos.o grille.o movTetromino.o jouer.o tetris