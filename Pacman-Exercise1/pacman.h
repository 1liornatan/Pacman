#pragma once

#include <iostream>
#include "gameUnit.h"



class Pacman: public gameUnit {
	Point startPt;
public:

	//ctors
	Pacman(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = 0, short int _y = 0):
	gameUnit(_board, _moveQueuePtr, _colors, _x, _y), startPt(_x, _y) {}

	void resetXY();
	void move(Direction dr);
	void print() const;
private:
	void checkTunnel(Point& pt);
};