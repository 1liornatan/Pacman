#include "pacman.h"

void Pacman::move(Direction dr) {
	Point nextPt = getXY();

	nextPt.move(dr);
	checkTunnel(nextPt);

	if (getBoard()->getSign(nextPt) != wall_sign) // overflow validation inside getSign
		setXY(nextPt);
}

void Pacman::checkTunnel(Point& pt) {
	short int _x = pt.getX(), _y = pt.getY();
	short int boardLen = getBoard()->getLength();
	short int boardWidth = getBoard()->getWidth();

	if (_x == -1) {
			pt.setX(boardLen - 1);
	}
	else if (_x == (boardLen)) {
			pt.setX(0);
	}
	else if (_y == -1) {
			pt.setY(boardWidth-1);
	}
	else if (_y == boardWidth) {
			pt.setY(0);
	}
}

void Pacman::print() const {
	static int bLength = getBoard()->getLength();
	static int bWidth = getBoard()->getWidth();

	Board::gotoxy(getX(), getY());
	GameColor const* colorsPtr = getGameColor();

	if(colorsPtr != nullptr)
		setTextColor(colorsPtr->getPacmanColor());

	std::cout << pacman_sign;
	Board::gotoxy(bLength + SCORE_LENGTH, bWidth + SCORE_WIDTH); // move cursor to bottom right
}

void Pacman::resetXY() {
	setXY(startPt);
}
