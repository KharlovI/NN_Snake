#include"Snake.h"
#include<cmath>

struct Coordinates
{
	int x;
	int y;
};

Snake::Snake()
{
	sf::RectangleShape head;							// Set random weights
	Genotype temp{};
	head.setFillColor(sf::Color::Green);
	head.setSize(sf::Vector2f(FrameLength, FrameLength));

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
	this->generation = 0;
	this->countOfApple = 0;
	this->totalScore = 0;
	//this->aliveTime = 0;					// when snake die use aliveTime = (clock() - aliveTime)/ CLOCKS_PER_SEC for seting time
	this->isAlive = 1;
	this->genotype = temp;

	SetStartPositionSnake();
}
Snake::Snake(Snake* old, int count)
{
	sf::RectangleShape head;

	head.setFillColor(sf::Color::Green);
	head.setSize(sf::Vector2f(FrameLength, FrameLength));

	/*Genotype* best = GetBestParents(old, count);*/

	Genotype temp(GetBestParents(old, count));

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
	this->generation = old[0].GetGeneration() + 1;
	this->totalScore = 0;
	this->countOfApple = 0;
	this->isAlive = 1;

	SetStartPositionSnake();
}

bool Snake::FrameIsWall()
{
	int headIndex = this->snake.size() - 1;
	sf::Vector2f headPosition = this->snake[headIndex].getPosition();

	if (headPosition.x < 0 || headPosition.y < 0)
		return 1;
	if (headPosition.x >= 800 || headPosition.y >= 800)
		return 1;

	return 0;
}
bool Snake::FrameIsBody()
{
	int headIndex = this->snake.size() - 1;
	//if (snakeLength < 4)
	//	return 0;

	sf::Vector2f headPosition = this->snake[headIndex].getPosition();

	sf::Vector2f temp;
	for (int i = 0; i < headIndex; i++)								// �� ��������� ������
	{
		temp = this->snake[i].getPosition();

		if (headPosition == temp)
			return 1;
	}

	return 0;
}

void Snake::Move()
{
	int length = this->snake.size();

	sf::Vector2f nextPosition;
	for (int i = 0; i < length - 1; i++)
	{
		nextPosition = this->snake[i + 1].getPosition();
		this->snake[i].setPosition(nextPosition);
	}

	sf::Vector2f head = GetNextPosition();
	this->snake[length - 1].setPosition(head);
}


void Snake::MoveAI(Apple& apple)
{
	int* inputs = Inputs(apple);
	Row steps = this->genotype.GetStepPosobility(inputs);				// contain chance of every (posible) steps(L, Str, R)
	int headIndex = this->snake.size() - 1;

	sf::Vector2f nextPosition;
	for (int i = 0; i < headIndex; i++)
	{
		nextPosition = this->snake[i + 1].getPosition();
		this->snake[i].setPosition(nextPosition);
	}

	if (this->direction == 'L')
	{
		if (steps[0] == 1)
		{
			this->direction = 'D';
		}
		else if (steps[1] == 1)
		{
			this->direction = 'L';
		}
		else if (steps[2] == 1)
		{
			this->direction = 'U';
		}

		if (EatApple(apple))
		{
			delete inputs;
			return;
		}

		sf::Vector2f head = GetNextPosition();
		this->snake[headIndex].setPosition(head);
	}
	else if (this->direction == 'U')
	{
		if (steps[0] == 1)
		{
			this->direction = 'L';
		}
		else if (steps[1] == 1)
		{
			this->direction = 'U';
		}
		else if (steps[2] == 1)
		{
			this->direction = 'R';
		}
		if (EatApple(apple))
		{
			delete inputs;
			return;
		}
		sf::Vector2f head = GetNextPosition();
		this->snake[headIndex].setPosition(head);
	}
	else if (this->direction == 'R')
	{
		if (steps[0] == 1)
		{
			this->direction = 'U';
		}
		else if (steps[1] == 1)
		{
			this->direction = 'R';
		}
		else if (steps[2] == 1)
		{
			this->direction = 'D';
		}
		if (EatApple(apple))
		{
			delete inputs;
			return;
		}
		sf::Vector2f head = GetNextPosition();
		this->snake[headIndex].setPosition(head);
	}
	else
	{
		if (steps[0] == 1)
		{
			this->direction = 'R';
		}
		else if (steps[1] == 1)
		{
			this->direction = 'D';
		}
		else if (steps[2] == 1)
		{
			this->direction = 'L';
		}
		if (EatApple(apple))
		{
			delete inputs;
			return;
		}
		sf::Vector2f head = GetNextPosition();
		this->snake[headIndex].setPosition(head);
	}
	delete inputs;
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
		std::cout << "T" << std::endl;
		return;
	}

	if (this->steps == 500)
	{
		this->isAlive = 0;
		return;
	}
	/*if (this->aliveTime > (10 + this->countOfApple * 5))
	{
		this->isAlive = 0;
	}*/
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
sf::Vector2f Snake::GetNextPosition()
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

void Snake::AddElementToBody(sf::Vector2f newPosition)
{
	sf::RectangleShape newPart;
	newPart.setSize(sf::Vector2f(FrameLength, FrameLength));
	newPart.setFillColor(sf::Color::Green);
	newPart.setPosition(newPosition);

	this->snake.push_back(newPart);
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
char Snake::ImposibleDirection()
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


// Check!!!!!!!!
int Snake::DistanceToWall(char direction)
{
	int answer;

	int headPosition = this->snake.size() - 1;

	switch (direction)
	{
	case 'L':
		answer = (this->snake[headPosition].getPosition().x) / FrameLength;
		break;
	case 'U':
		answer = (this->snake[headPosition].getPosition().y) / FrameLength;
		break;
	case 'R':
		answer = (WindowSize - (this->snake[headPosition].getPosition().x)) / FrameLength;
		break;
	case 'D':
		answer = (WindowSize - (this->snake[headPosition].getPosition().y)) / FrameLength;
		break;
	}

	return answer;
}
int Snake::DistanceToTail(char direction)
{
	int headIndex = this->snake.size() - 1;

	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	sf::Vector2f tailPosition;

	int answer;

	switch (direction)
	{
	case 'L':

		answer = snakePosition.x / FrameLength;
		for (int i = 0; i < headIndex; i++)
		{
			tailPosition = this->snake[i].getPosition();

			if (snakePosition.y == tailPosition.y)
			{
				if ((snakePosition.x - tailPosition.x) / FrameLength < answer && snakePosition.x - tailPosition.x > 0)
					answer = (snakePosition.x - tailPosition.x) / FrameLength;
			}
		}
		
		return answer;

	case 'U':
		answer = snakePosition.y / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			if (snakePosition.x == tailPosition.x)
			{
				if ((snakePosition.y - tailPosition.y) / FrameLength < answer && snakePosition.y - tailPosition.y > 0)
					answer = (snakePosition.y - tailPosition.y) / FrameLength;
			}
		}
		return answer;

	case 'R':
		answer = (WindowSize - snakePosition.x) / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			if (snakePosition.y == tailPosition.y)
			{
				if ((tailPosition.x - snakePosition.x) / FrameLength < answer && tailPosition.x - snakePosition.x > 0)
					answer = (tailPosition.x - snakePosition.x) / FrameLength;
			}
		}

		return answer;

	case 'D':
		answer = (WindowSize - snakePosition.y) / FrameLength;

		for (int i = 0; i < headIndex; i++)
		{
			if (snakePosition.x == tailPosition.x)
			{
				if ((tailPosition.y - snakePosition.y) / FrameLength < answer && tailPosition.y - snakePosition.y > 0)
					answer = (tailPosition.y - snakePosition.y) / FrameLength;
			}
		}

		return answer;
	}
}
int Snake::DistanceToApple(char direction, Apple& apple)
{
	int headPosition = this->snake.size() - 1;
	int answer;

	sf::Vector2f snakePosition = this->snake[headPosition].getPosition();
	sf::Vector2f applePosition = apple.GetApple().getPosition();

	switch (direction)
	{
	case 'L':
		answer = snakePosition.x / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (snakePosition.x - applePosition.x > 0)
			{
				answer = (snakePosition.x - applePosition.x) / FrameLength;
			}
		}
		return answer;

	case 'U':
		answer = snakePosition.y / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (snakePosition.y - applePosition.y > 0)
			{
				answer = snakePosition.y - applePosition.y;
			}
		}
		return answer;

	case 'R':
		answer =(WindowSize - snakePosition.x) / FrameLength;

		if (applePosition.y == snakePosition.y)
		{
			if (applePosition.x - snakePosition.x > 0)
			{
				answer = applePosition.x - snakePosition.x;
			}
		}
		return answer;

	case 'D':

		answer = (WindowSize - snakePosition.y) / FrameLength;

		if (applePosition.x == snakePosition.x)
		{
			if (applePosition.y - snakePosition.y > 0)
			{
				answer = applePosition.y - snakePosition.y;
			}
		}
		return answer;
	}
}
int Snake::DiagonalDistanceToApple(char direction1, char direction2, Apple& apple)
{
	int headIndex = this->snake.size() - 1;

	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	sf::Vector2f applePosition = apple.GetApple().getPosition();

	int answer;
	switch (direction1)
	{
	case 'L':
		switch (direction2)
		{
		case 'U':
			answer = (snakePosition.x + snakePosition.y) / (2 * FrameLength);

			if (snakePosition.x - applePosition.x == snakePosition.y - applePosition.y)
			{
				int dx = (snakePosition.x - applePosition.x) / FrameLength;
				int dy = (snakePosition.y - applePosition.y) / FrameLength;

				answer = (dx + dy) / 2;
			}
			return answer;


		case 'D':
			answer = (snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);

			if (snakePosition.x - applePosition.x == applePosition.y - snakePosition.y)
			{
				int dx = (snakePosition.x - applePosition.x) / FrameLength;
				int dy = (applePosition.y - snakePosition.y) / FrameLength;

				answer = (dx + dy) / 2;
			}
			return answer;
		}
		break;
	case 'R':
		switch (direction2)
		{
		case 'U':
			answer = (WindowSize - snakePosition.x + snakePosition.y) / (2 * FrameLength);

			if (applePosition.x - snakePosition.x == snakePosition.y - applePosition.y)
			{
				int dx = (applePosition.x - snakePosition.x) / FrameLength;
				int dy = (snakePosition.y - applePosition.y) / FrameLength;

				answer = (dx + dy) / 2;
			}
			return answer;
		case 'D':
			answer = (WindowSize - snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);

			if (applePosition.x - snakePosition.x == applePosition.y - snakePosition.y)
			{
				int dx = (applePosition.x - snakePosition.x) / FrameLength;
				int dy = (applePosition.y - snakePosition.y) / FrameLength;

				answer = (dx + dy) / 2;
			}
			return answer;
		}
	}
}
int Snake::DiagonalDistanceToTail(char direction1, char direction2)
{
	int headIndex = this->snake.size() - 1;
	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	sf::Vector2f tailPosition;

	int answer;

	switch (direction1)
	{
	case 'L':
		switch (direction2)
		{
		case 'U':
			answer = (snakePosition.x + snakePosition.y) / (2 * FrameLength);

			for (int i = 0; i < headIndex; i++)
			{
				tailPosition = this->snake[i].getPosition();

				if (snakePosition.x - tailPosition.x == snakePosition.y - tailPosition.y)
				{
					int dx = (snakePosition.x - tailPosition.x) / FrameLength;
					int dy = (snakePosition.y - tailPosition.y) / FrameLength;
					if (answer > (dx + dy) / 2)
						answer = (dx + dy) / 2;
				}
			}
			return answer;

		case 'D':
			answer = (snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);

			for (int i = 0; i < headIndex; i++)
			{
				tailPosition = this->snake[i].getPosition();

				if (snakePosition.x - tailPosition.x == tailPosition.y - snakePosition.y)
				{
					int dx = (snakePosition.x - tailPosition.x) / FrameLength;
					int dy = (tailPosition.y - snakePosition.y) / FrameLength;
					if (answer > (dx + dy) / 2)
						answer = (dx + dy) / 2;
				}
			}
			return answer;
		}

	case 'R':
		switch (direction2)
		{
		case 'U':

			answer = (WindowSize - snakePosition.x + snakePosition.y) / (2 * FrameLength);

			for (int i = 0; i < headIndex; i++)
			{
				tailPosition = this->snake[i].getPosition();

				if (tailPosition.x - snakePosition.x == snakePosition.y - tailPosition.y)
				{
					int dx = (tailPosition.x - snakePosition.x) / FrameLength;
					int dy = (snakePosition.y - tailPosition.y) / FrameLength;
					if (answer > (dx + dy) / 2)
						answer = (dx + dy) / 2;
				}
			}
			return answer;

		case 'D':
			answer = (WindowSize - snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);

			for (int i = 0; i < headIndex; i++)
			{
				tailPosition = this->snake[i].getPosition();

				if (tailPosition.x - snakePosition.x == tailPosition.y - snakePosition.y)
				{
					int dx = (tailPosition.x - snakePosition.x) / FrameLength;
					int dy = (tailPosition.y - snakePosition.y) / FrameLength;
					if (answer > (dx + dy) / 2)
						answer = (dx + dy) / 2;
				}
			}
			return answer;
		}
	}
}
int Snake::DiagonalDistanceToWall(char direction1, char direction2)
{
	int headIndex = this->snake.size() - 1;
	sf::Vector2f snakePosition = this->snake[headIndex].getPosition();
	int answer;

	switch (direction1)
	{
	case 'L':
		switch (direction2)
		{
		case'U':

			answer = (snakePosition.x + snakePosition.y) / (2 * FrameLength);
			return answer;

		case'D':

			answer = (snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);
			return answer;

		}

	case 'R':
		switch (direction2)
		{

		case'U':

			answer = (WindowSize - snakePosition.x + snakePosition.y) / (2 * FrameLength);
			return answer;

		case'D':

			answer = (WindowSize - snakePosition.x + WindowSize - snakePosition.y) / (2 * FrameLength);
			return answer;

		}
	}
}
//

int* Snake::Inputs(Apple& apple)
{
	int* answer = new int[22];

	switch (this->direction)
	{
	case'L':
		answer[0] = DistanceToWall('D');
		answer[1] = DistanceToTail('D');
		answer[2] = DistanceToApple('D', apple);
		answer[3] = DistanceToWall('L');
		answer[4] = DistanceToTail('L');
		answer[5] = DistanceToApple('L', apple);
		answer[6] = DistanceToWall('U');
		answer[7] = DistanceToTail('U');
		answer[8] = DistanceToApple('U', apple);
		break;

	case'U':
		answer[0] = DistanceToWall('L');
		answer[1] = DistanceToTail('L');
		answer[2] = DistanceToApple('L', apple);
		answer[3] = DistanceToWall('U');
		answer[4] = DistanceToTail('U');
		answer[5] = DistanceToApple('U', apple);
		answer[6] = DistanceToWall('R');
		answer[7] = DistanceToTail('R');
		answer[8] = DistanceToApple('R', apple);
		break;

	case 'R':
		answer[0] = DistanceToWall('U');
		answer[1] = DistanceToTail('U');
		answer[2] = DistanceToApple('U', apple);
		answer[3] = DistanceToWall('R');
		answer[4] = DistanceToTail('R');
		answer[5] = DistanceToApple('R', apple);
		answer[6] = DistanceToWall('D');
		answer[7] = DistanceToTail('D');
		answer[8] = DistanceToApple('D', apple);
		break;
	case 'D':
		answer[0] = DistanceToWall('R');
		answer[1] = DistanceToTail('R');
		answer[2] = DistanceToApple('R', apple);
		answer[3] = DistanceToWall('D');
		answer[4] = DistanceToTail('D');
		answer[5] = DistanceToApple('D', apple);
		answer[6] = DistanceToWall('L');
		answer[7] = DistanceToTail('L');
		answer[8] = DistanceToApple('L', apple);
		break;
	}

	answer[9] = DiagonalDistanceToApple('L', 'U', apple);
	answer[10] = DiagonalDistanceToApple('L', 'D', apple);
	answer[11] = DiagonalDistanceToApple('R', 'U', apple);;
	answer[12] = DiagonalDistanceToApple('R', 'D', apple);;
	answer[13] = DiagonalDistanceToTail('L', 'U');
	answer[14] = DiagonalDistanceToTail('L', 'D');
	answer[15] = DiagonalDistanceToTail('R', 'U');
	answer[16] = DiagonalDistanceToTail('R', 'D');
	answer[17] = DiagonalDistanceToWall('L', 'U');
	answer[18] = DiagonalDistanceToWall('L', 'D');
	answer[19] = DiagonalDistanceToWall('R', 'U');
	answer[20] = DiagonalDistanceToWall('R', 'D');
	answer[21] = 1;

	return answer;
}

void Snake::CalculateTotalScore()
{
	this->totalScore += this->countOfApple;
}

void Snake::RemoveSteps()
{
	this->steps -= 50;
}

void Snake::IncrementSteps()
{
	this->steps++;
}

bool Snake::FrameISApple(Apple& apple)
{
	int headIndex = this->snake.size() - 1;
	sf::Vector2f nextPosition = GetNextPosition();
	return (nextPosition == apple.GetApple().getPosition());
}

void Snake::SetPositionApple(Apple& apple)
{
	std::vector<Coordinates> notFreePositions;
	int snakeLength = this->snake.size();

	Coordinates temp;
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
		AppleX = rand() % 20;
		AppleY = rand() % 20;

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
}

bool Snake::EatApple(Apple& apple)
{
	if (FrameISApple(apple))
	{
		IncrementScore();
		RemoveSteps();

		AddElementToBody(apple.GetApple().getPosition());
		SetPositionApple(apple);
		return 1;
	}
	return 0;
}

Genotype* GetBestParents(Snake* generation, int count)
{
	float maxValue1 = generation[0].GetTotalScore();
	float maxValue2 = generation[1].GetTotalScore();

	int position1 = 0;
	int position2 = 1;

	float currentValue;

	for (int i = 2; i < count; i++)
	{
		currentValue = generation[i].GetTotalScore();

		if (currentValue > maxValue2 || currentValue > maxValue1)
		{

			if (currentValue > maxValue2)
			{
				maxValue2 = currentValue;
				position2 = i;
			}
			else if (currentValue > maxValue1)
			{
				maxValue1 = currentValue;
				position1 = i;
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

	std::cout << generation[position1].GetCountOfApple()<< " " << generation[position2].GetCountOfApple() << std::endl;
	return answer;
}