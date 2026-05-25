# Sources locales pour SFML
SFML_FLAGS = -I./SFML_local/include -DSFML_STATIC
SFML_LIBS = -L./SFML_local/lib \
    -lsfml-graphics-s -lsfml-window-s -lsfml-audio-s -lsfml-network-s -lsfml-system-s \
    -lGL -lX11 -lXrandr -lXcursor -lXi -lXinerama -ludev \
    -lpthread -lfreetype -lFLAC -lvorbisenc -lvorbisfile -lvorbis -logg

MAKE: clean Menu
	./Tetris


# Menu
Menu: menu player robot
	g++ menu.o -o Tetris $(SFML_LIBS)

# Robot
Robot: robot
	./robot

robot: grille serveur
	g++ -Wall serveur.o grille.o -o robot $(SFML_LIBS)

# Jeu
Player: player
	./tetris

player: grille jouer
	g++ grille.o jouer.o -o tetris $(SFML_LIBS)






# .o
grille:
	g++ -Wall $(SFML_FLAGS) -c grille.cpp -o grille.o
jouer:
	g++ -Wall $(SFML_FLAGS) -c jouer.cpp -o jouer.o
menu:
	g++ -Wall $(SFML_FLAGS) -c menu.cpp -o menu.o
serveur:
	g++ -Wall $(SFML_FLAGS) -c serveur.cpp -o serveur.o






# Clean
clean:
	rm -f grille.o jouer.o tetris Tetris menu.o serveur.o grille.o robot grille.txt coup.txt