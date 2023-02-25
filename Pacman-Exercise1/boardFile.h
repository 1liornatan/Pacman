#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
#include <queue>
#include "board.h"

namespace fs = std::filesystem;
using string = std::string;

class boardFile {
	std::queue<string*>* queuePtr;

public:

	boardFile() {
		queuePtr = new std::queue<string*>;
	}

	boardFile(const boardFile&) = delete;

	~boardFile() {
		
		if (queuePtr) {
			while (!queuePtr->empty()) {
				delete queuePtr->front();
				queuePtr->pop();
			}
			delete queuePtr;

		}
	}

	void initFileBoard();

	boardFile& operator=(boardFile& _fileBoard) = delete;
	void addMap(string* nextMap);
	string* getNextMap();
	static Board* fileToBoard(string& fileName);
	void initReplayFileBoard();

private:
	static void addToStr(string& dest, string& src, int amount);
};