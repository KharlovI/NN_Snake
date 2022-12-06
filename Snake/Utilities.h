#pragma once
#include "Snake.h"
#include "Button.h"

bool AllSnakesIsDead(Snake snakes[], int count);
int FirstAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS);
int SecondAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS);
int ThirdAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS);