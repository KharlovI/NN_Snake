#include "Apple.h"

struct Coordinates
{
	int x;
	int y;
};

Apple::Apple()
{
	this->apple.setRadius(20);
	this->apple.setFillColor(sf::Color::Red);
	this->apple.setPosition(0, 0);
}

sf::CircleShape& Apple::GetApple()
{
	return this->apple;
}

void Apple::SetColor(sf::Color color)
{
	this->apple.setFillColor(color);
}