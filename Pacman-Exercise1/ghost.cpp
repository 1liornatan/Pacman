#include "ghost.h"

void Ghost::dummyMove(Direction dr) { // make a move to a direction given
	Point nextPt = getXY();

	nextPt.move(dr);
	recordMove(dr); // saves move if game is being recorded

	if (getBoard()->getSign(nextPt) != wall_sign)
		setXY(nextPt);
}
void Ghost::smartMove() { // ghost will try to approach pacman by calculating the distance
	Point& pacmanPos = pacmanPtr->getXY();
	Point& ghostPos = getXY();
	Point nextPt = ghostPos;
	Direction dr;

	int ghostX, ghostY;
	int pacmanX, pacmanY;
	int xDistance, yDistance;

	ghostX = ghostPos.getX();
	ghostY = ghostPos.getY();
	pacmanX = pacmanPos.getX();
	pacmanY = pacmanPos.getY();

	xDistance = pacmanX - ghostX;
	yDistance = pacmanY - ghostY;

	if (abs(xDistance) > abs(yDistance)) {
		dr = (pacmanX > ghostX) ? Direction::RIGHT : Direction::LEFT;
	}
	else {
		dr = (pacmanY > ghostY) ? Direction::DOWN : Direction::UP;
	}

	nextPt.move(dr);

	if (getBoard()->getSign(nextPt) != wall_sign) { // overflow validation inside getSign
		setXY(nextPt);
		recordMove(dr);
	}
	else {
		if (abs(xDistance) > abs(yDistance)) {
			dr = (pacmanY > ghostY) ? Direction::DOWN : Direction::UP;
		}
		else {
			dr = (pacmanX > ghostX) ? Direction::RIGHT : Direction::LEFT;
		}

		nextPt = getXY();
		nextPt.move(dr);
		recordMove(dr);
		if (getBoard()->getSign(nextPt) != wall_sign) {// overflow validation inside getSign
			setXY(nextPt);
		}
	}
}

void Ghost::print() const {

	static int bLength = getBoard()->getLength();
	static int bWidth = getBoard()->getWidth();

	Board::gotoxy(getX(), getY());
	GameColor const* colorPtr = getGameColor();
	if(colorPtr != nullptr)
		setTextColor(colorPtr->getGhostColor());
	std::cout << ghost_sign;

	Board::gotoxy(bLength + SCORE_LENGTH, bWidth + SCORE_WIDTH); // move cursor to bottom right
}

bool Ghost::replayMove() // returns false if game is not replay otherwise makes replay move and returns true
{
	moveQueue* movesPtr = getQueuePtr();

	if (!movesPtr)
		return false;

	if (movesPtr->getGameMode() != gameType::GAME_REPLAY && movesPtr->getGameMode() != gameType::GAME_REPLAY_SILENT)
		return false;

	dummyMove(movesPtr->Dequeue());

	return true;
}

void Ghost::resetXY() {
	setXY(startPt);
}


void Ghost::setPacman(Pacman* _pacmanPtr) {
	pacmanPtr = _pacmanPtr;
}