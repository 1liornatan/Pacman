#include "moveQueue.h"

bool moveQueue::isEmpty() const {
	return queuePtr->empty();
}
Direction moveQueue::Dequeue() {
	Direction dr;

	if (queuePtr->empty())
		dr = Direction::NONE;
	else {
		dr = queuePtr->front();
		queuePtr->pop();
	}

	return dr;
}

void moveQueue::Push(const Direction& dr)
{
	queuePtr->push(dr);
}

Direction moveQueue::getDirection(int button) {
	static Direction dr = Direction::STAY;

	switch (button) {
	case 'a': case 'A':
		dr = Direction::LEFT;
		break;
	case 'd': case 'D':
		dr = Direction::RIGHT;
		break;
	case 'x': case 'X':
		dr = Direction::DOWN;
		break;
	case 'w': case 'W':
		dr = Direction::UP;
		break;
	case 's': case 'S':
		dr = Direction::STAY;
		break;
	}

	return dr;
}
