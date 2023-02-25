#include "game.h"

void Game::PlayReplay() {
	bFile.initReplayFileBoard();
	Start();

	if (gameMode == gameType::GAME_REPLAY_SILENT) {
		if (testResult) {
			std::cout << "Test Succeeded\n";
		}
		else {
			std::cout << "Test Failed\n";
		}
	}
}
void Game::Start() {
	bool gameOver = false;
	short int lives, score;
	gameStatus status;
	string* nextMap = bFile.getNextMap();
	Board* nextBoard;
	gameHandler* gameInstancePtr;
	int stepsCounter = 0, eventCounter = 0, boardWidth;

	if (nextMap == nullptr)
		return;

	nextBoard = boardFile::fileToBoard(*nextMap);

	if (nextBoard == nullptr) {
		mapNotFound();
		delete nextMap; // free map string
		return;
	}
	nextBoard->setColor(colorsPtr);
	  
	gameInstancePtr = getHandlerPtr(nextBoard, colorsPtr, level, nextMap);

	while (!gameOver) {
		status = gameInstancePtr->initGame();

		switch (status) {
		case gameStatus::GAME_PAUSED:
			stepsCounter += gameInstancePtr->getSteps();
			Pause();
			break;
		case gameStatus::GAME_WIN:
			stepsCounter += gameInstancePtr->getSteps();
			WriteWinInFile(*nextMap, stepsCounter);
			checkResult(*nextMap, stepsCounter, ++eventCounter, gameStatus::GAME_WIN);
			nextMap = bFile.getNextMap();
			eventCounter = 0;
			if (nextMap == nullptr) {
				Board::gotoxy(0, nextBoard->getWidth() + 2); // reset position on screen
				Win();
				gameOver = true;
			}
			else {
				lives = gameInstancePtr->getLives(); // save score and lives
				score = gameInstancePtr->getScore();

				delete gameInstancePtr;
				nextBoard = boardFile::fileToBoard(*nextMap);

				gameInstancePtr = getHandlerPtr(nextBoard, colorsPtr, level, nextMap); // advance to the next map

				gameInstancePtr->setLives(lives); // put back the score and lives
				gameInstancePtr->setScore(score);
			}
			break;
		case gameStatus::GAME_LOSE:
			stepsCounter += gameInstancePtr->getSteps();
			WriteLoseInFile(*nextMap, stepsCounter);
			checkResult(*nextMap, stepsCounter, ++eventCounter, gameStatus::GAME_LOSE);
			lives = gameInstancePtr->getLives();
			lives--;

			if (lives == 0) {
				Board::gotoxy(0, nextBoard->getWidth() + 2); // reset position on screen
				Lose();
				gameOver = true;
			}
			else {
				gameInstancePtr->setLives(lives);
				gameInstancePtr->setPositions();
			}
			break;
		case gameStatus::GAME_STOP: {
			gameOver = true;
		}
		}
	}

	if (gameInstancePtr)
		delete gameInstancePtr;
}

void Game::specificMap()
{
	string* mapName = nullptr;
	system("cls");
	std::cout << "Enter full map file name:" << std::endl;
	
	mapName = new string;

	std::getline(std::cin, *mapName);

	bFile.addMap(mapName);
	Start();
}

void Game::Pause() {
	system("cls");
	std::cout << "Game is Paused. Click ESC to resume." << std::endl;
	int button;
	while (!_kbhit() || (button = _getch()) != ESC) {
		Sleep(1000);
	}
}

void Game::Win() {
	int button;
	if (gameMode != gameType::GAME_REPLAY && gameMode != gameType::GAME_REPLAY_SILENT) {
		std::cout << "Congratulations, You Win!\nPress Any Key to Continue." << std::endl;
		button = _getch();
	}
}

void Game::Lose() {
	int button;
	
	if (gameMode != gameType::GAME_REPLAY && gameMode != gameType::GAME_REPLAY_SILENT) {
		std::cout << "Game Over! You Lost.\nPress Any Key to Continue." << std::endl;
		button = _getch();
	}
}

void Game::mapNotFound() {
	int button;
	system("cls");
	std::cout << "Map Not Found!\nPress Any Key to Continue." << std::endl;
	button = _getch();
}
void Game::Menu() {
	bool exit = false;
	while (!exit) {

		system("cls");
		std::cout << "Welcome to Pacman! Choose Your Option:" << std::endl;
		std::cout << "(1) Start a new game" << std::endl;
		std::cout << "(2) Play a specific map" << std::endl;
		std::cout << "(3) Color Settings" << std::endl;
		std::cout << "\n(7) Game Level [" << gameLevelName[(int)level] << "]" << std::endl;
		std::cout << "(8) Present instructions and keys" << std::endl;
		std::cout << "(9) EXIT" << std::endl;

		switch (_getch()) {
		case KEY_1: {
			bFile.initFileBoard();
			Start();
			break;
		}
		case KEY_2: {
			specificMap();
			break;
		}
		case KEY_3: {
			if (!colorsPtr)
				colorsPtr = new GameColor();
			ColorsMenu();
			break;
		}
		case KEY_7: {
			level = (gameLevel)((int)level + 1);
			if (level == gameLevel::COUNT)
				level = (gameLevel)0;
			break;
		}
		case KEY_8: {
			Keys();
			break;
		}
		case KEY_9: {
			exit = true;
			break;
		}
		}
	}
}

void Game::ColorsMenu() {
	bool exit = false;
	while (!exit) {
		system("cls");
		std::cout << "Choose What Color To Change:" << std::endl;
		std::cout << "(1) Board" << std::endl;
		std::cout << "(2) Pacman" << std::endl;
		std::cout << "(3) Ghost" << std::endl;
		std::cout << "(4) Fruit" << std::endl;
		std::cout << "(5) Score" << std::endl;
		std::cout << "\n(8) Restore All Defaults (WHITE)" << std::endl;
		std::cout << "(9) Return To Menu" << std::endl;

		switch (_getch()) {
		case KEY_1: {
			colorsPtr->setWallColor(ChooseColor());
			break;
		}
		case KEY_2: {
			colorsPtr->setPacmanColor(ChooseColor());
			break;
		}
		case KEY_3: {
			colorsPtr->setGhostColor(ChooseColor());
			break;
		}
		case KEY_4: {
			colorsPtr->setFruitColor(ChooseColor());
			break;
		}
		case KEY_5: {
			colorsPtr->setScoreColor(ChooseColor());
			break;
		}
		case KEY_8: {
			delete colorsPtr;
			colorsPtr = nullptr;
			exit = true;
			break;
		}
		case KEY_9: {
			exit = true;
			break;
		}
		default: {
			exit = false;
			break;
		}
		}
	}
}
void Game::Keys() {
	system("cls");
	std::cout << "Move around the map and gather all breadcrumbs without colliding with a ghost." << std::endl;
	std::cout << "LEFT - a or A\nRIGHT - d or D\nUP - w or W\nDOWN - x or X\nSTAY - s or S" << std::endl;
	std::cout << "\nPress ESC to return to the Menu." << std::endl;
	while (_getch() != ESC) {
		Sleep(1000);
	}
}

gameHandler* Game::getHandlerPtr(Board* _boardPtr, GameColor* _colorsPtr, const gameLevel& _level, string* currMap) {
	gameHandler* gameInstancePtr = nullptr;
	std::size_t extPos;

	extPos = currMap->find(".screen");
	currMap->erase(currMap->begin() + extPos, currMap->end());

	switch (gameMode) {
	case(gameType::GAME_NORMAL): {
		gameInstancePtr = new normalGameHandler(_boardPtr, _colorsPtr, _level);
		break;
	}
	case(gameType::GAME_RECORD): {
		gameInstancePtr = new recordGameHandler(_boardPtr, _colorsPtr, _level, currMap);
		break;
	}
	case(gameType::GAME_REPLAY): {
		gameInstancePtr = new normalReplayHandler(_boardPtr, _colorsPtr, _level, currMap);
		break;
	}
	case(gameType::GAME_REPLAY_SILENT): {
		gameInstancePtr = new silentReplayHandler(_boardPtr, _colorsPtr, _level, currMap);
		break;
	}
	}

	return gameInstancePtr;
}

void Game::WriteLoseInFile(string mapName, int steps) {

	std::ofstream myFile;

	if (gameMode == gameType::GAME_RECORD) {
		mapName += ".result";
		myFile.open(mapName, std::ofstream::out | std::ofstream::app); // write to file without removing

		if (myFile.is_open()) {
			myFile << steps << " " << gameStatusChar[(int)gameStatus::GAME_LOSE] << "\n";
		}

		myFile.close();
	}
}

void Game::WriteWinInFile(string mapName, int steps) {

	std::ofstream myFile;

	if (gameMode == gameType::GAME_RECORD) {
		mapName += ".result";
		myFile.open(mapName, std::ofstream::out | std::ofstream::app); // write to file without removing

		if (myFile.is_open()) {
			myFile << steps << " " << gameStatusChar[(int)gameStatus::GAME_WIN] << "\n";
		}
		myFile.close();
	}
}

void Game::checkResult(string mapName, int steps, int event, gameStatus status) {
	static std::ifstream myFile;
	char resultChar;
	int fileSteps;

	if (gameMode == gameType::GAME_REPLAY_SILENT) {
		myFile.open(mapName + ".result");
		if (myFile.is_open()) {
			string currLine;

			for(int i = 0; i < event; i++)
				std::getline(myFile, currLine);

			std::stringstream ss(currLine);
			ss >> fileSteps;
			ss >> resultChar;

			if (fileSteps != steps || gameStatusChar[(int)status] != resultChar)
				testResult = false;
		}
		myFile.close();
	}
}