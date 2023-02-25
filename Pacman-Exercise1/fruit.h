#pragma once

#include "gameUnit.h"
#include "fruitData.h"
#include "globalDef.h"

class Fruit : public gameUnit {
	fruitData dataOfFruit;
	bool spawned;

public:
	Fruit(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr) :
		gameUnit(_board, _moveQueuePtr, _colors) {

		spawned = false;
		dataOfFruit.Value = (rand() % (FRUIT_MAX_VAL - FRUIT_MIN_VAL + 1)) + FRUIT_MIN_VAL;
		dataOfFruit.spawnCooldown = (rand() % (FRUIT_MAX_SPAWN_CD - FRUIT_MIN_SPAWN_CD + 1)) + FRUIT_MIN_SPAWN_CD;
		dataOfFruit.Interval = (rand() % FRUIT_MAX_INTERVAL) + 1;
		dataOfFruit.Lifetime = (rand() % FRUIT_MAX_LIFETIME - FRUIT_MIN_LIFETIME + 1) + FRUIT_MIN_LIFETIME;
		setRandomPos();
	}

	Fruit(Board* _board, moveQueue* _moveQueuePtr, GameColor* _colors, const fruitData& _dataOfFruit, const Point& pos) :
		gameUnit(_board, _moveQueuePtr, _colors, pos.getX(), pos.getY()), dataOfFruit(_dataOfFruit) {
		spawned = false;
	};

	int getCooldown() const;
	int getInterval() const;
	int getLifetime() const;
	bool isSpawned() const;
	void fruitAdvance();
	int getValue() const;
	void move();
	void print() const;

private:
	void setRandomPos();
	Direction getNextMove();
};