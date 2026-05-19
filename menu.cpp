#include "menu.h"
#include <iostream>

// Affiche le texte
void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, sf::Color couleur, int taille, float x, float y) {
    sf::Font font;
    font.loadFromFile(police);
    sf::Text text(texte, font, taille);
    text.setFillColor(couleur);
    text.setPosition(x, y);
    f.draw(text);
}


// Affiche le menu
void afficherMenu(sf::RenderWindow& f, int selection)
{
    f.clear(sf::Color(8, 8, 18));

    // TITRE
    afficherTexte(f, "TETRIS", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(255, 0, 180), 90, 90, 20);

    // Ombre
    afficherTexte(f, "TETRIS", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(0, 255, 255), 90, 92, 22);

    // Ligne de separation
    sf::RectangleShape ligne;
    ligne.setSize({380, 2});
    ligne.setPosition(60, 150);
    ligne.setFillColor(sf::Color(0, 255, 255, 180));
    f.draw(ligne);


    // OPTIONS
    std::array <std::string, 4> options = {"JOUER", "REGARDER", "PARAMETRES", "QUITTER"};

    // Texte
    for (int i = 0; i < 4; ++i) {
        sf::Color color;
        std::string font;

        // Affiche en rose
        if (i == selection) {
            color = sf::Color(255, 0, 180);
            font = "font/savery/savery.regular.ttf";
        // Affiche en non séléctionné
        } else {
            color = sf::Color(180, 180, 220);
            font="font/savery/savery.outline.ttf";
        }

        afficherTexte( f, options[i], font, color, 48, 140, 190 + i * 80 );
    }


    // SCANLINES
    for (int y = 0; y < 510; y += 4)
    {
        sf::RectangleShape scan;
        scan.setSize({500, 1});
        scan.setPosition(0, y);
        scan.setFillColor(sf::Color(255, 255, 255, 10));
        f.draw(scan);
    }

    f.display();
}


// Affiche les paramètres
void afficherParametres(sf::RenderWindow & f, float & sliderX, bool & dragging) {
    f.clear(sf::Color(8, 8, 18));

    // PARAMETRES
    afficherTexte(f, "PARAMETRES", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(255, 0, 180), 55, 50, 20);

    // Ombre
    afficherTexte(f, "PARAMETRES", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(0, 255, 255), 55, 52, 22);

    // Ligne de separation
    sf::RectangleShape ligne;
    ligne.setSize({450, 2});
    ligne.setPosition(60, 100);
    ligne.setFillColor(sf::Color(0, 255, 255, 180));
    f.draw(ligne);


    // CONTROLES avec une ombre
    afficherTexte(f, "CONTROLES", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(255, 0, 180), 40, 80, 100);
    afficherTexte(f, "CONTROLES", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(0, 255, 255), 40, 82, 102);


    // Controles
    afficherTexte(f, "GAUCHE : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 145);
    afficherTexte(f, "DROITE : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 170);
    afficherTexte(f, "TOURNER", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 195);
        afficherTexte(f, "GAUCHE : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 160, 220);
        afficherTexte(f, "DROITE : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 160, 245);
    afficherTexte(f, "BAS : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 270);
    afficherTexte(f, "RESERVER : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 295);
    afficherTexte(f, "PAUSE : ", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 30, 130, 320);
    // Ombres
    afficherTexte(f, "GAUCHE : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 145);
    afficherTexte(f, "DROITE : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 170);
    afficherTexte(f, "TOURNER", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 195);
        afficherTexte(f, "GAUCHE : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 160, 220);
        afficherTexte(f, "DROITE : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 160, 245);
    afficherTexte(f, "BAS : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 270);
    afficherTexte(f, "RESERVER : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 295);
    afficherTexte(f, "PAUSE : ", "font/savery/savery.outline.ttf",  sf::Color(255, 0, 180), 30, 130, 320);



    // Touches
    afficherTexte(f, "<", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 400, 145);
    afficherTexte(f, ">", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 400, 170);
    afficherTexte(f, "/\\", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 400, 220);
    afficherTexte(f, "\\/", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 400, 245);
    afficherTexte(f, "ENTREE", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 350, 270);
    afficherTexte(f, "R", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 400, 295);
    afficherTexte(f, "ESPACE", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 30, 350, 320);


    // SON avec une ombre
    afficherTexte(f, "SON", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(255, 0, 180), 40, 80, 350);
    afficherTexte(f, "SON", "font/circuit-forem-font/CircuitForemRegular-zr2n1.otf", sf::Color(0, 255, 255), 40, 82, 352);



    // Retour en arrière
    afficherTexte(f, "RETOUR", "font/savery/savery.outline.ttf",  sf::Color(255, 255, 255), 40, 170, 450);


    // Barre du slider
    float sliderMinX = 150;
    float sliderMaxX = 380;

    sf::RectangleShape barre({sliderMaxX - sliderMinX, 4});
    barre.setPosition(sliderMinX, 410);
    barre.setFillColor(sf::Color(180, 180, 220));
    f.draw(barre);

    // Curseur
    sf::CircleShape curseur(10);
    curseur.setPosition(sliderX - 10, 400);
    curseur.setFillColor(sf::Color(255, 0, 180));
    f.draw(curseur);


    // SCANLINES
    for (int y = 0; y < 510; y += 4)
    {
        sf::RectangleShape scan;
        scan.setSize({500, 1});
        scan.setPosition(0, y);
        scan.setFillColor(sf::Color(255, 255, 255, 10));
        f.draw(scan);
    }

    f.display();
}


int main() {
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(60);

    // Musique
    sf::Music music;
    music.openFromFile("tetrismusic.wav");
    music.setLoop(true);
    float volume = 0;
    music.setVolume(volume);
    music.play();

    int selection = -1;
    bool peuxAfficherParametres = false;
    bool retour = false;

    float sliderMinX = 150;
    float sliderMaxX = 380;
    float sliderX = sliderMinX;
    bool dragging = false;
    
    while (fenetre.isOpen())
    {
        // souris
        sf::Vector2i mouse = sf::Mouse::getPosition(fenetre);


        
        sf::Event event;
        while (fenetre.pollEvent(event))
{
    if (event.type == sf::Event::Closed) fenetre.close();

    if (peuxAfficherParametres) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (mouse.x >= sliderX - 10 && mouse.x <= sliderX + 10 &&
                mouse.y >= 400 && mouse.y <= 420)
                dragging = true;
        }
        if (event.type == sf::Event::MouseButtonReleased)
            dragging = false;
        if (event.type == sf::Event::MouseMoved && dragging) {
            sliderX = std::clamp((float)event.mouseMove.x, sliderMinX, sliderMaxX);
            volume = (sliderX - sliderMinX) / (sliderMaxX - sliderMinX) * 100;
            music.setVolume(volume);
        }
    }

    if (event.type == sf::Event::MouseButtonPressed) {
        if (peuxAfficherParametres && retour) {
            peuxAfficherParametres = false;
            retour = false;
        }
        else if (!peuxAfficherParametres) {
            if (selection == 0) system("./tetris");
            if (selection == 2) peuxAfficherParametres = true;
            if (selection == 3) fenetre.close();
        }
    }
}





        if (peuxAfficherParametres) {

            // On affiche les paramètres
            afficherParametres(fenetre, sliderX, dragging);

            // Changer le sprite au survol
            if (mouse.y >= 450.f && mouse.y <= 490) {
                afficherTexte(fenetre, "RETOUR", "font/savery/savery.regular.ttf",  sf::Color(255, 0, 180), 40, 170, 450);
                fenetre.display();
                retour = true;
            } else retour = false;
        } else {
            // Calcul de la zone Séléctionnée
            for (int i = 0; i < 4; i++) {
                float y1 = 190.f + i * 90.f;
                float y2 = y1 + 50.f;
 
                if (mouse.y >= y1 && mouse.y <= y2) {
                    selection = i;
                }
            }

            // On affiche le menu
            afficherMenu(fenetre, selection);
        }
    }
}