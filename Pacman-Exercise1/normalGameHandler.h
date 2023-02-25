#pragma once

#include "gameHandler.h"

class normalGameHandler : public gameHandler {

public:
	normalGameHandler() = delete;
	normalGameHandler(Board* _boardPtr, GameColor* _colorsPtr = nullptr, gameLevel _level = gameLevel::GAME_HARD) :
		gameHandler(_boardPtr, _colorsPtr, _level) {};

	Direction getDirection(int button);

	gameStatus initGame() override;
};