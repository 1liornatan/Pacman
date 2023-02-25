#include "recordFile.h"
#include <sstream>

void recordFile::writeMoves(std::ofstream& myFile, moveQueue* src)
{
    if (myFile.is_open()) {
        while (!src->isEmpty()) {
            myFile.put(DirectionChar[(int)src->Dequeue()]); // pull all chars from queue and put them in file
        }
        myFile.put('\n');
    }
}
void recordFile::writeFruitData(std::ofstream& myFile, fruitQueueHandler* fruitQueue) {
    Point pos = fruitQueue->getPos();
    fruitData dataOfFruit = fruitQueue->getFruitData();
    moveQueue* fruitMoves = fruitQueue->getQueuePtr();

    if (myFile.is_open()) {
        myFile << pos.getX() << " " << pos.getY() << " " << dataOfFruit.Value << " " << dataOfFruit.Lifetime << " " << dataOfFruit.spawnCooldown << " ";
        myFile << dataOfFruit.Interval << " ";
        writeMoves(myFile, fruitMoves); // write fruit moves
    }
}

void recordFile::readMoves(std::ifstream& myFile, moveQueue* movesQueue)
{
    std::string currLine;
    int length;
    Direction dr;
    if (myFile.is_open()) {
        
        std::getline(myFile, currLine);
        length = currLine.length();

        for (int i = 0; i < length; i++) {
            movesQueue->Push(moveQueue::getDirection(currLine[i]));            
        }
    }
}

fruitQueueHandler* recordFile::readFruitData(std::stringstream& ss, const gameType& gameMode = gameType::GAME_RECORD) {
    int x, y, strLen;
    fruitData dataOfFruit;
    fruitQueueHandler* fruitQueue = nullptr;
    std::string movesStr;
    moveQueue* currQueue;

    ss >> x;
    ss >> y;
    ss >> dataOfFruit.Value;
    ss >> dataOfFruit.Lifetime;
    ss >> dataOfFruit.spawnCooldown;
    ss >> dataOfFruit.Interval;

    fruitQueue = new fruitQueueHandler(dataOfFruit, Point(x, y), gameMode);
    currQueue = fruitQueue->getQueuePtr();

    ss >> movesStr;
    strLen = movesStr.length();

    for (int i = 0; i < strLen; i++) {
        currQueue->Push(moveQueue::getDirection(movesStr[i]));
    }

    return fruitQueue;
}

