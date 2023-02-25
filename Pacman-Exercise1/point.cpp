#include "point.h"

void Point::setXY(Point& pt) {
	x = pt.getX();
	y = pt.getY();
}


void Point::move(Direction dr) {
	switch (dr) {
	case Direction::LEFT:
			x--;
		break;
	case Direction::RIGHT:
			x++;
		break;
	case Direction::UP:
			y--;
		break;
	case Direction::DOWN:
			y++;
		break;
	}

}

short int Point::getX() const {
	return x;
}
void Point::setX(short int _x) {
	x = _x;
}
short int Point::getY() const {
	return y;
}
void Point::setY(short int _y) {
	y = _y;
}
void Point::setXY(short int _x, short int _y) {
	x = _x;
	y = _y;
}