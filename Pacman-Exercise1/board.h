#pragma once

#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include "globalDef.h"
#include "point.h"
#include "color.h"

class Board {
	unsigned char* boardArr;
	int length, width;
	Point scorePos;
	GameColor* colors;

public:
	// ctors
	Board(GameColor* _colors = nullptr) : colors(_colors), scorePos(0, DEFAULT_WIDTH + 2) {
		boardArr = new unsigned char[DEFAULT_WIDTH * DEFAULT_LENGTH + 1];
		length = DEFAULT_LENGTH;
		width = DEFAULT_WIDTH;
		setDefaultBoard();
	};

	Board(const Board& _board) = delete;

	Board(std::string& boardStr, int _length = DEFAULT_LENGTH, int _width = DEFAULT_WIDTH, GameColor* _colors = nullptr)
		: colors(_colors), length(_length), width(_width) {
		int arr_size = (int)boardStr.length() + 1;
		int scoreIndex = findScorePos(boardStr);

		scorePos.setXY(scoreIndex % (length + 1), scoreIndex / (length + 1));
		boardArr = new unsigned char[arr_size];
		memcpy(boardArr, &boardStr[0], arr_size);

		setScoreArea();
	};
	//dtor
	~Board() {
		if (boardArr)
			delete[] boardArr;
	};

	Board& operator=(Board& _board) {

		if (boardArr)
			delete[] boardArr;

		length = _board.getLength();
		width = _board.getWidth();

		int arr_size = (((length + 1) * width) + 1);
		boardArr = new unsigned char[arr_size];
		memcpy(boardArr, _board.getStr(), arr_size);

		scorePos = _board.getScorePos();
		setScoreArea();
	};

	Board& operator=(unsigned char* boardPtr) = delete;
	Board& operator=(std::string boardStr) = delete;

	void print(const Point& pt) const;
	void printAll() const;
	unsigned char getSign(const Point& pt) const;
	unsigned char getSign(int x, int y) const;
	void setSign(const Point& pt, const unsigned char ch);
	short int setBreadCrumbs();
	static void gotoxy(short int x, short int y);
	int getLength() const;
	int getWidth() const;
	unsigned char* getStr();
	Point& getScorePos();
	bool isValidX(short int _x) const;
	bool isValidY(short int _y) const;
	bool isValidXY(short int _x, short int _y) const; // returns if x,y received are valid
	bool isValidXY(const Point& pt1) const; // returns if Point's x,y are valid
	void setColor(GameColor* _colors);
	static int findScorePos(std::string& str);
private:
	void setDefaultBoard();
	void setScoreArea();
};