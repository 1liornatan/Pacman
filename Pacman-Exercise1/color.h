#pragma once

#include <Windows.h>
#include <iostream>
#include <conio.h>
#include "globalDef.h"

void setTextColor(Color colorToSet);
Color ChooseColor();

class GameColor {
	Color pacman, ghost, wall, food, fruit, score;

public:
	GameColor(Color _pacman = Color::WHITE, Color _ghost = Color::WHITE, Color _wall = Color::WHITE,
		Color _food = Color::WHITE, Color _fruit = Color::WHITE, Color _score = Color::WHITE) :
		pacman(_pacman), ghost(_ghost), wall(_wall), food(_food), fruit(_fruit), score(_score) {};


	void setPacmanColor(const Color color);
	void setGhostColor(const Color color);
	void setWallColor(const Color color);
	void setFoodColor(const Color color);
	void setFruitColor(const Color color);
	void setScoreColor(const Color color);
	Color getPacmanColor() const;
	Color getGhostColor() const;
	Color getWallColor() const;
	Color getFoodColor() const;
	Color getFruitColor() const;
	Color getScoreColor() const;

	void setColorByChar(char ch);
	void resetColors();
};
