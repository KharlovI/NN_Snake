#pragma once
#include"SFML/Graphics.hpp"
#include <vector>
#include"Genotype.h"
#include "Apple.h"
#include <ctime>
constexpr int FrameLength = 40;
constexpr int FieldSIze = 800;
constexpr int WindowSize = 1100;

class Snake
{
private:

	std::vector <sf::RectangleShape> snake;
	std::vector <sf::Sprite> sprites;

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
	Snake(Genotype* old, int generation);
	Snake(bool HER);

	void UpdateSprites(std::vector<sf::Sprite> sprites);
	void AddSprites(std::vector<sf::Sprite> sprites);
	bool FrameIsWall();
	bool FrameIsBody();
	bool FrameISApple(Apple& apple);

	void Move();
	void MoveAI(Apple& apple, std::vector<sf::Sprite>snakeSprites);

	void SetDirection(char dir);
	void SetStartPositionSnake();
	void SetIsAliveStatus();
	void SetIsAliveStatus(bool status);
	void IncrementScore() { this->countOfApple++; }

	void AddElementToBody(sf::Vector2f newPosition);

	std::vector <sf::RectangleShape>& GetSnake();
	sf::Vector2f NextPosition();

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

	void PrintSnakeSprites(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->sprites[i]);
		}
	}

	char ImpossibleDirection();

	int GetLength() { return this->snake.size(); }

	int DistanceToWall(char direction);
	int DistanceToTail(char direction);
	int DistanceToTail(char direction, int& tailIndex);
	int DistanceToApple(char direction, Apple& apple);
	int DiagonalDistanceToApple(char direction1, char direction2, Apple& apple);	// (L+U, L+D, R+U, R+D)
	int DiagonalDistanceToTail(char direction1, char direction2);
	int DiagonalDistanceToWall(char direction1, char direction2);

	int* Inputs(Apple& apple);														// Distance by current direction 

	void CalculateTotalScore();

	void RemoveSteps();
	void IncrementSteps();

	void SetApple(Apple& apple);

	bool EatApple(Apple& apple, std::vector<sf::Sprite> sp);
};

Genotype* GetBestParents(Snake* generation, int count, int& value);