#pragma once

#include "gameHandler.h"
#include <fstream>
#include <vector>
#include "fruitQueueHandler.h"
#include "recordFile.h"

using vector = std::vector<fruitQueueHandler*>;
using string = std::string;

class recordGameHandler : public gameHandler {
	vector* fruitDataArr;
	string* mapStr;

public:
	recordGameHandler() = delete;
	recordGameHandler(Board* _boardPtr, GameColor* _colorsPtr, gameLevel _level, string* _mapStr) :
		gameHandler(_boardPtr, _colorsPtr, _level), mapStr(_mapStr) {
		Ghost** ghostPtrArr;
		int ghostsAmount;

		fruitDataArr = new vector;
		pacmanPtr->setQueuePtr(new moveQueue(gameType::GAME_RECORD));

		std::ofstream myFile(*mapStr + ".result"); // clear result file
		myFile.close();
		ghostPtrArr = getGhostPtrArr();
		ghostsAmount = getGhostsAmount();

		for (int i = 0; i < ghostsAmount; i++)
			ghostPtrArr[i]->setQueuePtr(new moveQueue(gameType::GAME_RECORD));
		
	};

	~recordGameHandler() override {
		saveRecord();

		for (auto a : *fruitDataArr)
			delete a;

		delete fruitDataArr;
		delete pacmanPtr->getQueuePtr();

		if (mapStr)
			delete mapStr;
	}

	recordGameHandler& operator=(const recordGameHandler&) = delete;

	gameStatus initGame(); //override;
	void saveRecord();

private:
	void addFruitToQueue();
};
