#include "normalGameHandler.h"

gameStatus normalGameHandler::initGame() {
	static bool ghostsMove = false;
	static bool isFruitSet = false;
	static int button = 's';
	int lastButton = 's';
	Point pointSaver;
	//	gameUnit* unitPtr;
	Direction dr = Direction::NONE;

	boardPtr->printAll();
	printScore();

	pacmanPtr->print();
	printGhosts();


	while ((button) != ESC)
	{
		lastButton = button;
		dr = getDirection(button);
		pointSaver = pacmanPtr->getXY();

		if (!fruitPtr) { // set a new fruit spawn
			fruitPtr = new Fruit(boardPtr, nullptr, colorsPtr);
		}
		else {
			if (fruitPtr->getLifetime() <= 0) { // remove fruit
				boardPtr->print(fruitPtr->getXY());
				delete fruitPtr;
				fruitPtr = new Fruit(boardPtr, nullptr, colorsPtr);
			}
		}
		fruitPtr->fruitAdvance();

		pacmanPtr->move(dr);
		checkEat(pacmanPtr->getXY());

		if (checkCollision()) // check for collision before movement of ghosts
			return gameStatus::GAME_LOSE;

		if (breadCrumbs == 0)
			return gameStatus::GAME_WIN;

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

		if (checkCollision()) // check for collision after movement of ghosts
			return gameStatus::GAME_LOSE;

		Sleep(TIME_INTERVAL);
		if (_kbhit())
			button = _getch();
	}
	button = lastButton;
	return gameStatus::GAME_PAUSED;
}


Direction normalGameHandler::getDirection(int button) {
	static Direction dr = Direction::STAY;

	switch (button) {
	case 'a': case 'A':
		dr = Direction::LEFT;
		break;
	case 'd': case 'D':
		dr = Direction::RIGHT;
		break;
	case 'x': case 'X':
		dr = Direction::DOWN;
		break;
	case 'w': case 'W':
		dr = Direction::UP;
		break;
	case 's': case 'S':
		dr = Direction::NONE;
		break;
	}

	return dr;
}
