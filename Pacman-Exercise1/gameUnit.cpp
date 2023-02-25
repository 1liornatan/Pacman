#include "gameUnit.h"

short int gameUnit::getX() const {
	return currPt.getX();
}

short int gameUnit::getY() const {
	return currPt.getY();
}

Point& gameUnit::getXY() {
	return currPt;
}

void gameUnit::setXY(short int _x, short int _y) {
	currPt.setX(_x);
	currPt.setY(_y);
}

void gameUnit::setXY(Point& pt) {
	currPt.setXY(pt);
}


Board const* gameUnit::getBoard() const {
	return boardPtr;
}

GameColor const* gameUnit::getGameColor() const {
	return colors;
}

void gameUnit::setBoard(Board* _board) {
	boardPtr = _board;
}

void gameUnit::setQueuePtr(moveQueue* _moveQueuePtr)
{
	moveQueuePtr = _moveQueuePtr;
}

moveQueue* gameUnit::getQueuePtr() const
{
	return moveQueuePtr;
}

void gameUnit::recordMove(const Direction& dr)
{
	moveQueue* currQueue = getQueuePtr();

	if (currQueue == nullptr)
		return;

	if (currQueue->getGameMode() == gameType::GAME_RECORD) {
		currQueue->Push(dr);
	}
}
