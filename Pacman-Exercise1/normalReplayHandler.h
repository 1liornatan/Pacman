#pragma once

#include "replayGameHandler.h"

class normalReplayHandler : public replayGameHandler {

public:
	normalReplayHandler() = delete;
	normalReplayHandler(Board* _boardPtr, GameColor* _colorsPtr, gameLevel _level, std::string* _mapStr) :
		replayGameHandler(_boardPtr, _colorsPtr, _level, _mapStr) {};

	normalReplayHandler& operator=(const normalReplayHandler&) = delete;

	gameStatus initGame();
	void moveGhosts();
};