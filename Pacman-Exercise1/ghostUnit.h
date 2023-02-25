#pragma once

#include "ghost.h"

class ghostBest : public Ghost {

public:

	ghostBest(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = -1, short int _y = -1, Pacman* _pacmanPtr = nullptr) :
		Ghost(_board, _moveQueuePtr, _colors, _x, _y, _pacmanPtr) {};

	void move() override {
		if(!replayMove())
			smartMove();
	};
};

class ghostNovice : public Ghost {

public:

	ghostNovice(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = -1, short int _y = -1, Pacman* _pacmanPtr = nullptr) :
		Ghost(_board, _moveQueuePtr, _colors, _x, _y, _pacmanPtr) {};

	void move() override {
		if(!replayMove())
			dummyMove((Direction)(rand() % 4));
	}
};

class ghostGood : public Ghost {
	int smartInterval;
	int dummySteps;
	Direction dr;

public:

	ghostGood(Board* _board = nullptr, moveQueue* _moveQueuePtr = nullptr, GameColor* _colors = nullptr, short int _x = -1, short int _y = -1, Pacman* _pacmanPtr = nullptr) :
		Ghost(_board, _moveQueuePtr, _colors, _x, _y, _pacmanPtr) {
		smartInterval = 20;
		dummySteps = 5;
		dr = (Direction)(rand() % 4);
	};

	void move() override {
		if (!replayMove()) {
			if (smartInterval == 0) {
				if (dummySteps == 0) {
					smartInterval = 20;
					dummySteps = 5;
					dr = (Direction)(rand() % 4);
				}
				else {
					dummySteps--;
				}
				dummyMove(dr);
			}
			else {
				smartMove();
				smartInterval--;
			}
		}
	};
};
