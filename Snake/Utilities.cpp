#include "Utilities.h"

struct Coordinates
{
	int x;
	int y;
};

bool FrameISApple(Apple& apple, Snake& snake)
{
	const int headIndex = snake.GetSnake().size() - 1;

	sf::Vector2f nextPosition = snake.GetNextPosition();
	sf::Vector2f currentPosition = snake.GetSnake()[headIndex].getPosition();

	return (nextPosition == apple.GetApple().getPosition() || currentPosition == apple.GetApple().getPosition());
}

void SetPositionApple(Apple& apple, Snake& snake)
{
	srand(time(0));

	int position[20] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19 };

	std::vector<Coordinates> notFreePositions;

	int xTemp;
	int yTemp;

	int AppleX = -1;
	int AppleY = -1;

	bool flag = 1;

	while (AppleX == -1 || AppleY == -1)
	{
		AppleX = position[rand() % 20];
		AppleY = position[rand() % 20];

		for (int j = 0; j < notFreePositions.size(); j++)
		{
			if (AppleX == notFreePositions[j].x && AppleY == notFreePositions[j].y)
			{
				flag = 0;
				AppleX = -1;
				AppleY = -1;
			}
		}

		if (flag)
		{
			for (int i = 0; i < snake.GetSnake().size(); i++)
			{
				if (AppleX == snake.GetSnake()[i].getPosition().x)
				{
					if (AppleY == snake.GetSnake()[i].getPosition().y)
					{
						notFreePositions.push_back({ AppleX, AppleY });

						AppleX = -1;
						AppleY = -1;

						break;
					}
				}
			}
		}

		flag = 1;
	}

	apple.GetApple().setPosition(sf::Vector2f(AppleX * FrameLength, AppleY * FrameLength));
}

bool EatApple(Apple& apple, Snake& snake)
{
	if (FrameISApple(apple, snake))
	{
		snake.IncrementScore();
		snake.AddElementToBody(apple.GetApple().getPosition());
		SetPositionApple(apple, snake);
		return 1;
	}

	return 0;
}