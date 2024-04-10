#include <SFML/Graphics.hpp>

#include "global.h"

int main() {
    sf::RenderWindow window{ sf::VideoMode{ GLOBAL::SCR_WIDTH, GLOBAL::SCR_HEIGHT }, "Sandbox 2"};

    while (window.isOpen()) 
    {
        sf::Event event;

        while (window.pollEvent(event)) 
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Black);


        window.display();
    }

    return 0;
}