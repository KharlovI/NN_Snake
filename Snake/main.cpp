#include <SFML/Graphics.hpp>
#include "Utilities.h"

//#include"Matrix.h"
//#include <iostream>

int main()
{
	srand(time(NULL));

	int delay = 100;
	int counter = 0;
	char impossibleDirection;
	char lastPossibleDirection;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Snake With AI");

	Snake snake{};
	Apple apple{};

	SetPositionApple(apple, snake);

    lastPossibleDirection = snake.GetDirection();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
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
			}

		window.clear();

		snake.PrintSnake(window);
		apple.PrintApple(window);

		if (counter == delay)
		{
			snake.SetDirection(lastPossibleDirection);
            impossibleDirection = snake.GetDirection();

			if (EatApple(apple, snake))
			{
				counter = 0;
				continue;
			}
			snake.Move();

			counter = 0;

		}
		snake.SetIsAliveStatus();
		if (snake.GetAliveStatus() != 1)
			window.close();

		counter++;

		window.display();
	}

	return 0;
}