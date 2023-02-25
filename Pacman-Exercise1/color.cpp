#include "color.h"

void GameColor::resetColors() {
	pacman = ghost = wall = food = Color::WHITE;
}

void setTextColor(Color colorToSet) {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}

void GameColor::setColorByChar(char ch) {
	Color colorToSet;
	switch (ch) {
	case pacman_sign:
		colorToSet = pacman;
		break;
	case wall_sign:
		colorToSet = wall;
		break;
	case ghost_sign:
		colorToSet = ghost;
		break;
	case food_sign:
		colorToSet = food;
		break;
	default:
		colorToSet = Color::WHITE;
	}

	setTextColor(colorToSet);
}

Color ChooseColor() {

	system("cls");
	std::cout << "Choose A Color:" << std::endl;
	std::cout << "(1) Blue" << std::endl;
	std::cout << "(2) Red" << std::endl;
	std::cout << "(3) Green" << std::endl;
	std::cout << "(4) Yellow" << std::endl;
	std::cout << "(5) Brown" << std::endl;
	std::cout << "(6) Light Blue" << std::endl;
	std::cout << "(7) White" << std::endl;

	switch (_getch()) {
	case '1':
		return Color::BLUE;
		break;
	case '2':
		return Color::RED;
		break;
	case '3':
		return Color::GREEN;
		break;
	case '4':
		return Color::YELLOW;
		break;
	case '5':
		return Color::BROWN;
		break;
	case '6':
		return Color::LIGHTBLUE;
		break;
	case '7':
		return Color::WHITE;
		break;
	default:
		return ChooseColor();
	}
}


void GameColor::setPacmanColor(const Color color) {
	pacman = color;
}
void GameColor::setGhostColor(const Color color) {
	ghost = color;
}
void GameColor::setWallColor(const Color color) {
	wall = color;
}
void GameColor::setFoodColor(const Color color) {
	food = color;
}
void GameColor::setFruitColor(const Color color) {
	fruit = color;
}

void GameColor::setScoreColor(const Color color)
{
	score = color;
}

Color GameColor::getPacmanColor() const {
	return pacman;
}
Color GameColor::getGhostColor() const {
	return ghost;
}
Color GameColor::getWallColor() const {
	return wall;
}
Color GameColor::getFoodColor() const {
	return food;
}
Color GameColor::getFruitColor() const {
	return fruit;
}

Color GameColor::getScoreColor() const
{
	return score;
}
