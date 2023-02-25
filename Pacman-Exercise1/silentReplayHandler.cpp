#include "silentReplayHandler.h"

gameStatus silentReplayHandler::initGame() {
	static bool ghostsMove = false;
	static bool isFruitSet = false;
	Point pointSaver;

	fruitQueueHandler* nextFruit = nullptr;
	moveQueue* pacmanQueuePtr = pacmanPtr->getQueuePtr();

	Direction dr = Direction::NONE;

	stepsCounter = 0;
	while (!pacmanQueuePtr->isEmpty())
	{
		stepsCounter++;
		dr = pacmanQueuePtr->Dequeue();

		pointSaver = pacmanPtr->getXY();

		if (!fruitPtr) { // set a new fruit spawn
			nextFruit = readFruitData();
			fruitPtr = new Fruit(boardPtr, nextFruit->getQueuePtr(), nullptr, nextFruit->getFruitData(), nextFruit->getPos());
		}
		else {
			if (fruitPtr->getLifetime() <= 0) { // remove fruit
				delete fruitPtr;
				delete nextFruit;
				nextFruit = readFruitData();
				fruitPtr = new Fruit(boardPtr, nextFruit->getQueuePtr(), nullptr, nextFruit->getFruitData(), nextFruit->getPos());
			}
		}
		fruitPtr->fruitAdvance();

		pacmanPtr->move(dr);
		checkEat(pacmanPtr->getXY());

		if (checkCollision()) {	// check for collision before movement of ghosts
			return gameStatus::GAME_LOSE;
		}

		if (breadCrumbs == 0) {
			if (nextFruit)
				delete nextFruit;
			return gameStatus::GAME_WIN;
		}

		if (ghostsMove) { // make ghosts move half the speed of pacman
			//move the ghosts
			moveGhosts();
			ghostsMove = false;
		}
		else {
			ghostsMove = true;
		}

		checkFruitGhostCollision();

		if (checkCollision()) {	// check for collision after movement of ghosts
			return gameStatus::GAME_LOSE;
		}
	}

	if (nextFruit)
		delete nextFruit;

	return gameStatus::GAME_STOP;
}


void silentReplayHandler::moveGhosts() {
	int i;
	int ghostAmount = getGhostsAmount();
	for (i = 0; i < ghostAmount; i++) {
		ghostPtrArr[i]->move();
	}
}