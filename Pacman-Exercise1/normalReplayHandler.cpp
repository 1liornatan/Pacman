#include "normalReplayHandler.h"

gameStatus normalReplayHandler::initGame() {
	static bool ghostsMove = false;
	static bool isFruitSet = false;
	static int movesCounter = 0;
	Point pointSaver;

	fruitQueueHandler* nextFruit = nullptr;
	moveQueue* pacmanQueuePtr = pacmanPtr->getQueuePtr();

	Direction dr = Direction::NONE;

	boardPtr->printAll();
	printScore();

	pacmanPtr->print();
	printGhosts();


	while (!pacmanQueuePtr->isEmpty())
	{
		movesCounter++;
		dr = pacmanQueuePtr->Dequeue();

		pointSaver = pacmanPtr->getXY();

		if (!fruitPtr) { // set a new fruit spawn
			nextFruit = readFruitData();
			fruitPtr = new Fruit(boardPtr, nextFruit->getQueuePtr(), nullptr, nextFruit->getFruitData(), nextFruit->getPos());
		}
		else {
			if (fruitPtr->getLifetime() <= 0) { // remove fruit
				boardPtr->print(fruitPtr->getXY());
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
			if (nextFruit)
				delete nextFruit;
			return gameStatus::GAME_LOSE;
		}

		if (breadCrumbs == 0) {
			if (nextFruit)
				delete nextFruit;
			movesCounter = 0;
			return gameStatus::GAME_WIN;
		}

		printScore();
		boardPtr->print(pointSaver);
		pacmanPtr->print();

		if (ghostsMove) { // make ghosts move half the speed of pacman
			//move the ghosts
			makeGhostsMove();
			ghostsMove = false;
		}
		else {
			ghostsMove = true;
		}

		checkFruitGhostCollision();

		if (checkCollision()) {	// check for collision after movement of ghosts
			if (nextFruit)
				delete nextFruit;
			return gameStatus::GAME_LOSE;
		}
		Sleep(TIME_INTERVAL);
	}

	if (nextFruit)
		delete nextFruit;

	return gameStatus::GAME_STOP;
}
