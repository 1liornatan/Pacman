#pragma once

#include "gameHandler.h"
#include <fstream>
#include <string>
#include <sstream>
#include "fruitQueueHandler.h"
#include "recordFile.h"

class replayGameHandler : public gameHandler {
	std::queue<fruitQueueHandler*>* fruitDataQueue;
	std::string* mapStr;
	gameType gameMode;

public:
	replayGameHandler() = delete;
	replayGameHandler(Board* _boardPtr, GameColor* _colorsPtr, gameLevel _level, std::string* _mapStr, gameType _gameMode = gameType::GAME_REPLAY) :
		gameHandler(_boardPtr, _colorsPtr, _level), mapStr(_mapStr), gameMode(_gameMode) {
		Ghost** ghostPtrArr;
		int ghostsAmount;

		fruitDataQueue = new std::queue<fruitQueueHandler*>();
		pacmanPtr->setQueuePtr(new moveQueue(gameMode));

		ghostPtrArr = getGhostPtrArr();
		ghostsAmount = getGhostsAmount();

		for (int i = 0; i < ghostsAmount; i++)
			ghostPtrArr[i]->setQueuePtr(new moveQueue(gameMode));

		setUnitsQueues();
	};

	~replayGameHandler() override {

		while (!fruitDataQueue->empty()) {
			delete fruitDataQueue->front();
			fruitDataQueue->pop();
		}

		delete fruitDataQueue;
		delete pacmanPtr->getQueuePtr();

		if (mapStr)
			delete mapStr;
	}

	replayGameHandler& operator=(const replayGameHandler&) = delete;

	virtual gameStatus initGame() = 0; //override;

protected:
	fruitQueueHandler* readFruitData();
	void setUnitsQueues();
};