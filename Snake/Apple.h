#pragma once
#include"SFML/Graphics.hpp"

class Apple
{
private:
	sf::RectangleShape apple;

public:
	Apple();

	sf::RectangleShape& GetApple();

	void PrintApple(sf::RenderWindow& window)
	{
		window.draw(this->apple);
	}
};