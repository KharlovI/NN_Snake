#pragma once
#include "Snake.h"
#include "Button.h"

bool AllSnakesIsDead(Snake snakes[], int count);
int FirstAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS, sf::Sprite& appleSprite, std::vector<sf::Sprite> snakeSprites);
int SecondAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS, sf::Sprite& appleSprite, std::vector<sf::Sprite> snakeSprites);
int ThirdAction(std::vector<Button> b, sf::RenderWindow& w, int& curFPS, sf::Sprite& appleSprite, std::vector<sf::Sprite> snakeSprites);