#pragma once

#include <iostream>
#include "gameUnit.h"
#include "globalDef.h"
#include "pacman.h"

class Ghost : public gameUnit {
	Pacman* pacmanPtr;
	Point startPt;

public:

	//ctors

	Ghost(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = -1, short int _y = -1, Pacman* _pacmanPtr = nullptr) :
		gameUnit(_board, _moveQueuePtr, _colors, _x, _y), pacmanPtr(_pacmanPtr), startPt(_x, _y) {};

	virtual void move() = 0;
	void setPacman(Pacman* _pacmanPtr);
	void resetXY();
	void smartMove();
	void dummyMove(Direction dr);
	void print() const;

protected:
	bool replayMove();
};