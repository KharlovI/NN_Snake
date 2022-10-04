#pragma once
#include"SFML/Graphics.hpp"
#include <vector>

constexpr int FrameLenth = 40;

class Snake
{
private:

	std::vector <sf::RectangleShape> snake;

	int score;
	char direction;
	bool isAlive;

public:

	Snake();

	bool FrameIsWall();
	bool FrameIsBody();

	void Move();


	void SetDirection(char dir);
	void SetStartPositionSnake();
	void SetIsAliveStatus();
	void IncrementScore();
	void AddElementToBody(sf::Vector2f newPosition);

	std::vector <sf::RectangleShape>& GetSnake();
	sf::Vector2f& GetNextPosition();
	bool GetAliveStatus();
	char GetDirection();

	void PrintSnake(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->snake[i]);
		}
	}
};