#include"Snake.h"
#include <ctime>
Snake::Snake()
{
	srand(time(0));
	const int randValue = rand() % 4;					// Случайное стартовое направление движения 
	switch (randValue)
	{
	case 0:
		this->direction = 'L';
		break;

	case 1:
		this->direction = 'U';
		break;

	case 2:
		this->direction = 'R';
		break;

	case 3:
		this->direction = 'D';
		break;

	}

	sf::RectangleShape head;
	head.setFillColor(sf::Color::Green);
	head.setSize(sf::Vector2f(40, 40));

	this->snake.push_back(head);
	SetStartPositionSnake();							// Присваиваем голове рандомную позицию

	this->score = 0;
	this->isAlive = 1;

}

bool Snake::FrameIsWall()
{
	const int snakeLenth = this->snake.size();
	sf::Vector2f headPosition = this->snake[snakeLenth - 1].getPosition();


	if (headPosition.x < 0 || headPosition.y < 0)
		return 1;
	if (headPosition.x >= 800 || headPosition.y >= 800)
		return 1;

	return 0;
}

bool Snake::FrameIsBody()
{
	const int snakeLenth = this->snake.size();
	if (snakeLenth < 4)
		return 0;

	sf::Vector2f headPosition = this->snake[snakeLenth - 1].getPosition();

	sf::Vector2f temp;
	for (int i = 0; i < snakeLenth - 1; i++)								// не учитываем голову 
	{
		temp = this->snake[i].getPosition();

		if (headPosition == temp)
			return 1;
	}

	return 0;
}

void Snake::Move()
{
	const int snakeLenth = this->snake.size();

	sf::Vector2f nextPosition;
	for (int i = 0; i < snakeLenth - 1; i++)
	{
		nextPosition = this->snake[i + 1].getPosition();
		this->snake[i].setPosition(nextPosition);
	}

	sf::Vector2f head = GetNextPosition();
	this->snake[snakeLenth - 1].setPosition(head);
}

void Snake::SetDirection(char dir)							// dir будем получать в мейне 
{
	this->direction = dir;
}
void Snake::SetStartPositionSnake()
{
	srand(time(0));

	int x;
	int y;

	x = (rand() % 7 + 7) * FrameLenth;
	y = (rand() % 7 + 7) * FrameLenth;

	this->snake[0].setPosition(x, y);
}

std::vector<sf::RectangleShape>& Snake::GetSnake()
{
	return this->snake;
}

sf::Vector2f& Snake::GetNextPosition()
{
	const int headIndex = this->snake.size() - 1;

	sf::Vector2f temp = this->snake[headIndex].getPosition();

	switch (this->direction)
	{
	case 'L':
		temp.x -= 40;
		return temp;

	case 'U':
		temp.y -= 40;
		return temp;

	case 'R':
		temp.x += 40;
		return temp;

	case 'D':
		temp.y += 40;
		return temp;
	}
}

bool Snake::GetAliveStatus()
{
	return this->isAlive;
}

void Snake::SetIsAliveStatus()
{
	if (FrameIsWall())
	{
		this->isAlive = 0;
		return;
	}

	if (FrameIsBody())
	{
		this->isAlive = 0;
		return;
	}
}

void Snake::IncrementScore()
{
	this->score++;
}

void Snake::AddElementToBody(sf::Vector2f newPosition)
{
	sf::RectangleShape newPart;
	newPart.setSize(sf::Vector2f(40, 40));
	newPart.setFillColor(sf::Color::Green);
	newPart.setPosition(newPosition);

	this->snake.push_back(newPart);
}

char Snake::GetDirection()
{
	return this->direction;
}