#pragma once

#include "globalDef.h"
#include <queue>

using queue = std::queue<Direction>;

class moveQueue {
	queue* queuePtr;
	gameType gameMode;

public:
	moveQueue() = delete;

	moveQueue(const gameType& _gameMode) {
		queuePtr = new queue();
		gameMode = _gameMode;
	}

	~moveQueue() {
		if(queuePtr)
			delete queuePtr;
	}

	moveQueue(const moveQueue&) = delete;
	moveQueue& operator=(const moveQueue&) = delete;

	Direction Dequeue();
	void Push(const Direction& dr);
	bool isEmpty() const;

	inline moveQueue* getQueuePtr() { return this; };
	inline gameType getGameMode() const { return gameMode; };
	//inline void setGameMode(gameType mode) { }

	static Direction getDirection(int button);

};