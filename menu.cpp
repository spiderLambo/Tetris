#include "menu.h"

void afficherTexte (sf::RenderWindow & f, std::string texte,std::string police, sf::Color couleur, int taille, float x, float y) {
    sf::Font font;
    font.loadFromFile(police);
    sf::Text text(texte, font, taille);
    text.setFillColor(couleur);
    text.setPosition(x, y);
    f.draw(text);
}

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
    std::array <std::string, 4> options = {
        "JOUER",
        "REGARDER",
        "PARAMETRES",
        "QUITTER"
    };

    for (int i = 0; i < 4; ++i)
    {
        sf::Color color;
        std::string font;

        if (i == selection)
            {color = sf::Color(255, 0, 180);
            font = "font/savery/savery.regular.ttf";}
        else
            {color = sf::Color(180, 180, 220);font="font/savery/savery.outline.ttf";}

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


int main()
{
    sf::RenderWindow fenetre(sf::VideoMode({500, 510}), "Tetris");
    fenetre.setFramerateLimit(60);

    int selection = -1;

    while (fenetre.isOpen())
    {
        sf::Event event;
        while (fenetre.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) fenetre.close();
            if (event.type == sf::Event::MouseButtonPressed) {
                if (selection == 0) system("./tetris");
                if (selection == 3) fenetre.close();
            }
        }

        // souris
        sf::Vector2i mouse = sf::Mouse::getPosition(fenetre);

        // Calcul de la zone Séléctionnée
        for (int i = 0; i < 4; i++)
        {
            float y1 = 190.f + i * 90.f;
            float y2 = y1 + 50.f;

            if (mouse.y >= y1 && mouse.y <= y2)
            {
                selection = i;
            }
        }

        afficherMenu(fenetre, selection);
    }
}