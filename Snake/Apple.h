#pragma once
#include"SFML/Graphics.hpp"

class Apple
{
private:
	sf::CircleShape apple;
	sf::Sprite aS;
public:
	Apple();
	
	sf::CircleShape& GetApple();
	sf::Sprite& GetAS() { return this->aS; }
	void SetColor(sf::Color color);
	void SetSprite(sf::Sprite& appleSprite);

	void PrintAppleSprite(sf::RenderWindow& window)
	{
		window.draw(aS);
	}
	void PrintAppleShape(sf::RenderWindow& window)
	{
		window.draw(apple);
	}

	void SetPosition(sf::Vector2f position);
	sf::Vector2f GetPosition();
};