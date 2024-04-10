#pragma once
#include "element.h"

class Board {
	Element*** board;
	int size;

public:
	Board();
	~Board();

	void addElement(int x, int y, Element::ElementType type);
	void render(sf::RenderWindow& window, sf::Shape& shape) const ;
};