#include <SFML/Graphics.hpp>
#include <iostream>
#include "element.h"
#include "board.h"
#include "global.h"

void processEvent(sf::RenderWindow& window);

Element::ElementType currentType{ Element::ElementType::SAND };

int main() {
	sf::RenderWindow window{ sf::VideoMode{ GLOBAL::SCR_SIZE, GLOBAL::SCR_SIZE }, "Sandbox 2"};

	sf::RectangleShape grainShape{ sf::Vector2f{ GLOBAL::GRAIN_SIZE, GLOBAL::GRAIN_SIZE } };

	Board board{};
	sf::Clock physicsClock{};

	while (window.isOpen()) 
	{
		processEvent(window);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			board.addElement(mousePos.x / GLOBAL::GRAIN_SIZE, mousePos.y / GLOBAL::GRAIN_SIZE, currentType);
		}

		window.clear(sf::Color{ 22, 23, 26, 255 });

		if (physicsClock.getElapsedTime().asSeconds() >= 1.0f / GLOBAL::PHYSICS_RATE) {
			board.calculatePhysics();
			physicsClock.restart();
		}

		board.render(window, grainShape);

		/* BENCHMARK
		for (int i = 0; i < GLOBAL::BOARD_SIZE; ++i) {
			board.addElement(i, i % 2, currentType);
		}
		*/

		window.display();
	}

	return 0;
}

void processEvent(sf::RenderWindow& window)
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
			if (event.key.scancode == sf::Keyboard::Scan::Num1)
				currentType = Element::ElementType::SAND;
			if (event.key.scancode == sf::Keyboard::Scan::Num2)
				currentType = Element::ElementType::WATER;
			break;
		default:
			break;
		}
	}
}
