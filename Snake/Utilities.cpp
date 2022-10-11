#include "Utilities.h"

//struct Coordinates
//{
//	int x;
//	int y;
//};
//
//bool FrameISApple(Apple& apple, Snake& snake)
//{
//	const int headIndex = snake.GetSnake().size() - 1;
//
//	sf::Vector2f nextPosition = snake.GetNextPosition();
//	sf::Vector2f currentPosition = snake.GetSnake()[headIndex].getPosition();
//
//	return (nextPosition == apple.GetApple().getPosition());
//}
//void SetPositionApple(Apple& apple, Snake& snake)
//{
//	std::vector<Coordinates> notFreePositions;
//	int snakeLength = snake.GetSnake().size();
//
//	Coordinates temp;
//	for (int i = 0; i < snakeLength; i++)
//	{
//		temp.x = snake.GetSnake()[i].getPosition().x / FrameLength;
//		temp.y = snake.GetSnake()[i].getPosition().y / FrameLength;
//
//		notFreePositions.push_back(temp);
//	}
//
//	int AppleX = -1;
//	int AppleY = -1;
//
//	while (AppleX == -1)
//	{
//		AppleX = rand() % 20;
//		AppleY = rand() % 20;
//
//		for (int i = 0; i < snakeLength; i++)
//		{
//			if (AppleX == notFreePositions[i].x && AppleY == notFreePositions[i].y)
//			{
//				AppleX = -1;
//				AppleY = -1;
//
//				break;
//			}
//		}
//	}
//
//	apple.GetApple().setPosition(sf::Vector2f(AppleX * FrameLength, AppleY * FrameLength));
//}
//void EatApple(Apple& apple)
//{
//	if (FrameISApple(apple, snake))
//	{
//		snake.IncrementScore();
//		snake.RemoveSteps();
//
//		snake.AddElementToBody(apple.GetApple().getPosition());
//		SetPositionApple(apple, snake);
//	}
//}

bool AllSnakesIsDead(Snake snakes[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (snakes[i].GetAliveStatus())
			return 0;
	}

	return 1;
}
