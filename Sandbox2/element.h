#pragma once
#include <SFML/Graphics.hpp>

class Element {
public:
	enum class ElementType { EMPTY, SAND, WATER};

private:
	int Xpos;
	int Ypos;
	sf::Color color;
	ElementType type;

public:
	Element(int x = -1, int y = -1, ElementType type = ElementType::EMPTY);

	void render(sf::RenderWindow& window, sf::Shape& shape) const;
	void setPos(int x, int y);
};