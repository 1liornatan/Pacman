#pragma once

#include <iostream>
#include "board.h"
#include "moveQueue.h"

class gameUnit {
	Point currPt;
	Board* boardPtr;
	GameColor* colors;
	moveQueue* moveQueuePtr;

public:
	//ctors
	gameUnit(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = -1, short int _y = -1) :
		boardPtr(_board), colors(_colors), currPt(_x, _y), moveQueuePtr(_moveQueuePtr) {};

	virtual void print() const = 0;

	short int getX() const;
	short int getY() const;
	void setXY(short int _x, short int _y);
	Point& getXY();
	void setXY(Point& pt);
	void setBoard(Board* _board);
	Board const* getBoard() const;
	GameColor const* getGameColor() const;
	void setQueuePtr(moveQueue* _moveQueuePtr);
	moveQueue* getQueuePtr() const;

protected:
	void recordMove(const Direction& dr);
};