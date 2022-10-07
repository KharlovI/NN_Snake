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

	this->countOfApple = 0;
	this->isAlive = 1;

	//SetGenotyp(generation, parents);
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

void Snake::SetGenotyp(int generation, Snake parents[])
{
	Genotyp temp{ generation + 1, GetBestParrents(parents) };
	this->genotyp = temp;
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

char Snake::GetDirection()
{
	return this->direction;
}
float Snake::GetTotalScore()
{
	return this->totalScore;
}
bool Snake::GetAliveStatus()
{
	return this->isAlive;
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

void Snake::IncrementScore()
{
	this->countOfApple++;
}

void Snake::AddElementToBody(sf::Vector2f newPosition)
{
	sf::RectangleShape newPart;
	newPart.setSize(sf::Vector2f(40, 40));
	newPart.setFillColor(sf::Color::Green);
	newPart.setPosition(newPosition);

	this->snake.push_back(newPart);
}

// Протестить
Genotyp& Snake::GetGenotyp()
{
	return this->genotyp;
}

// Протестить
int Snake::DistanceToWall(char direction)
{
	int answer = 0;

	const int headPosition = this->snake.size() - 1;

	switch (direction)
	{
	case 'L':
		answer = (this->snake[headPosition].getPosition().x) / FrameLenth;
		break;
	case 'U':
		answer = (this->snake[headPosition].getPosition().y) / FrameLenth;
		break;
	case 'R':
		answer = (800 - (this->snake[headPosition].getPosition().x)) / FrameLenth;
		break;
	case 'D':
		answer = (800 - (this->snake[headPosition].getPosition().y)) / FrameLenth;
		break;
	}

	return answer;
}


// Протестить
int Snake::DistanceToTail(char direction)
{
	const int headPosition = this->snake.size() - 1;

	int xHead = this->snake[headPosition].getPosition().x;
	int yHead = this->snake[headPosition].getPosition().y;

	int answerX = xHead / FrameLenth;
	int answerY = yHead / FrameLenth;

	switch (direction)
	{
	case 'L':
		for (int i = 0; i < headPosition; i++)
		{
			if (this->snake[i].getPosition().y == yHead)
			{
				if ((xHead - this->snake[i].getPosition().x) / FrameLenth < answerX && xHead - this->snake[i].getPosition().x > 0)
				{
					answerX = (xHead - this->snake[headPosition].getPosition().x) / FrameLenth;
				}
			}
		}
		if (answerX == xHead)
			return 0;
		return answerX;
	case 'U':
		for (int i = 0; i < headPosition; i++)
		{
			if (this->snake[i].getPosition().x == xHead)
			{
				if ((yHead - this->snake[i].getPosition().y) / FrameLenth < answerY && xHead - this->snake[i].getPosition().y > 0)
				{
					answerY = (yHead - this->snake[headPosition].getPosition().y) / FrameLenth;
				}
			}
		}
		if (answerY == yHead)
			return 0;
		return answerY;
	case 'R':

		for (int i = 0; i < headPosition; i++)
		{
			if (this->snake[i].getPosition().y == yHead)
			{
				if ((this->snake[i].getPosition().x - xHead) / FrameLenth < answerX && this->snake[i].getPosition().x - xHead > 0)
				{
					answerX = (this->snake[headPosition].getPosition().x - xHead) / FrameLenth;
				}
			}
		}
		if (answerX == xHead)
			return 0;
		return answerX;

	case 'D':
		for (int i = 0; i < headPosition; i++)
		{
			if (this->snake[i].getPosition().x == xHead)
			{
				if ((yHead - this->snake[i].getPosition().y) / FrameLenth < answerY && xHead - this->snake[i].getPosition().y > 0)
				{
					answerY = (yHead - this->snake[headPosition].getPosition().y) / FrameLenth;
				}
			}
		}
		if (answerY == yHead)
			return 0;
		return answerY;
	}
}

// Протестить
int Snake::DistanceToApple(char direction, Apple& apple)
{
	int answer = 0;
	const int headPosition = this->snake.size() - 1;

	switch (direction)
	{
	case 'L':
		if (apple.GetApple().getPosition().y == this->snake[headPosition].getPosition().y)
		{
			if (this->snake[headPosition].getPosition().x - apple.GetApple().getPosition().x > 0)
			{
				answer = this->snake[headPosition].getPosition().x - apple.GetApple().getPosition().x;
			}
		}
		return answer;

	case 'U':
		if (apple.GetApple().getPosition().x == this->snake[headPosition].getPosition().x)
		{
			if (this->snake[headPosition].getPosition().y - apple.GetApple().getPosition().y > 0)
			{
				answer = this->snake[headPosition].getPosition().y - apple.GetApple().getPosition().y;
			}
		}
		return answer;

	case 'R':
		if (apple.GetApple().getPosition().y == this->snake[headPosition].getPosition().y)
		{
			if (apple.GetApple().getPosition().x - this->snake[headPosition].getPosition().x > 0)
			{
				answer = apple.GetApple().getPosition().x - this->snake[headPosition].getPosition().x;
			}
		}
		return answer;

	case 'D':
		if (apple.GetApple().getPosition().x == this->snake[headPosition].getPosition().x)
		{
			if (apple.GetApple().getPosition().y - this->snake[headPosition].getPosition().y > 0)
			{
				answer = apple.GetApple().getPosition().y - this->snake[headPosition].getPosition().y;
			}
		}
		return answer;
	}
}

Genotyp* GetBestParrents(Snake generation[])
{
	float maxValue1 = generation[0].GetTotalScore();
	float maxValue2 = 0;

	int position1 = 0;
	int position2 = 0;

	float currentValue;

	for (int i = 1; i < 100; i++)
	{
		currentValue = generation[i].GetTotalScore();

		if (currentValue > maxValue1)
		{
			maxValue2 = maxValue1;
			position2 = position1;

			maxValue1 = currentValue;
			position1 = i;
		}
	}

	Genotyp temp[2] = { generation[position1].GetGenotyp(), generation[position2].GetGenotyp()};

	return temp;
}