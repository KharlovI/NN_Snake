#include "Apple.h"

struct Coordinates
{
	int x;
	int y;
};

Apple::Apple()
{
	this->apple.setSize(sf::Vector2f(40, 40));
	this->apple.setFillColor(sf::Color::Red);
	this->apple.setPosition(0, 0);
}

sf::RectangleShape& Apple::GetApple()
{
	return this->apple;
}