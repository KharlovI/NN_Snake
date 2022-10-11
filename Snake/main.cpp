#include <SFML/Graphics.hpp>
#include "Utilities.h"

//#include"Matrix.h"
//#include <iostream>

constexpr bool flag = 0;

int main()
{
	srand(time(NULL));

	//int delay = 5;
	//int counter = 0;

	/*char impossibleDirection;
	char lastPossibleDirection;*/

	sf::RenderWindow window(sf::VideoMode(WindowSize, WindowSize), "Snake With AI");
	window.setFramerateLimit(240);

	const int countOfSnakes = 100;

	Snake snake[countOfSnakes];
	Apple apple[countOfSnakes];

	for (int i = 0; i < countOfSnakes; i++)
		snake[i].SetApple(apple[i]);

	//   lastPossibleDirection = snake.GetDirection();
	   //impossibleDirection = snake.ImposibleDirection();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				if (snake.GetDirection() != 'R')
				{
					if (impossibleDirection != 'L')
						lastPossibleDirection = 'L';
				}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
				if (snake.GetDirection() != 'D')
				{
					if (impossibleDirection != 'U')
						lastPossibleDirection = 'U';
				}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				if (snake.GetDirection() != 'L')
				{
					if (impossibleDirection != 'R')
						lastPossibleDirection = 'R';
				}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				if (snake.GetDirection() != 'U')
				{
					if (impossibleDirection != 'D')
						lastPossibleDirection = 'D';
				}*/
		}

		window.clear();

		if (flag)
		{
			int position = 0;
			int maxCountOfApple = snake[0].GetCountOfApple();

			for (int i = 1; i < countOfSnakes; i++)
			{
				if (snake[i].GetCountOfApple() > maxCountOfApple && snake[i].GetAliveStatus() == 1)
					position = i;
			}

			snake[position].PrintSnake(window);
			apple[position].PrintApple(window);
		}
		else
		{
			for (int i = 0; i < countOfSnakes; i++)
			{
				if (snake[i].GetAliveStatus())
				{
					snake[i].PrintSnake(window);
					apple[i].PrintApple(window);
				}
			}
		}
			/*snake.SetDirection(lastPossibleDirection);
			impossibleDirection = snake.ImposibleDirection();
			impossibleDirection = snake.GetDirection();*/

			for (int i = 0; i < countOfSnakes; i++)
			{
				if (snake[i].GetAliveStatus())
				{
					snake[i].PrintSnake(window);
					apple[i].PrintApple(window);

					snake[i].MoveAI(apple[i]);
					snake[i].SetIsAliveStatus();
					snake[i].IncrementSteps();
				}
			}

		if (AllSnakesIsDead(snake, countOfSnakes))
		{
			int generation = snake[0].GetGeneration();

			std::cout << "Generation: " << generation << std::endl;

			for (int i = 0; i < countOfSnakes; i++)
			{
				snake[i].CalculateTotalScore();
			}
			Snake babies[countOfSnakes];
			Apple newApples[countOfSnakes];

			Genotype* best = GetBestParents(snake, countOfSnakes);
			std::cout << std::endl;
			for (int i = 0; i < countOfSnakes; i++)
			{
				Snake snake2{ best , generation };
				babies[i] = snake2;
			}

			for (int i = 0; i < countOfSnakes; i++)
				babies[i].SetApple(apple[i]);

			for (int i = 0; i < countOfSnakes; i++)
			{
				snake[i] = babies[i];
			}
		}
		/*snake.SetIsAliveStatus();
		if (snake.GetAliveStatus() != 1)
		{
			Snake snake2{};
			Apple apple2{};

			snake = snake2;
			apple = apple2;
			SetPositionApple(apple, snake);
		}*/

		window.display();
	}

	return 0;
}