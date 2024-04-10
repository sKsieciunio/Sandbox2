#include <SFML/Graphics.hpp>
#include <iostream>
#include "element.h"
#include "global.h"

void ProcessEvent(sf::RenderWindow& window);

int main() {
	sf::RenderWindow window{ sf::VideoMode{ GLOBAL::SCR_SIZE, GLOBAL::SCR_SIZE }, "Sandbox 2"};

	sf::RectangleShape grainShape{ sf::Vector2f{ GLOBAL::GRAIN_SIZE, GLOBAL::GRAIN_SIZE } };

	try {
		Element*** board = new Element**[GLOBAL::BOARD_SIZE];

		for (int i = 0; i < GLOBAL::BOARD_SIZE; ++i) {
			board[i] = new Element*[GLOBAL::BOARD_SIZE];

			for (int j = 0; j < GLOBAL::BOARD_SIZE; ++j) {
				board[i][j] = nullptr;
			}
		}
	}
	catch (std::bad_alloc& e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	catch (...) {
		return 2;
	}

	while (window.isOpen()) 
	{
		ProcessEvent(window);
		window.clear(sf::Color{ 20, 30, 40, 255 });

		Element e1{ 4, 4, Element::ElementType::SAND };
		Element e2{ 5, 10, Element::ElementType::WATER };

		e1.render(window, grainShape);
		e2.render(window, grainShape);

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
