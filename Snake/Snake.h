#pragma once
#include"SFML/Graphics.hpp"
#include <vector>
#include"Genotype.h"
#include "Apple.h"
#include <ctime>
constexpr int FrameLength = 40;
constexpr int WindowSize = 800;

class Snake
{
private:

	std::vector <sf::RectangleShape> snake;
    sf::Color color;

    static const int opacity = 128;

	Genotype genotype;
	int generation;

	int countOfApple;
	int steps;

	float totalScore;

	bool isAlive;
	char direction;

public:

	Snake();
	Snake(Snake* old, int count);

	bool FrameIsWall();
	bool FrameIsBody();
	bool FrameISApple(Apple& apple);

	void Move();
	void MoveAI(Apple& apple);

	void SetDirection(char dir);
	void SetStartPositionSnake();
	void SetIsAliveStatus();
	//void SetAliveTime();
	void IncrementScore() { this->countOfApple++; }

	void AddElementToBody(sf::Vector2f newPosition);

	std::vector <sf::RectangleShape>& GetSnake();
	sf::Vector2f GetNextPosition();

	bool GetAliveStatus();
	char GetDirection();
	float GetTotalScore();
	Genotype GetGenotype();
	int GetGeneration();
	int GetCountOfApple();

	void PrintSnake(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->snake[i]);
		}
	}

	char ImposibleDirection();



	int DistanceToWall(char direction);
	int DistanceToTail(char direction);
	int DistanceToApple(char direction, Apple& apple);
	int DiagonalDistanceToApple(char direction1, char direction2, Apple& apple);	// (L+U, L+D, R+U, R+D)
	int DiagonalDistanceToTail(char direction1, char direction2);
	int DiagonalDistanceToWall(char direction1, char direction2);

	int* Inputs(Apple& apple);														// Distance by current direction 

	void CalculateTotalScore();

	void RemoveSteps();
	void IncrementSteps();

	void SetApple(Apple& apple);

	bool EatApple(Apple& apple);
};

Genotype* GetBestParents(Snake* generation, int count);