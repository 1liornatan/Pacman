#include "fruit.h"

int Fruit::getCooldown() const
{
	return dataOfFruit.spawnCooldown;
}

int Fruit::getInterval() const
{
	return dataOfFruit.Interval;
}

int Fruit::getLifetime() const
{
	return dataOfFruit.Lifetime;
}

void Fruit::fruitAdvance()
{
	static int fruitInterval = dataOfFruit.Interval;
	if (spawned) {
		if (fruitInterval == 0) {
			moveQueue* movesPtr = this->getQueuePtr();
			Point ptSaver = getXY();

			dataOfFruit.Lifetime--;
			move();
			fruitInterval = dataOfFruit.Interval;

			if (movesPtr) {
				if (movesPtr->getGameMode() == gameType::GAME_REPLAY_SILENT) // dont print if silent
					return;
			}
			getBoard()->print(ptSaver);
			print();
		}
		else
			fruitInterval--;
	}
	else {
		dataOfFruit.spawnCooldown--;
		if (dataOfFruit.spawnCooldown == 0)
			spawned = true;
	}
}

int Fruit::getValue() const
{
	return dataOfFruit.Value;
}

bool Fruit::isSpawned() const {
	return spawned;
}

void Fruit::move() {
	Point nextPt = getXY();
	Direction dr = getNextMove();

	nextPt.move(dr);
	recordMove(dr);

	if (getBoard()->getSign(nextPt) != wall_sign) // overflow validation inside getSign
		setXY(nextPt);
}

void Fruit::setRandomPos() {
	Board const* boardPtr = getBoard();
	short int length = boardPtr->getLength();
	short int width = boardPtr->getWidth();
	short int x, y;

	do {
		x = rand() % length;
		y = rand() % width;
	} while (boardPtr->getSign(x, y) == wall_sign);
	
	setXY(x, y);
}

Direction Fruit::getNextMove() { // if game is a replay pull the next move, otherwise make a random move
	moveQueue* movesPtr = getQueuePtr();
	gameType gameMode;

	if (movesPtr) {
		gameMode = movesPtr->getGameMode();
		if (gameMode == gameType::GAME_REPLAY || gameMode == gameType::GAME_REPLAY_SILENT) {
			return movesPtr->Dequeue();
		}
	}

	return (Direction)(rand() % 4);

}
void Fruit::print() const {
	static int bLength = getBoard()->getLength();
	static int bWidth = getBoard()->getWidth();
	
	Board::gotoxy(getX(), getY());
	GameColor const* colorPtr = getGameColor();

	if (colorPtr != nullptr)
		setTextColor(colorPtr->getFruitColor());

	std::cout << dataOfFruit.Value;
	Board::gotoxy(bLength + SCORE_LENGTH, bWidth + SCORE_WIDTH); // move cursor to bottom right
}