#include "board.h"

void Board::printAll() const {
	int x, y;
	system("cls");
	if (colors) {
		_flushall();
		setTextColor(colors->getWallColor());
	}
	std::cout << boardArr << std::endl;

	x = scorePos.getX();
	y = scorePos.getY();

	// clear score box
	for (int i = 0; i < 3; i++) {
		gotoxy(x, y + i);
		std::cout << "                    " << std::endl;
	}
}
void Board::print(const Point& pt) const {
	gotoxy(pt.getX(), pt.getY());
	if (colors)
		setTextColor(colors->getWallColor());
	std::cout << boardArr[pt.getX() + pt.getY() * (length + 1)];
	gotoxy(length + SCORE_LENGTH, width + SCORE_WIDTH); // move cursor to bottom left
}

void Board::setDefaultBoard() {
	for (int i = 0; i < (DEFAULT_WIDTH * DEFAULT_LENGTH + 1); i++) {
		boardArr[i] = defaultBoard[i];
	}
}
unsigned char Board::getSign(const Point& pt) const {
	return getSign(pt.getX(), pt.getY());
}

unsigned char Board::getSign(int _x, int _y) const {
	if (isValidXY(_x, _y))
		return boardArr[_x + _y * (length + 1)];

	return wall_sign;
}
void Board::setSign(const Point& pt, unsigned char ch) {
	if (isValidXY(pt)) {
		boardArr[pt.getX() + pt.getY() * (length + 1)] = ch;
	}
}

bool Board::isValidX(short int _x) const {
	return (_x >= 0) && (_x < (length));
}

bool Board::isValidY(short int _y) const {
	return (_y >= 0) && (_y < (width));
}

bool Board::isValidXY(short int _x, short int _y) const {
	return isValidX(_x) && isValidY(_y);
}

bool Board::isValidXY(const Point& pt1) const {
	return isValidX(pt1.getX()) && isValidY(pt1.getY());
}

void Board::setColor(GameColor* _colors)
{
	colors = _colors;
}


void Board::gotoxy(short int x, short int y) {
	static HANDLE hConsoleOutput = NULL;
	if (NULL == hConsoleOutput)
		hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

	COORD dwCursorPosition = { x, y };
	std::cout.flush();
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

short int Board::setBreadCrumbs() {
	short int i, counter = 0;

	for (i = 0; i < (width * (length + 1)); i++) {
		switch (boardArr[i]) {
		case space_sign: {
			boardArr[i] = food_sign;
			counter++;
			break;
		}
		case space_sign_old: {
			boardArr[i] = space_sign;
			break;
		}
		case wall_sign_old: {
			boardArr[i] = wall_sign;
			break;
		}
		}
	}

	return counter;
}

int Board::getLength() const {
	return length;
}

int Board::getWidth() const {
	return width;
}

unsigned char* Board::getStr() {
	return boardArr;
}

Point& Board::getScorePos() {
	return scorePos;
}

int Board::findScorePos(std::string& str) {
	int len = (int)str.length();
	for (int i = 0; i < len; i++) {
		if (str[i] == score_sign) {
			return i;
		}
	}
	return len;
}

void Board::setScoreArea() {
	int scorePosX = scorePos.getX();
	int scorePosY = scorePos.getY();
	for (int i = 0; i < SCORE_WIDTH; i++) {
		for (int j = 0; j < SCORE_LENGTH; j++) {
			if (isValidXY(scorePosX + j, scorePosY + i)) {
				boardArr[scorePosX + j + ((scorePosY + i) * (length + 1))] = score_sign;
			}
			else {
				break;
			}
		}
	}
}