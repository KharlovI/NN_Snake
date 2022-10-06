#pragma once
#include"SFML/Graphics.hpp"
#include <vector>
#include"Genotyp.h"

/// <Заметка>
/// 1) Сделать выбор направления
/// 2) Переделаь движение
/// 3) Сделать счетчик времени 
/// 4) Обучение змеи
/// </summary>



constexpr int FrameLenth = 40;

class Snake
{
private:

	std::vector <sf::RectangleShape> snake;

	Genotyp genotyp;

	int countOfApple;
	float aliveTime;
	float totalScore;

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
	float GetTotalScore();
	Genotyp& GetGenotyp();

	void PrintSnake(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->snake[i]);
		}
	}



	// Сделать !!!!

	float DistanceToWall();
	float DistanceToTail();
	float DistanceToApple();
};

Genotyp* GetBestParrents(Snake generation[]);