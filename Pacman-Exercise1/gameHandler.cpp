#include "gameHandler.h"

short int gameHandler::getLives() const {
	return lives;
}

void gameHandler::setLives(short int _lives) {
	lives = _lives;
}

void gameHandler::setScore(short int _score)
{
	score = _score;
}

short int gameHandler::getScore() const
{
	return score;
}

void gameHandler::setGameUnits() {
	int size;
	short int x, y, length, width;

	if (boardPtr) {
		length = boardPtr->getLength();
		width = boardPtr->getWidth();
		size = ((length+1) * width);

		for (int i = 0; i < size; i++) {
			x = i % (length);
			y = i / (length);

			switch (boardPtr->getSign(x, y)) {
			case pacman_sign: {
				if (!pacmanPtr) {
					pacmanPtr = new Pacman(boardPtr, nullptr, colorsPtr, x, y);
					boardPtr->setSign(pacmanPtr->getXY(), space_sign_old);
				}
				break;
			}
			case ghost_sign: {
				if (ghostsAmount < MAX_GHOSTS) {
					switch (level) {
						case gameLevel::GAME_HARD: {
							ghostPtrArr[ghostsAmount] = new ghostBest(boardPtr, nullptr, colorsPtr, x, y);
							break;
						}
						case gameLevel::GAME_MEDIUM: {
							ghostPtrArr[ghostsAmount] = new ghostGood(boardPtr, nullptr, colorsPtr, x, y);
							break;
						}
						case gameLevel::GAME_EASY: {
							ghostPtrArr[ghostsAmount] = new ghostNovice(boardPtr, nullptr, colorsPtr, x, y);
							break;
						}
					}
					boardPtr->setSign(ghostPtrArr[ghostsAmount]->getXY(), space_sign_old);
					ghostsAmount++;
				}
				break;
			}
			}
		}

		if (!pacmanPtr) { // no pacman in file
			setRandomPacman();
		}
		for (int i = 0; i < ghostsAmount; i++) {
			ghostPtrArr[i]->setPacman(pacmanPtr);
		}

	}
}

void gameHandler::setRandomPacman() {
	short int length = boardPtr->getLength();
	short int width = boardPtr->getWidth();
	short int x, y;

	do {
		x = rand() % length;
		y = rand() % width;
	} while (boardPtr->getSign(x, y) == wall_sign_old);

	pacmanPtr = new Pacman(boardPtr, nullptr, colorsPtr, x, y);
}

void gameHandler::setPositions() {
	int i;
	bool isSilent = false;
	moveQueue* movesPtr;
	if ((movesPtr = pacmanPtr->getQueuePtr())) {
		isSilent = (movesPtr->getGameMode() == gameType::GAME_REPLAY_SILENT);
	}
	for (i = 0; i < ghostsAmount; i++) {
		ghostPtrArr[i]->resetXY();
		if(!isSilent)
			boardPtr->print(ghostPtrArr[i]->getXY());
	}

	if (!isSilent)
		boardPtr->print(pacmanPtr->getXY());

	pacmanPtr->resetXY();
}

bool gameHandler::checkCollision() {
	Point& pacmanPos = pacmanPtr->getXY();

	for (int i = 0; i < ghostsAmount; i++) {
		if (ghostPtrArr[i]->getXY() == pacmanPos) {
			return true;
		}
	}
	return false;
}

void gameHandler::checkEat(Point& pt) {
	unsigned char sign;

	if (fruitPtr) {
		if (fruitPtr->isSpawned() && fruitPtr->getXY() == pt) {
			score += fruitPtr->getValue();
			delete fruitPtr;
			fruitPtr = nullptr;
		}
	}

	sign = boardPtr->getSign(pt);
	if (sign == food_sign) {
		score++;
		breadCrumbs--;
		boardPtr->setSign(pt, space_sign); // clear last position
	}
}

void gameHandler::printGhosts() const {
	for (int i = 0; i < ghostsAmount; i++) {
		ghostPtrArr[i]->print();
	}
}
void gameHandler::printScore() {
	int x = boardPtr->getScorePos().getX();
	int y = boardPtr->getScorePos().getY();

	if (colorsPtr != nullptr)
		setTextColor(colorsPtr->getScoreColor());

	Board::gotoxy(x, y);
	std::cout << "Remaining Lives: " << lives << std::endl;
	Board::gotoxy(x, y + 1);
	std::cout << "Score: " << score << std::endl;


}

void gameHandler::checkFruitGhostCollision() {
	if (fruitPtr) {
		for (int i = 0; i < ghostsAmount; i++) {
			if (fruitPtr->isSpawned() && fruitPtr->getXY() == ghostPtrArr[i]->getXY()) {
				delete fruitPtr;
				fruitPtr = nullptr;
				return;
			}
		}
	}
}
void gameHandler::makeGhostsMove() {
	int i;

	Point& pacmanPt = pacmanPtr->getXY();
	Point currGhostPt;

	for (i = 0; i < ghostsAmount; i++) {
		currGhostPt = ghostPtrArr[i]->getXY();
		if(pacmanPt != currGhostPt) // to no override pacmans symbol on board
			boardPtr->print(currGhostPt); 
		ghostPtrArr[i]->move();
		ghostPtrArr[i]->print();
	}
}

Ghost** gameHandler::getGhostPtrArr()
{
	return ghostPtrArr;
}

short int gameHandler::getGhostsAmount() {
	int i;
	for (i = 0; i < 4; i++) {
		if (ghostPtrArr[i] == nullptr)
			return i;
	}
	return i;
}