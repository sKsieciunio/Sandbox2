#pragma once
#include "element.h"

class Board {
	Element*** board;
	int size;

public:
	Board();
	~Board();

	void addElement(int x, int y, Element::ElementType type);
	void render(sf::RenderWindow& window, sf::Shape& shape) const;
	void calculatePhysics();

private:
	void sandPhysics(int x, int y);
	void waterPhysics(int x, int y);
	void swapElements(int x1, int y1, int x2, int y2);
	bool valueInBound(int v) const;
};