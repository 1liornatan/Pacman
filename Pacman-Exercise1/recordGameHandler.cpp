
#include "recordGameHandler.h"

gameStatus recordGameHandler::initGame() {
	static bool ghostsMove = false;
	static bool isFruitSet = false;
	static int button = 's';
	int lastButton = 's';
	Point pointSaver;

	moveQueue* pacmanQueuePtr = pacmanPtr->getQueuePtr();

	Direction dr = Direction::NONE;

	boardPtr->printAll();
	printScore();

	pacmanPtr->print();
	printGhosts();

	stepsCounter = 0;
	while ((button) != ESC)
	{
		stepsCounter++;
		lastButton = button;
		dr = moveQueue::getDirection(button);

		pacmanQueuePtr->Push(dr);
		pointSaver = pacmanPtr->getXY();

		if (!fruitPtr) { // set a new fruit spawn
			fruitPtr = new Fruit(boardPtr, nullptr, colorsPtr);
			addFruitToQueue();
		}
		else {
			if (fruitPtr->getLifetime() <= 0) { // remove fruit
				boardPtr->print(fruitPtr->getXY());
				delete fruitPtr;
				fruitPtr = new Fruit(boardPtr, nullptr, colorsPtr);
				addFruitToQueue();
			}
		}
		fruitPtr->fruitAdvance();

		pacmanPtr->move(dr);
		checkEat(pacmanPtr->getXY());

		if (breadCrumbs == 0)
			return gameStatus::GAME_WIN;

		printScore();
		boardPtr->print(pointSaver);
		pacmanPtr->print();

		if (checkCollision()) // check for collision after movement of ghosts
			return gameStatus::GAME_LOSE;

		if (ghostsMove) { // make ghosts move half the speed of pacman
			//move the ghosts
			makeGhostsMove();
			ghostsMove = false;
		}
		else {
			ghostsMove = true;
		}

		checkFruitGhostCollision();

		if (checkCollision()) // check for collision after movement of ghosts
			return gameStatus::GAME_LOSE;

		Sleep(TIME_INTERVAL);
		if (_kbhit())
			button = _getch();
	}
	button = lastButton;
	return gameStatus::GAME_PAUSED;
}

void recordGameHandler::saveRecord()
{
	Ghost** ghostsPtrArr;
	int ghostsAmount, fruitsAmount, i;
	vector& fruitArr = *fruitDataArr;
	string recordFileName = *mapStr + ".steps";

	std::ofstream myFile(recordFileName);

	// TODO: Override the current file

	pacmanPtr->resetXY();
	myFile << pacmanPtr->getX() << " " << pacmanPtr->getY() << " ";
	recordFile::writeMoves(myFile, pacmanPtr->getQueuePtr());

	ghostsPtrArr = getGhostPtrArr();
	ghostsAmount = getGhostsAmount();

	for(i = 0; i < ghostsAmount; i++)
		recordFile::writeMoves(myFile, ghostsPtrArr[i]->getQueuePtr());
	
	fruitsAmount = fruitDataArr->size();

	for (i = 0; i < fruitsAmount; i++) {
		recordFile::writeFruitData(myFile, fruitArr[i]);
	}
	myFile.close();
}


void recordGameHandler::addFruitToQueue()
{
	fruitData currData;
	fruitQueueHandler* currFruitHandler;

	currData.Interval = fruitPtr->getInterval();
	currData.Lifetime = fruitPtr->getLifetime();
	currData.spawnCooldown = fruitPtr->getCooldown();
	currData.Value = fruitPtr->getValue();

	currFruitHandler = new fruitQueueHandler(currData, fruitPtr->getXY(), gameType::GAME_RECORD);
	fruitDataArr->push_back(currFruitHandler);
	fruitPtr->setQueuePtr(currFruitHandler->getQueuePtr()); // save fruits movement to a new queue

}

