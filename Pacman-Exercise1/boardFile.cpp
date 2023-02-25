#include "boardFile.h"

const string MAPS_EXT = ".screen";
const string MAPS_PATH = "./";

Board* boardFile::fileToBoard(std::string& fileName) { // transform a file into a board (returns nullptr if file doesnt exists)
	std::ifstream myFile(fileName);
	std::string a, boardStr;
	Board* boardPtr = nullptr;
	Point scoreXY;
	int length, width;

	if (myFile.is_open()) {
		std::getline(myFile, boardStr, '\n');
		length = (int)boardStr.length(); // + 1 for \n
		boardStr += '\n';

		width = 1;
		while (std::getline(myFile, a, '\n')) {
			width++;
			addToStr(boardStr, a, length);
		}

		boardPtr = new Board(boardStr, length, width);
	}
	return boardPtr;
}

void boardFile::addToStr(std::string& dest, std::string& src, int amount) {
	int srcLen = (int)src.length();
	for (srcLen; srcLen < amount; srcLen++) {
		src += space_sign_old;
	}
	src.resize(amount); // remove any extra charachters

	dest += src;
	dest += '\n';
}

void boardFile::initFileBoard() { // fill queue with all board files
	string* currStr;
	string path(MAPS_PATH);
	string ext(MAPS_EXT);

	while (!queuePtr->empty()) { // empty queue before filling
		delete queuePtr->front();
		queuePtr->pop();
	}

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext) {
			currStr = new string;
			*currStr = p.path().stem().string();
			*currStr += ext;
			queuePtr->push(currStr);
		}
	}
}

void boardFile::initReplayFileBoard() { // fill queue with all board files
	string* currStr;
	string path(MAPS_PATH);
	string ext(MAPS_EXT);

	while (!queuePtr->empty()) { // empty queue before filling
		delete queuePtr->front();
		queuePtr->pop();
	}

	for (auto& p : fs::recursive_directory_iterator(path))
	{
		if (p.path().extension() == ext) {
			currStr = new string;
			*currStr = p.path().stem().string();
			if (std::filesystem::exists(*currStr + ".steps")) {
				*currStr += ext;
				queuePtr->push(currStr);
			}
		}
	}
}

void boardFile::addMap(string* nextMap) // manually add map to queue
{
	if(queuePtr)
		queuePtr->push(nextMap);
}

string* boardFile::getNextMap() {
	string* mapStr;

	if (queuePtr->empty())
		return nullptr;

	mapStr = queuePtr->front();
	queuePtr->pop();

	return mapStr;
}