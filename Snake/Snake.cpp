#include"Snake.h"
#include<cmath>

Snake::Snake()
{
    this->color = sf::Color(20+rand()%236, 20+rand()%236, 20+rand()%236, this->opacity);
	sf::RectangleShape head;
	head.setFillColor(this->color);
	head.setSize(sf::Vector2f(FrameLength, FrameLength));

	Genotype temp{};

	int randValue = rand() % 4;

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

	this->snake.push_back(head);
	this->steps = 0;
	this->generation = 0;
	this->countOfApple = 0;
	this->totalScore = 0;
	this->isAlive = 1;
	this->genotype = temp;

	SetStartPositionSnake();
}
Snake::Snake(Genotype* old, int generation)
{
	this->color = sf::Color(20+rand()%236, 20+rand()%236, 20+rand()%236, this->opacity);
	sf::RectangleShape head;
	head.setFillColor(this->color);
	head.setSize(sf::Vector2f(FrameLength, FrameLength));

	Genotype temp(old);

	int randValue = rand() % 4;
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
	this->steps = 0;
	this->snake.push_back(head);
	this->genotype = temp;
	this->generation = generation + 1;
	this->totalScore = 0;
	this->countOfApple = 0;
	this->isAlive = 1;

	SetStartPositionSnake();
}

sf::Vector2f Snake::GetHeadPosition()
{
	return this->snake[this->snake.size()-1].getPosition();
}

void Snake::SetHeadPosition(sf::Vector2f position)
{
	this->snake[0].setPosition(position);
}

int Snake::DistanceToWall(char direction2)
{
	int answer = 0;

	int headPosition = this->snake.size() - 1;

	switch (this->direction)
	{
	case 'L':
		switch (direction2)
		{
		case 'L':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().y) - FrameLength) / FrameLength;
		case 'U':
			return answer = (this->snake[headPosition].getPosition().x) / FrameLength;
		case 'R':
			return answer = (this->snake[headPosition].getPosition().y) / FrameLength;
		}
	case 'U':
		switch (direction2)
		{
		case 'L':
			return answer = (this->snake[headPosition].getPosition().x) / FrameLength;
		case 'U':
			return answer = (this->snake[headPosition].getPosition().y) / FrameLength;
		case 'R':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().x) - FrameLength) / FrameLength;
		}
	case 'R':
		switch (direction2)
		{
		case 'L':
			return answer = (this->snake[headPosition].getPosition().y) / FrameLength;
		case 'U':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().x) - FrameLength) / FrameLength;
		case 'R':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().y) - FrameLength) / FrameLength;
		}
	case 'D':
		switch (direction2)
		{
		case 'L':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().x) - FrameLength) / FrameLength;
		case 'U':
			return answer = (FieldSIze - (this->snake[headPosition].getPosition().y) - FrameLength) / FrameLength;
		case 'R':
			return answer = (this->snake[headPosition].getPosition().x) / FrameLength;
		}
	}

	return answer;
}
int Snake::DistanceToTail(char direction2)
{
	int headIndex = this->snake.size() - 1;

	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	sf::Vector2f tailPosition;

	int answer;

	switch (this->direction)
	{
	case 'L':
	switch (direction2)
	{
		case 'L':
		answer = (FieldSIze - FrameLength) / FrameLength;
		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();

			if (snakePosition.x == tailPosition.x && snakePosition.y < tailPosition.y)
			{
				int temp = (tailPosition.y - snakePosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}		
		return answer;

		case 'U':
		answer = snakePosition.x / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.y == tailPosition.y && snakePosition.x > tailPosition.x)
			{
				int temp = (snakePosition.x - tailPosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}

		return answer;
		case 'R':
		answer = snakePosition.y / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.x == tailPosition.x && snakePosition.y > tailPosition.y)
			{
				int temp = (snakePosition.y - tailPosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}

		return answer;
	}
	case 'U':
	switch (direction2)
	{
		case 'L':
		answer = snakePosition.x / FrameLength;
		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();

			if (snakePosition.y == tailPosition.y && tailPosition.x < snakePosition.x)
			{
				int temp = (snakePosition.x - tailPosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}		
		return answer;

		case 'U':
		answer = snakePosition.y / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.x == tailPosition.x && snakePosition.y > tailPosition.y)
			{
				int temp = (snakePosition.y - tailPosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}

		return answer;
		case 'R':
		answer = (FieldSIze - FrameLength)/ FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.y == tailPosition.y && snakePosition.x < tailPosition.x)
			{
				int temp = (tailPosition.x - snakePosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}
	}
		return answer;
	case 'R':
	switch (direction2)
	{
		case 'L':
		answer = snakePosition.y / FrameLength;
		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();

			if (snakePosition.x == tailPosition.x && tailPosition.y < snakePosition.y)
			{
				int temp = (snakePosition.y - tailPosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}		
		return answer;

		case 'U':
		answer = (FieldSIze - FrameLength) / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.y == tailPosition.y && snakePosition.x < tailPosition.x)
			{
				int temp = (tailPosition.x - snakePosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}

		return answer;
		case 'R':
		answer = (FieldSIze - FrameLength)/ FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.x == tailPosition.x && snakePosition.y < tailPosition.y)
			{
				int temp = (tailPosition.y - snakePosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}
	}
		return answer;
	case 'D':
	switch (direction2)
	{
		case 'L':
		answer = (FieldSIze - FrameLength) / FrameLength;
		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();

			if (snakePosition.y == tailPosition.y && tailPosition.x > snakePosition.x)
			{
				int temp = (tailPosition.x - snakePosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}		
		return answer;

		case 'U':
		answer = (FieldSIze - FrameLength) / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.x == tailPosition.x && snakePosition.y < tailPosition.y)
			{
				int temp = (tailPosition.y - snakePosition.y) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}

		return answer;
		case 'R':
		answer = snakePosition.x / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();
			if (snakePosition.y == tailPosition.y && snakePosition.x > tailPosition.x)
			{
				int temp = (snakePosition.x - tailPosition.x) / FrameLength;
				if (temp < answer)
					answer = temp;
			}
		}
	}
		return answer;
	default:
		break;
	}
	
}
int Snake::DistanceToApple(char direction, Apple& apple)
{
	int headPosition = this->snake.size() - 1;
	int answer;

	sf::Vector2f snakePosition = this->snake[headPosition].getPosition();
	sf::Vector2f applePosition = apple.GetApple().getPosition();

	switch(this->direction)
	{
	case 'L':
		switch (direction)
		{
		case 'L':
		answer = (FieldSIze - FrameLength)  / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (snakePosition.y < applePosition.y)
			{
				answer = (applePosition.y - snakePosition.y) / FrameLength;
			}
		}
		return answer;

		case 'U':
		answer = snakePosition.x / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (snakePosition.x > applePosition.x)
			{
				answer = snakePosition.x - applePosition.x;
			}
		}
		return answer;

		case 'R':
		answer = snakePosition.y / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (applePosition.y < snakePosition.y)
			{
				answer = snakePosition.y - applePosition.y;
			}
		}
		return answer;
		}
	case 'U':
		switch (direction)
		{
		case 'L':
		answer = snakePosition.x  / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (snakePosition.x > applePosition.x)
			{
				answer = (snakePosition.x - applePosition.x ) / FrameLength;
			}
		}
		return answer;

		case 'U':
		answer = snakePosition.y / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (snakePosition.y > applePosition.y)
			{
				answer = snakePosition.y - applePosition.y;
			}
		}
		return answer;

		case 'R':
		answer = (FieldSIze - FrameLength) / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (applePosition.x > snakePosition.x)
			{
				answer = applePosition.x - snakePosition.x;
			}
		}
		return answer;
		}
	case 'R':
		switch (direction)
		{
		case 'L':
		answer = snakePosition.y / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (snakePosition.y > applePosition.y)
			{
				answer = (snakePosition.y - applePosition.y) / FrameLength;
			}
		}
		return answer;

		case 'U':
		answer = (FieldSIze - FrameLength) / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (snakePosition.x < applePosition.x)
			{
				answer = applePosition.x - snakePosition.x;
			}
		}
		return answer;

		case 'R':
		answer = (FieldSIze - FrameLength) / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (applePosition.y > snakePosition.y)
			{
				answer = applePosition.y - snakePosition.y;
			}
		}
		return answer;
		}
	case 'D':
		switch (direction)
		{
		case 'L':
		answer = (FieldSIze - FrameLength)  / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (snakePosition.x < applePosition.x)
			{
				answer = (applePosition.x - snakePosition.x) / FrameLength;
			}
		}
		return answer;

		case 'U':
		answer = (FieldSIze - FrameLength) / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (snakePosition.y < applePosition.y)
			{
				answer = applePosition.y - snakePosition.y;
			}
		}
		return answer;

		case 'R':
		answer = snakePosition.x / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (applePosition.x < snakePosition.x)
			{
				answer = snakePosition.x - applePosition.x;
			}
		}
		return answer;
		}
	}
}
int Snake::DiagonalDistanceToApple(char direction1, Apple& apple)
{
	int headIndex = this->snake.size() - 1;

	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	sf::Vector2f applePosition = apple.GetApple().getPosition();

	int snakeNormX = snakePosition.x / FrameLength;
	int snakeNormY = snakePosition.y / FrameLength;

	int appleNormX = applePosition.x / FrameLength;
	int appleNormY = applePosition.y / FrameLength;

	int dx;
	int dy;

	int answer;
	int alternativeAnsver = ( 2 * (FieldSIze-FrameLength) / FrameLength);
	switch (this->direction)
	{
	case 'L':
		switch (direction1)
		{
		case 'L':
			dx = snakeNormX - appleNormX;
			dy = appleNormY - snakeNormY;

			if(dx == dy)
			{
				return dx + dy;
			}

			return alternativeAnsver;
		case 'R':
			dx = snakeNormX - appleNormX;
			dy = snakeNormY - appleNormY;

			if(dx == dy)
			{
				return dx + dy;
			}

			return alternativeAnsver;
		}
	case 'U':
		switch (direction1)
		{
		case 'L':
			dx = snakeNormX - appleNormX;
			dy = snakeNormY - appleNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;
		case 'R':
			dx = appleNormX - snakeNormX;
			dy = snakeNormY - appleNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;		
		}
	case 'R':
		switch (direction1)
		{
		case 'L':
			dx = appleNormX - snakeNormX;
			dy = snakeNormY - appleNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;
		case 'R':
			dx = appleNormX - snakeNormX;
			dy = appleNormY - snakeNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;		
		}
	case 'D':
		switch (direction1)
		{
		case 'L':
			dx = appleNormX - snakeNormX;
			dy = appleNormY - snakeNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;
		case 'R':
			dx = snakeNormX - appleNormX;
			dy = appleNormY - snakeNormY;

			if(dx == dy)
			{
				return dx + dy;
			}
			return alternativeAnsver;
		}
	}
}

void Snake::AddElementToBody(sf::Vector2f newPosition)
{
	sf::RectangleShape newPart;
	newPart.setSize(sf::Vector2f(FrameLength, FrameLength));
	newPart.setFillColor(this->color);
	newPart.setPosition(newPosition);

	this->snake.push_back(newPart);
}
bool Snake::EatApple(Apple& apple)
{
	if (FrameISApple(apple))
	{
		IncrementScore();
		RemoveSteps();
		AddElementToBody(apple.GetApple().getPosition());
		SetApple(apple);

		return 1;
	}
	return 0;
}

int* Snake::Inputs(Apple& apple)
{
	int* answer = new int[CountOfInputs];
	answer[0] = DistanceToTail('L');
	answer[1] = DistanceToTail('U');
	answer[2] = DistanceToTail('R');

	answer[3] = DistanceToWall('L');
	answer[4] = DistanceToWall('U');
	answer[5] = DistanceToWall('R');

	answer[6] = DistanceToApple('L', apple);
	answer[7] = DiagonalDistanceToApple('L', apple);
	answer[8] = DistanceToApple('U', apple);
	answer[9] = DiagonalDistanceToApple('R', apple);
	answer[10] = DistanceToApple('R', apple);

	answer[11] = 1;

	return answer;
}

bool Snake::MoveAI(Apple& apple)
{
	int* inputs = Inputs(apple);
	int headIndex = this->snake.size() - 1;

	Row steps = this->genotype.GetStepPossibility(inputs);

	sf::Vector2f nextPosition;
	for (int i = 0, j = 1; i < headIndex; i++, j++)
	{
		nextPosition = this->snake[j].getPosition();
		this->snake[i].setPosition(nextPosition);
	}

	if (this->direction == 'L')
	{
		if (steps[0] == 1)
			this->direction = 'D';
		else if (steps[1] == 1)
			this->direction = 'L';
		else if (steps[2] == 1)
			this->direction = 'U';
	}

	else if (this->direction == 'U')
	{
		if (steps[0] == 1)
			this->direction = 'L';
		else if (steps[1] == 1)
			this->direction = 'U';
		else if (steps[2] == 1)
			this->direction = 'R';
	}

	else if (this->direction == 'R')
	{
		if (steps[0] == 1)
			this->direction = 'U';
		else if (steps[1] == 1)
			this->direction = 'R';
		else if (steps[2] == 1)
			this->direction = 'D';
	}

	else
	{
		if (steps[0] == 1)
			this->direction = 'R';
		else if (steps[1] == 1)
			this->direction = 'D';
		else if (steps[2] == 1)
			this->direction = 'L';
	}

	if (EatApple(apple))
	{        
		delete inputs;
		return 1;
	}
	nextPosition = NextPosition();
	this->snake[headIndex].setPosition(nextPosition);
    
	delete inputs;
	return 0;
}


bool Snake::FrameIsWall()
{
	int headIndex = this->snake.size() - 1;
	sf::Vector2f headPosition = this->snake[headIndex].getPosition();

	if (headPosition.x < 0 || headPosition.y < 0)
		return 1;
	if (headPosition.x >= FieldSIze || headPosition.y >= FieldSIze)
		return 1;

	return 0;
}
bool Snake::FrameIsBody()
{
	int headIndex = this->snake.size() - 1;

	sf::Vector2f headPosition = this->snake[headIndex].getPosition();
	sf::Vector2f temp;

	for (int i = 0; i < headIndex; i++)								
	{
		temp = this->snake[i].getPosition();

		if (headPosition == temp)
			return 1;
	}

	return 0;
}
void Snake::SetIsAliveStatus(bool status)
{
	this->isAlive = status;
}

Genotype* GetBestParents(Snake* generation, int count, int& currentValue2)
{
	float maxValue1 = 0;
	float maxValue2 = 0;

	int position1 = -1;
	int position2 = -1;

	float currentValue;

	for (int i = 0; i < count; i++)
	{
		currentValue = generation[i].GetTotalScore();

		if (currentValue >= maxValue2 || currentValue >= maxValue1)
		{

			if (maxValue1 <= maxValue2)
			{
				maxValue1 = currentValue;
				position1 = i;
			}

			else
			{
				maxValue2 = currentValue;
				position2 = i;
			}
		}
	}

	Genotype* answer = new Genotype[2];

	if (maxValue1 == 0 && maxValue2 == 0)
	{
		Genotype randSnake1{};
		Genotype randSnake2{};
		answer[0] = randSnake1;
		answer[1] = randSnake2;

		return answer;
	}

	answer[0] = generation[position1].GetGenotype();
	answer[1] = generation[position2].GetGenotype();

	std::cout << generation[position1].GetCountOfApple() << " " << generation[position2].GetCountOfApple() << std::endl;

	if (maxValue2 > currentValue2 || maxValue1 > currentValue2)
	{
		currentValue2 = maxValue2;

		std::ofstream file1;
		std::ofstream file2;

		file1.open("firstLayer.txt");
		file2.open("secondLayer.txt");

		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < CountOfInputs; j++)
			{
				file1 << answer[1].GetFirstLayer()[i][j];
				file1 << std::endl;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				file2 << answer[1].GetSecondLayer()[i][j];
				file2 << std::endl;
			}
		}

		file1.close();
		file2.close();
	}
	return answer;
}

Snake::Snake(bool flag)
{
	this->color = sf::Color(20 + rand() % 236, 20 + rand() % 236, 20 + rand() % 236, this->opacity);

	sf::RectangleShape head;							// Set random weights
	head.setFillColor(this->color);
	head.setSize(sf::Vector2f(FrameLength, FrameLength));

	Genotype temp{};

	temp.SetFromFile();

	int randValue = rand() % 4;

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

	this->snake.push_back(head);
	this->steps = 0;
	this->generation = 0;
	this->countOfApple = 0;
	this->totalScore = 0;
	this->isAlive = 1;
	this->genotype = temp;

	SetStartPositionSnake();
}

sf::Vector2f Snake::NextPosition()
{
	const int headIndex = this->snake.size() - 1;

	sf::Vector2f temp = this->snake[headIndex].getPosition();

	switch (this->direction)
	{
	case 'L':
	    if(temp.x == 0)
			return temp;
		temp.x -= FrameLength;
		return temp;

	case 'U':
		if(temp.y == 0)
			return temp;
		temp.y -= FrameLength;
		return temp;

	case 'R':
		if(temp.x == FieldSIze - FrameLength)
			return temp;
		temp.x += FrameLength;
		return temp;

	case 'D':
		if(temp.y == FieldSIze - FrameLength)
			return temp;
		temp.y += FrameLength;
		return temp;
	}
}
char Snake::ImpossibleDirection()
{
	switch (this->direction)
	{
	case 'L':
		return 'R';
	case 'U':
		return 'D';
	case 'R':
		return 'L';
	case 'D':
		return 'U';
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
Genotype Snake::GetGenotype()
{
	return this->genotype;
}
int Snake::GetGeneration()
{
	return this->generation;
}
int Snake::GetCountOfApple()
{
	return this->countOfApple;
}
std::vector<sf::RectangleShape>& Snake::GetSnake()
{
	return this->snake;
}
void Snake::SetDirection(char dir)
{
	this->direction = dir;
}
void Snake::SetStartPositionSnake()
{
	int x;
	int y;

	x = (rand() % 7 + 7) * FrameLength;
	y = (rand() % 7 + 7) * FrameLength;

	this->snake[0].setPosition(x, y);
}
void Snake::SetIsAliveStatus()
{
	if (FrameIsWall())
	{
		this->isAlive = 0;
		this->totalScore -= 1.5;
		return;
	}

	if (FrameIsBody())
	{
		this->isAlive = 0;
		this->totalScore -= 1.5;
		return;
	}

	if (this->steps == 500)
	{
		this->isAlive = 0;
		return;
	}
}
void Snake::UpdateSprites(std::vector<sf::Sprite> sprites)
{
	switch (this->direction)
	{
	case 'L':
		this->sprites[this->snake.size() - 1] = sprites[9];
		break;
	case 'U':
		this->sprites[this->snake.size() - 1] = sprites[6];
		break;
	case 'R':
		this->sprites[this->snake.size() - 1] = sprites[8];
		break;
	case 'D':
		this->sprites[this->snake.size() - 1] = sprites[7];
		break;

	}
	for (int i = 1; i < this->snake.size() - 1; i++)
	{
		sf::Vector2f tailDirection = this->snake[i - 1].getPosition();
		sf::Vector2f CurrentPosition = this->snake[i].getPosition();
		sf::Vector2f headDirection = this->snake[i + 1].getPosition();


		if (CurrentPosition.x > tailDirection.x && CurrentPosition.y == tailDirection.y )
		{
			if (CurrentPosition.x < headDirection.x && CurrentPosition.y == headDirection.y)					// ---
			{
				this->sprites[i] = sprites[5];		
				continue;
			}

			if (CurrentPosition.x == headDirection.x && CurrentPosition.y > headDirection.y)
			{
				this->sprites[i] = sprites[13];
				continue;
			}

			if (CurrentPosition.x == headDirection.x && CurrentPosition.y < headDirection.y)
			{
				this->sprites[i] = sprites[12];
				continue;
			}
		}
		if (CurrentPosition.x < tailDirection.x && CurrentPosition.y == tailDirection.y)
		{
			if (CurrentPosition.x > headDirection.x && CurrentPosition.y == headDirection.y)					// ---
			{
				this->sprites[i] = sprites[5];
				continue;
			}

			if (CurrentPosition.x == headDirection.x && CurrentPosition.y > headDirection.y)
			{
				this->sprites[i] = sprites[10];
				continue;
			}

			if (CurrentPosition.x == headDirection.x && CurrentPosition.y < headDirection.y)
			{
				this->sprites[i] = sprites[11];
				continue;
			}
		}

		if (CurrentPosition.x == tailDirection.x && CurrentPosition.y > tailDirection.y)
		{
			if (CurrentPosition.x == headDirection.x && CurrentPosition.y < headDirection.y)					// ---
			{
				this->sprites[i] = sprites[4];
				continue;
			}

			if (CurrentPosition.x > headDirection.x && CurrentPosition.y == headDirection.y)
			{
				this->sprites[i] = sprites[13]; // 12
				continue;
			}

			if (CurrentPosition.x < headDirection.x && CurrentPosition.y == headDirection.y)
			{
				this->sprites[i] = sprites[10];
				continue;
			}
		}
		if (CurrentPosition.x == tailDirection.x && CurrentPosition.y < tailDirection.y)
		{
			if (CurrentPosition.x == headDirection.x && CurrentPosition.y > headDirection.y)					// ---
			{
				this->sprites[i] = sprites[4];
				continue;
			}

			if (CurrentPosition.x > headDirection.x && CurrentPosition.y == headDirection.y)
			{
				this->sprites[i] = sprites[12];
				continue;
			}

			if (CurrentPosition.x < headDirection.x && CurrentPosition.y == headDirection.y)
			{
				this->sprites[i] = sprites[11];
				continue;
			}
		}
	}

	if (this->snake.size() > 1)
	{
		sf::Vector2f tailPosition = this->snake[0].getPosition();
		sf::Vector2f prevPosition = this->snake[1].getPosition();

		if (tailPosition.x == prevPosition.x)
		{
			if (tailPosition.y > prevPosition.y)
			{
				this->sprites[0] = sprites[0];
			}

			else if (tailPosition.y < prevPosition.y)
			{
				this->sprites[0] = sprites[3];
			}
		}

		else
		{
			if (tailPosition.x > prevPosition.x)
			{
				this->sprites[0] = sprites[1];
			}

			else if (tailPosition.x < prevPosition.x)
			{
				this->sprites[0] = sprites[2];
			}
		}
	}

	for (int i = 0; i < this->snake.size(); i++)
	{
		sf::Vector2f position = this->snake[i].getPosition();
		this->sprites[i].setPosition(position);
	}
}
void Snake::AddSprites(std::vector<sf::Sprite> sprites)
{
	this->sprites.push_back(sprites[0]);
}
void Snake::CalculateTotalScore()
{
	this->totalScore += this->countOfApple;
}
void Snake::RemoveSteps()
{
	this->steps -= 75;
}
void Snake::IncrementSteps()
{
	this->steps++;
}
bool Snake::FrameISApple(Apple& apple)
{
	sf::Vector2f nextPosition = NextPosition();
	return (nextPosition == apple.GetApple().getPosition());
}
void Snake::SetApple(Apple& apple)
{
    apple.SetColor(this->color);

	std::vector<sf::Vector2f> notFreePositions;
	int snakeLength = this->snake.size();

	sf::Vector2f temp;
	for (int i = 0; i < snakeLength; i++)
	{
		temp.x = this->snake[i].getPosition().x / FrameLength;
		temp.y = this->snake[i].getPosition().y / FrameLength;

		notFreePositions.push_back(temp);
	}

	int AppleX = -1;
	int AppleY = -1;

	while (AppleX == -1)
	{
		AppleX = rand() % (FieldSIze / FrameLength);
		AppleY = rand() % (FieldSIze / FrameLength);

		for (int i = 0; i < snakeLength; i++)
		{
			if (AppleX == notFreePositions[i].x && AppleY == notFreePositions[i].y)
			{
				AppleX = -1;
				AppleY = -1;

				break;
			}
		}
	}

	apple.GetApple().setPosition(sf::Vector2f(AppleX * FrameLength, AppleY * FrameLength));
	apple.GetAS().setPosition(sf::Vector2f(AppleX * FrameLength, AppleY * FrameLength));
}
