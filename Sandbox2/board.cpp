#include <iostream>
#include <random>
#include "board.h"
#include "global.h"

// XDDDDDDDDD
static int getChoice() {
	static std::mt19937 mt{};
	static std::uniform_int_distribution die{ 0, 1 };
	return die(mt);
}

Board::Board()
	: size{ GLOBAL::BOARD_SIZE }
{
	try {
		board = new Element**[GLOBAL::BOARD_SIZE];

		for (int i{ 0 }; i < GLOBAL::BOARD_SIZE; ++i) {
			board[i] = new Element * [GLOBAL::BOARD_SIZE];

			for (int j{ 0 }; j < GLOBAL::BOARD_SIZE; ++j) {
				board[i][j] = nullptr;
			}
		}
	}
	catch (std::bad_alloc& e) {
		std::cerr << e.what() << std::endl;
	}
	catch (...) {
		std::cerr << "allocation error" << std::endl;
	}
}

Board::~Board() {
	for (int i{ 0 }; i < GLOBAL::BOARD_SIZE; ++i) {
		for (int j{ 0 }; j < GLOBAL::BOARD_SIZE; ++j) {
			if (board[i][j] != nullptr)
				delete board[i][j];
		}
		delete[] board[i];
	}
	delete[] board;
}

void Board::addElement(int x, int y, Element::ElementType type) {
	if (valueInBound(x) && valueInBound(y))
		if (board[x][y] == nullptr)
			board[x][y] = new Element{ x, y, type };
}

void Board::render(sf::RenderWindow& window, sf::Shape& shape) const {
	for (int i{ 0 }; i < GLOBAL::BOARD_SIZE; ++i) {
		for (int j{ 0 }; j < GLOBAL::BOARD_SIZE; ++j) {
			if (board[i][j] != nullptr)
				board[i][j]->render(window, shape);
		}
	}
}

void Board::calculatePhysics() {
	for (int y{ GLOBAL::BOARD_SIZE - 2 }; y >= 0; --y) {
		for (int x{ 0 }; x < GLOBAL::BOARD_SIZE; ++x) {
			if (board[x][y] == nullptr) continue;
			switch (board[x][y]->getType())
			{
			case Element::ElementType::SAND:
				sandPhysics(x, y);
				break;
			case Element::ElementType::WATER:
				waterPhysics(x, y);
				break;
			default:
				break;
			}
		}
	}
}

void Board::sandPhysics(int x, int y) {
	if (board[x][y + 1] == nullptr) {
		swapElements(x, y, x, y + 1);
	}
	else if (board[x][y + 1]->getType() == Element::ElementType::WATER) {
		swapElements(x, y, x, y + 1);
	}
	else if (x > 0 && x < GLOBAL::BOARD_SIZE - 1 
		&& board[x - 1][y + 1] == nullptr 
		&& board[x + 1][y + 1] == nullptr) {
		int choice{ (getChoice() == 0) ? -1 : 1 };
		swapElements(x, y, x + choice, y + 1);
	}
	else if (x > 0 && board[x - 1][y + 1] == nullptr) {
		swapElements(x, y, x - 1, y + 1);
	}
	else if (x < GLOBAL::BOARD_SIZE - 1 && board[x + 1][y + 1] == nullptr) {
		swapElements(x, y, x + 1, y + 1);
	}
}

void Board::waterPhysics(int x, int y) {
	if (board[x][y + 1] == nullptr) {
		swapElements(x, y, x, y + 1);
	}
	else if (x > 0 && x < GLOBAL::BOARD_SIZE - 1
		&& board[x - 1][y + 1] == nullptr
		&& board[x + 1][y + 1] == nullptr) {
		int choice{ (getChoice() == 0) ? -1 : 1 };
		swapElements(x, y, x + choice, y + 1);
	}
	else if (x > 0 && board[x - 1][y + 1] == nullptr) {
		swapElements(x, y, x - 1, y + 1);
	}
	else if (x < GLOBAL::BOARD_SIZE - 1 && board[x + 1][y + 1] == nullptr) {
		swapElements(x, y, x + 1, y + 1);
	}
}

void Board::swapElements(int x1, int y1, int x2, int y2) {
	if (board[x1][y1] == nullptr && board[x2][y2] == nullptr) { return; }
	else if (board[x2][y2] == nullptr) {
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = nullptr;
		board[x2][y2]->setPos(x2, y2);
	}
	else if (board[x1][y1] == nullptr) {
		board[x1][y1] = board[x2][y2];
		board[x2][y2] = nullptr;
		board[x1][y1]->setPos(x1, y1);
	}
	else {
		Element* temp = board[x1][y1];
		board[x1][y1] = board[x2][y2];
		board[x2][y2] = temp;
		board[x1][y1]->setPos(x1, y1);
		board[x2][y2]->setPos(x2, y2);
	}
}

bool Board::valueInBound(int v) const {
	return (v >= 0 && v < GLOBAL::BOARD_SIZE);
}