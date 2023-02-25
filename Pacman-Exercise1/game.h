#pragma once

#include "pacman.h"
#include "ghostUnit.h"
#include "boardFile.h"
#include "board.h"
#include "recordGameHandler.h"
#include "normalGameHandler.h"
#include "silentReplayHandler.h"
#include "normalReplayHandler.h"


class Game {
	GameColor* colorsPtr;
	gameLevel level;
	boardFile bFile;
	gameType gameMode;

	bool testResult;
public:
	Game(gameType _gameMode = gameType::GAME_NORMAL) : gameMode(_gameMode) {
		level = gameLevel::GAME_HARD;
		colorsPtr = nullptr;
		srand((unsigned int)time(NULL)); // generate random seed
		testResult = true;
	};
	~Game() {
		if (colorsPtr)
			delete colorsPtr;
	};
	void Menu();
	void PlayReplay();
private:
	void Start();
	void specificMap();
	void Pause();
	void Win();
	void Lose();
	void Keys();
	void mapNotFound();
	void ColorsMenu();
	void WriteLoseInFile(string mapName, int steps);
	void WriteWinInFile(string mapName, int steps);
	void checkResult(string mapName, int steps, int event, gameStatus status);
	gameHandler* getHandlerPtr(Board* _boardPtr, GameColor* _colorsPtr, const gameLevel& _level, string* currMap);
};