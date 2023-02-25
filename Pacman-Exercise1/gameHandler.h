#pragma once

#include "ghostUnit.h"
#include "pacman.h"
#include "fruit.h"
#include "board.h"

class gameHandler {
	short int lives, score, ghostsAmount;
	gameStatus status;
	gameLevel level;

protected:
	Board* boardPtr;
	GameColor* colorsPtr;
	Pacman* pacmanPtr;
	Ghost** ghostPtrArr;
	Fruit* fruitPtr;

	int stepsCounter;
	short int breadCrumbs;

public:
	gameHandler() = delete;
	gameHandler(Board* _boardPtr, GameColor* _colorsPtr = nullptr, gameLevel _level = gameLevel::GAME_HARD) :
		boardPtr(_boardPtr), colorsPtr(_colorsPtr), level(_level) {

		ghostPtrArr = new Ghost * [MAX_GHOSTS];

		for (int i = 0; i < MAX_GHOSTS; i++)
			ghostPtrArr[i] = nullptr;

		fruitPtr = nullptr;
		score = 0;
		lives = 3;
		setGameUnits();
		breadCrumbs = boardPtr->setBreadCrumbs();
		ghostsAmount = getGhostsAmount();
	}
	
	gameHandler(const gameHandler&) = delete;
	
	gameHandler& operator=(gameHandler&) = delete;

	virtual ~gameHandler() {
		if (boardPtr)
			delete boardPtr;

		if (pacmanPtr)
			delete pacmanPtr;

		if (fruitPtr)
			delete fruitPtr;

		for (int i = 0; i < ghostsAmount; i++)
			delete ghostPtrArr[i];

		delete[] ghostPtrArr;
	}

	virtual gameStatus initGame() = 0;
	void setPositions();
	short int getLives() const;
	void setLives(short int _lives);
	void setScore(short int _score);
	short int getScore() const;
	inline int getSteps() const { return stepsCounter; };

private:
	void setGameUnits();
	void setRandomPacman();

protected:
	Ghost** getGhostPtrArr();
	short int getGhostsAmount();
	void printScore();
	void printGhosts() const;
	void checkEat(Point& pt); // check if bread crumb eaten and clear last location
	void makeGhostsMove();
	bool checkCollision();
	void checkFruitGhostCollision();
};
