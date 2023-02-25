#include <iostream>
#include "game.h"
#include "boardFile.h"

int main(int argc, char** argv) {
	
	gameType loadMode = gameType::GAME_NORMAL;
	bool isReplay = false;

	if (argc > 1 && strcmp(argv[1], "-save") == 0) {
		loadMode = gameType::GAME_RECORD;
	}
	else if (argc > 1 && strcmp(argv[1], "-load") == 0) {
		if(argc > 2 && strcmp(argv[2], "-silent") == 0) {
			loadMode = gameType::GAME_REPLAY_SILENT;
		}
		else {
			loadMode = gameType::GAME_REPLAY;
		}
		isReplay = true;
	}

	_flushall();
	Game game(loadMode);

	if (isReplay)
		game.PlayReplay();
	else
		game.Menu();

	return 0;
}