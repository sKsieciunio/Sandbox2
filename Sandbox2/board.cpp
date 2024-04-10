#include <iostream>
#include "board.h"
#include "global.h"

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