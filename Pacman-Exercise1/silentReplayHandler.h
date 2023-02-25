#pragma once

#include "replayGameHandler.h"

class silentReplayHandler : public replayGameHandler {

public:
	silentReplayHandler() = delete;
	silentReplayHandler(Board* _boardPtr, GameColor* _colorsPtr, gameLevel _level, std::string* _mapStr) :
		replayGameHandler(_boardPtr, _colorsPtr, _level, _mapStr, gameType::GAME_REPLAY_SILENT) {};

	silentReplayHandler& operator=(const  silentReplayHandler&) = delete;

	gameStatus initGame();
	void moveGhosts();
};