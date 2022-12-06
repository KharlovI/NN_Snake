#include <SFML/Graphics.hpp>
#include "Utilities.h"
#include<iostream>

constexpr int NORM = CHAR_SIZE_Button - 7;
int FPS = 15;

int main()
{
	srand(time(NULL));

	sf::Font font;
	font.loadFromFile("NotCourierSans.otf");

	Button first("Not trained SNAKE", sf::Vector2f{ FieldSIze + 5*NORM, 10*NORM}, font);
	Button second("Train 100 SNAKES", sf::Vector2f{ FieldSIze + 5*NORM, 15 * NORM }, font);
	Button third("Trained SNAKE", sf::Vector2f{ FieldSIze + 5*NORM, 20 * NORM }, font);
	Button SpeedUP("Speed up", sf::Vector2f{ FieldSIze + 5 * NORM, FieldSIze - 15 * NORM }, font);
	Button SpeedDown("Slaw down", sf::Vector2f{ FieldSIze + 5 * NORM, FieldSIze - 10 * NORM }, font);

	sf::RenderWindow window(sf::VideoMode(WindowSize, FieldSIze), "Snake With AI", sf::Style::Close);
	window.setFramerateLimit(FPS);
	const int countOfSnakes = 100;

	int maxValue = 60;

	std::vector<Button> b;
	b.push_back(first);
	b.push_back(second);
	b.push_back(third);

	b.push_back(SpeedUP);
	b.push_back(SpeedDown);

	sf::Texture appleTexture;
	appleTexture.loadFromFile("Apple_Texture.png");
	sf::Sprite appleSprite;
	appleSprite.setTexture(appleTexture);

	sf::Texture SnakeTexture;
	SnakeTexture.loadFromFile("Snake_Texture.png");
	std::vector<sf::Sprite> SP;
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			sf::Sprite temp;
			temp.setTexture(SnakeTexture);
			temp.setTextureRect({i*40,j*40,40,40});
			SP.push_back(temp);
		}
	}

	int numOfFunction = FirstAction(b, window, FPS, appleSprite, SP);

	while (window.isOpen())
	{
		switch (numOfFunction)
		{
		case 0:
			return 1;
		case 1:
			numOfFunction = FirstAction(b, window, FPS, appleSprite, SP);
			continue;
		case 2:
			numOfFunction = SecondAction(b, window, FPS, appleSprite, SP);
			continue;
		case 3:
			numOfFunction = ThirdAction(b, window, FPS, appleSprite, SP);
			continue;
		}
	}

	return 0;
}