#pragma once

#include <iostream>
#include "globalDef.h"

class Point {
	short int x, y;
public:
	Point(short int _x = -1, short int _y = -1) : x(_x), y(_y) {};

	bool operator==(Point& pt1) {
		return (pt1.getX() == x && pt1.getY() == y);
	}

	bool operator!=(Point& pt1) {
		return (pt1.getX() != x || pt1.getY() != y);
	}

	short int getX() const;
	void setX(short int _x);
	short int getY() const;
	void setY(short int _y);
	void setXY(short int _x, short int _y);
	void setXY(Point& pt);

	void move(Direction dr);
};