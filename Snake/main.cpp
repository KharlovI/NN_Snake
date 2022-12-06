#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include<iostream>

constexpr int NORM = CHAR_SIZE_Button - 7;
int FPS = 15;

int main()
{
	sf::Font font;
	font.loadFromFile("NotCourierSans.otf");

	Button first("Not trained SNAKE", sf::Vector2f{ FieldSIze + 5*NORM, 10*NORM}, font);
	Button second("Train 100 SNAKES", sf::Vector2f{ FieldSIze + 5*NORM, 15 * NORM }, font);
	Button third("Trained SNAKE", sf::Vector2f{ FieldSIze + 5*NORM, 20 * NORM }, font);

	Button SpeedUP("Speed up", sf::Vector2f{ FieldSIze + 5 * NORM, FieldSIze - 15 * NORM }, font);
	Button SpeedDown("Slow down", sf::Vector2f{ FieldSIze + 5 * NORM, FieldSIze - 10 * NORM }, font);
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(WindowSize, FieldSIze), "Snake With AI");
	window.setFramerateLimit(FPS);
	const int countOfSnakes = 100;

	int maxValue = 60;
	Snake snake;
	Apple apple;

	/*Snake snake[countOfSnakes];
	for (int i = 0; i < countOfSnakes; i++)
	{
		Snake temp{ 1 };
		snake[i] = temp;
	}
	Apple apple[countOfSnakes];

	for (int i = 0; i < countOfSnakes; i++)
		snake[i].SetApple(apple[i]);*/
	snake.SetApple(apple);

	std::vector<Button> b;
	b.push_back(first);
	b.push_back(second);
	b.push_back(third);

	b.push_back(SpeedUP);
	b.push_back(SpeedDown);

	int numOfFunction = FirstAction(b, window, FPS);

	while (window.isOpen())
	{
		switch (numOfFunction)
		{
		case 0:
			return 1;
		case 1:
			numOfFunction = FirstAction(b, window, FPS);
			continue;
		case 2:
			numOfFunction = SecondAction(b, window, FPS);
			continue;
		case 3:
			numOfFunction = ThirdAction(b, window, FPS);
			continue;
		}
		/*sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				sf::Vector2i mp = sf::Mouse::getPosition(window);

				first.SetIsPressed(mp);
				second.SetIsPressed(mp);
				third.SetIsPressed(mp);

				SpeedUP.SetIsPressed(mp);
				SpeedDown.SetIsPressed(mp);

				if (first.IsPressed())
				{
					FirstAction(b, window, FPS);
					
				}

				else if (second.IsPressed())
				{
					SecondAction(b, window, FPS);
				}

				else if (third.IsPressed())
				{
					ThirdAction(b, window, FPS);
				}

				else if (SpeedUP.IsPressed())
				{
					if (FPS < 150)
					{
						FPS += 5; 
						window.setFramerateLimit(FPS);
					}
				}
				else if (SpeedDown.IsPressed())
				{
					if (FPS > 14)
					{
						FPS -= 5;
						window.setFramerateLimit(FPS);
					}
				}
				
			}
		}

		window.clear();
		first.Draw(window);
		second.Draw(window);
		third.Draw(window);
		SpeedUP.Draw(window);
		SpeedDown.Draw(window);

		window.display();*/
	}

	return 0;
}