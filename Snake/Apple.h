#pragma once
#include"SFML/Graphics.hpp"

class Apple
{
private:
	sf::CircleShape apple;

public:
	Apple();

	sf::CircleShape& GetApple();
	void SetColor(sf::Color color);

	void PrintApple(sf::RenderWindow& window)
	{
		window.draw(this->apple);
	}
};