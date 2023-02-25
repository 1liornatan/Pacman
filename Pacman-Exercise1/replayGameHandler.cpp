
#include "replayGameHandler.h"


fruitQueueHandler* replayGameHandler::readFruitData()
{
	fruitQueueHandler* nextFruit = nullptr;
	if (!fruitDataQueue->empty()) {
		nextFruit = fruitDataQueue->front();
		fruitDataQueue->pop();
	}

	return nextFruit;
}

void replayGameHandler::setUnitsQueues()
{
	bool stopRead = false;
	std::string currLine;
	std::string recordFileName = *mapStr + ".steps";
	std::ifstream myFile(recordFileName);
	int pacmanX, pacmanY;


	Ghost** ghostPtrArr = getGhostPtrArr();
	fruitQueueHandler* currFruitHandler;

	myFile >> pacmanX;
	myFile >> pacmanY;

	pacmanPtr->setXY(pacmanX, pacmanY);
	myFile.ignore();
	recordFile::readMoves(myFile, pacmanPtr->getQueuePtr());

	for (int i = 0; i < getGhostsAmount(); i++) {
		recordFile::readMoves(myFile, ghostPtrArr[i]->getQueuePtr());
	}

	do {
		std::getline(myFile, currLine);

		if (currLine.length() < 1) {
			stopRead = true;
		}
		else {

			std::stringstream ss(currLine);
			currFruitHandler = recordFile::readFruitData(ss, gameMode);
			fruitDataQueue->push(currFruitHandler);
		}
	} while (!stopRead);

	myFile.close();
}