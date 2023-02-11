#pragma once
#include"SFML/Graphics.hpp"
#include <vector>
#include"Genotype.h"
#include "Apple.h"
#include <ctime>
constexpr int FrameLength = 40;
constexpr int FieldSIze = 800;


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

	int DistanceToWall(char direction);
	int DistanceToTail(char direction);	
	int DistanceToApple(char direction, Apple& apple);
	int DiagonalDistanceToApple(char direction1, char direction2, Apple& apple);	

	void AddElementToBody(sf::Vector2f newPosition);
	bool EatApple(Apple& apple);

	int* Inputs(Apple& apple);	
	bool MoveAI(Apple& apple);

	bool FrameIsWall();
	bool FrameIsBody();
	bool FrameISApple(Apple& apple);


	void UpdateSprites(std::vector<sf::Sprite> sprites);
	void AddSprites(std::vector<sf::Sprite> sprites);
	
	sf::Vector2f NextPosition();	

	void SetDirection(char dir);
	void SetStartPositionSnake();
	void SetIsAliveStatus();
	void SetIsAliveStatus(bool status);
	void IncrementScore() { this->countOfApple++; }


	std::vector <sf::RectangleShape>& GetSnake();


	bool GetAliveStatus();
	char GetDirection();
	float GetTotalScore();
	Genotype GetGenotype();
	int GetGeneration();
	int GetCountOfApple();
	int GetLength() { return this->snake.size(); }

	sf::Vector2f GetHeadPosition();
	void SetHeadPosition(sf::Vector2f position);

	void PrintSnake(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->snake.size(); i++)
		{
			window.draw(this->snake[i]);
		}
	}
	void PrintSnakeSprites(sf::RenderWindow& window)
	{
		for (int i = 0; i < this->sprites.size(); i++)
		{
			window.draw(this->sprites[i]);
		}
	}

	char ImpossibleDirection();														
	void CalculateTotalScore();

	void RemoveSteps();
	void IncrementSteps();

	void SetApple(Apple& apple);
};

Genotype* GetBestParents(Snake* generation, int count, int& value);