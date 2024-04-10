#include <SFML/Graphics.hpp>
#include <iostream>
#include "element.h"
#include "board.h"
#include "global.h"

void ProcessEvent(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window{ sf::VideoMode{ GLOBAL::SCR_SIZE, GLOBAL::SCR_SIZE }, "Sandbox 2"};

	sf::RectangleShape grainShape{ sf::Vector2f{ GLOBAL::GRAIN_SIZE, GLOBAL::GRAIN_SIZE } };

	Board board{};
	board.addElement(2,2,Element::ElementType::SAND);
	board.addElement(4,4,Element::ElementType::WATER);

	while (window.isOpen()) 
	{
		ProcessEvent(window);
		window.clear(sf::Color{ 20, 30, 40, 255 });

		board.render(window, grainShape);

		window.display();
	}

	return 0;
}

void ProcessEvent(sf::RenderWindow& window)
{
	sf::Event event;

	while (window.pollEvent(event)) {
		switch (event.type) {
		case sf::Event::Closed:
			window.close();
			break;
		case sf::Event::KeyPressed:
			if (event.key.scancode == sf::Keyboard::Scan::Escape)
				window.close();
			break;
		default:
			break;
		}
	}
}
