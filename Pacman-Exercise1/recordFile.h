#pragma once

#include "globalDef.h"
#include <fstream>
#include "moveQueue.h"
#include "fruitQueueHandler.h"

class recordFile {

public:
	static void writeMoves(std::ofstream& myFile, moveQueue* src);
	static void writeFruitData(std::ofstream& myFile, fruitQueueHandler* fruitQueue);
	static void readMoves(std::ifstream& myFile, moveQueue* movesQueue);
	static fruitQueueHandler* readFruitData(std::stringstream& ss, const gameType& gameMode);
};