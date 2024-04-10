#include "element.h"
#include "global.h"

Element::Element(int x, int y, ElementType type) 
	: Xpos{ x }, Ypos{ y }, type{ type } 
{
	switch (type)
	{
	case Element::ElementType::EMPTY:
		color = sf::Color::Transparent;
		break;
	case Element::ElementType::SAND:
		color = sf::Color{ 255, 244, 91, 255 };
		break;
	case Element::ElementType::WATER:
		color = sf::Color{ 68, 108, 225, 255 };
		break;
	}
}

void Element::render(sf::RenderWindow& window, sf::Shape& shape) const {
	shape.setFillColor(color);
	shape.setPosition(Xpos * GLOBAL::GRAIN_SIZE, Ypos * GLOBAL::GRAIN_SIZE);
	window.draw(shape);
}

void Element::setPos(int x, int y) {
	Xpos = x;
	Ypos = y;
}

Element::ElementType Element::getType() const {
	return type;
}