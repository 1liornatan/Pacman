#pragma once

#include "fruitData.h"
#include "moveQueue.h"
#include "point.h"

class fruitQueueHandler : public moveQueue {
	fruitData dataOfFruit;
	Point pos;

public:
	fruitQueueHandler() = delete;
	fruitQueueHandler(const fruitData& _dataOfFruit, const Point& _pos, const gameType& gameMode) :
		moveQueue(gameMode), dataOfFruit(_dataOfFruit), pos(_pos) {};

	Point getPos() const;
	fruitData getFruitData() const;
	inline void setPos(int x, int y) { pos.setX(x); pos.setY(y); };
	inline void setFruitData(const fruitData& _dataOfFruit) { dataOfFruit = _dataOfFruit; };
};