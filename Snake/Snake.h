#pragma once
#include"SFML/Graphics.hpp"
#include <vector>
#include"Genotype.h"
#include "Apple.h"

/// <�������>
/// 1) ������� ����� �����������
/// 2) ��������� ��������
/// 3) ������� ������� ������� 
/// 4) �������� ����
/// </summary>



constexpr int FrameLength = 40;

class Snake
{
private:

	std::vector <sf::RectangleShape> snake;

	int generation;
	Genotype genotype;

	int countOfApple;
	float aliveTime;
	float totalScore;

	char direction;
	bool isAlive;

public:

	Snake();															// 20 ����

	bool FrameIsWall();
	bool FrameIsBody();

	void Move();


	void SetGenotype(int generation, Snake parents[]);					// 20 ����
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
	Genotype& GetGenotype();

	void PrintSnake(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->snake[i]);
		}
	}



	// ������� !!!!

	int DistanceToWall(char direction);
	int DistanceToTail(char direction);
	int DistanceToApple(char direction, Apple& apple);
};

Genotype* GetBestParents(Snake generation[]);