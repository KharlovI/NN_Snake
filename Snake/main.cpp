#include <SFML/Graphics.hpp>
#include "Utilits.h"
#include <iostream>

int main()
{
	int deley = 100;
	int counter = 0;
	char imposibleDirection;
	char lustPosibleDirection;

	sf::RenderWindow window(sf::VideoMode(800, 800), "Lesson 1. kychka-pc.ru");

	Snake snake{};
	Apple apple{};

	SetPositionApple(apple, snake);

	lustPosibleDirection = snake.GetDirection();

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
				if (imposibleDirection != 'L')
					lustPosibleDirection = 'L';
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			if (snake.GetDirection() != 'D')
			{
				if (imposibleDirection != 'U')
					lustPosibleDirection = 'U';
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			if (snake.GetDirection() != 'L')
			{
				if (imposibleDirection != 'R')
					lustPosibleDirection = 'R';
			}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			if (snake.GetDirection() != 'U')
			{
				if (imposibleDirection != 'D')
					lustPosibleDirection = 'D';
			}

		window.clear();

		snake.PrintSnake(window);
		apple.PrintAple(window);

		if (counter == deley)
		{
			snake.SetDirection(lustPosibleDirection);
			imposibleDirection = snake.GetDirection();

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