#pragma once


const short int DEFAULT_LENGTH = 81;
const short int DEFAULT_WIDTH = 25;
const unsigned char wall_sign = 219;
const unsigned char food_sign = 250;
const int TIME_INTERVAL = 10; // lower value results in a faster game
const unsigned char pacman_sign = '@';
const unsigned char ghost_sign = '$';
const unsigned char wall_sign_old = '#';
const unsigned char score_sign = '&';
const unsigned char space_sign = ' ';
const unsigned char space_sign_old = '%';
const int ESC = 27;
const int SCORE_LENGTH = 20; // score box size
const int SCORE_WIDTH = 3;
const short int MAX_GHOSTS = 4;
const int goodGhostInterval = 20;
const int FRUIT_MIN_LIFETIME = 30;
const int FRUIT_MAX_LIFETIME = 60;
const int FRUIT_MAX_INTERVAL = 5;
const int FRUIT_MAX_SPAWN_CD = 25;
const int FRUIT_MIN_SPAWN_CD = 15;
const int FRUIT_MAX_VAL = 9;
const int FRUIT_MIN_VAL = 5;

const unsigned char defaultBoard[DEFAULT_WIDTH * DEFAULT_LENGTH + 1] = {
	//01234567890123456789012345678901234567890123456789012345678901234567890123456789\n
	 "#####################################      #####################################\n"
	 "#                                                                              #\n"
	 "#                                                                              #\n"
	 "#      ##########################            ##########################        #\n"
	 "#                  ###                 $                  ###                  #\n"
	 "#######            ###                                    ###            #######\n"
	 "#                  ###                                    ###                  #\n"
	 "#                  ###      ########       ########       ###                  #\n"
	 "#                                                                              #\n"
	 "#                                                                              #\n"
	 "#            #####################################################             #\n"
	 "                             #&%%%%%%%%%%%%%%%%%%%#                             \n"
	 "       $                     #%%%%%%%%%%%%%%%%%%%%#                     $       \n"
	 "                             #%%%%%%%%%%%%%%%%%%%%#                             \n"
	 "#            #####################################################             #\n"
	 "#                                                                              #\n"
	 "#                                                                              #\n"
	 "#                  ###      ########       ########       ###                  #\n"
	 "#                  ###                                    ###                  #\n"
	 "#######            ###                                    ###            #######\n"
	 "#                  ###                                    ###                  #\n"
	 "#       ##########################     $      ##########################       #\n"
	 "#                                                                              #\n"
	 "#                                                                              #\n"
	 "#####################################      #####################################\n"
};

enum Keys { KEY_0 = '0', KEY_1, KEY_2, KEY_3, KEY_4, KEY_5, KEY_6, KEY_7, KEY_8, KEY_9 };

enum class Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15
};

enum class Direction {
	NONE = -1,
	LEFT,
	RIGHT,
	UP,
	DOWN,
	STAY
};

const char DirectionChar[5]{
	'A',
	'D',
	'W',
	'X',
	'S'
};

enum class gameType {
	GAME_NORMAL,
	GAME_RECORD,
	GAME_REPLAY,
	GAME_REPLAY_SILENT
};

enum class gameStatus {
	GAME_PAUSED,
	GAME_WIN,
	GAME_LOSE,
	GAME_STOP
};

const char gameStatusChar[4] {
	'P',
	'W',
	'L',
	'S'
};
enum class gameLevel {
	GAME_HARD,
	GAME_MEDIUM,
	GAME_EASY,
	COUNT
};

const char gameLevelName[(int)gameLevel::COUNT][20] = {
	"BEST",
	"GOOD",
	"NOVICE"
};