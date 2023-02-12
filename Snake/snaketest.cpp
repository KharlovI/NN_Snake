#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Snake.h"


TEST_CASE("Distance to wall")
{
    Snake snake;
    sf::Vector2f position{10*FrameLength,0};
    snake.SetHeadPosition(position);

    int UpDistance = snake.DistanceToWall('U');
    int RightDistance = snake.DistanceToWall('R');
    int DownDistance = snake.DistanceToWall('D');
    int LeftDistance = snake.DistanceToWall('L');
    
    CHECK(UpDistance == 0);
    CHECK(RightDistance == 10);
    CHECK(DownDistance == 20);
    CHECK(LeftDistance == 10);
}

TEST_CASE("Distance to tail")
{
    Snake snake;
    sf::Vector2f headPosition{10*FrameLength,10*FrameLength};
    snake.AddElementToBody(sf::Vector2f{11*FrameLength,10*FrameLength});
    snake.AddElementToBody(sf::Vector2f{12*FrameLength,10*FrameLength});
    snake.AddElementToBody(sf::Vector2f{13*FrameLength,10*FrameLength});
    snake.AddElementToBody(sf::Vector2f{13*FrameLength,11*FrameLength});
    snake.AddElementToBody(sf::Vector2f{13*FrameLength,12*FrameLength});
    snake.AddElementToBody(sf::Vector2f{13*FrameLength,13*FrameLength});
    snake.AddElementToBody(sf::Vector2f{12*FrameLength,13*FrameLength});
    snake.AddElementToBody(sf::Vector2f{11*FrameLength,13*FrameLength});
    snake.AddElementToBody(sf::Vector2f{11*FrameLength,12*FrameLength});

    int UpDistance = snake.DistanceToTail('U');
    int RightDistance = snake.DistanceToTail('R');
    int DownDistance = snake.DistanceToTail('D');
    int LeftDistance = snake.DistanceToTail('L');
    
    CHECK(UpDistance == 2);
    CHECK(RightDistance == 2);
    CHECK(DownDistance == 20);
    CHECK(LeftDistance == 20);
}

TEST_CASE("Distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 0};
    Apple apple;
    sf::Vector2f applePosition{0,0};

    int UpDistance = snake.DistanceToApple('U', apple);
    int RightDistance = snake.DistanceToApple('R', apple);
    int DownDistance = snake.DistanceToApple('D', apple);
    int LeftDistance = snake.DistanceToApple('L',apple); 

    CHECK(UpDistance == 20);
    CHECK(RightDistance == 20);
    CHECK(DownDistance == 20);
    CHECK(LeftDistance == 10);
}

TEST_CASE("Diagonal distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 10*FrameLength};
    Apple apple;
    sf::Vector2f applePosition{0,0};

    int LUDistance = snake.DiagonalDistanceToApple('L','U', apple);
    int URDistance = snake.DiagonalDistanceToApple('U','R', apple);
    int RDDistance = snake.DiagonalDistanceToApple('R','D', apple);
    int DLDistance = snake.DiagonalDistanceToApple('D','L',apple); 

    CHECK(LUDistance == 20);
    CHECK(URDistance == 40);
    CHECK(RDDistance == 40);
    CHECK(DLDistance == 40);
    
}

TEST_CASE("Next position")
{
    Snake snake1;
    Snake snake2;
    Snake snake3;
    Snake snake4;
    sf::Vector2f firstSnakePosition{10*FrameLength, 0};
    char firstSnakeDirection = 'U';
    sf::Vector2f secondSnakePosition{0, 10*FrameLength};
    char secondSnakeDirection = 'D';
    sf::Vector2f thirdSnakePosition{10*FrameLength, 10*FrameLength};
    char thirdSnakeDirection = 'L';
    sf::Vector2f lastSnakePosition{10*FrameLength, 10*FrameLength};
    char lastSnakeDirection = 'R';

    snake1.SetHeadPosition(firstSnakePosition);
    snake1.SetDirection(firstSnakeDirection);
    snake2.SetHeadPosition(secondSnakePosition);
    snake2.SetDirection(secondSnakeDirection);
    snake3.SetHeadPosition(thirdSnakePosition);
    snake3.SetDirection(thirdSnakeDirection);
    snake4.SetHeadPosition(lastSnakePosition);
    snake4.SetDirection(lastSnakeDirection);
   
    snake1.NextPosition();
    snake2.NextPosition();
    snake3.NextPosition();
    snake4.NextPosition();

    CHECK(snake1.GetHeadPosition().x == 10*FrameLength && snake1.GetHeadPosition().y == -FrameLength);
    CHECK(snake2.GetHeadPosition().x == 0 && snake2.GetHeadPosition().y == 11*FrameLength);
    CHECK(snake3.GetHeadPosition().x == 9*FrameLength && snake3.GetHeadPosition().y == 10*FrameLength);
    CHECK(snake4.GetHeadPosition().x == 11*FrameLength && snake4.GetHeadPosition().y == 10*FrameLength);
}

TEST_CASE("Frame is wall")
{
    Snake snake1;
    Snake snake2;
    Snake snake3;
    Snake snake4;

    sf::Vector2f snake1Position{0,0};
    sf::Vector2f snake2Position{FieldSIze,FieldSIze};   // into the wall
    sf::Vector2f snake3Position{FieldSIze - FrameLength, 0};
    sf::Vector2f snake4Position{0, FieldSIze - FrameLength};

    snake1.SetHeadPosition(snake1Position);
    snake2.SetHeadPosition(snake2Position);
    snake3.SetHeadPosition(snake3Position);
    snake4.SetHeadPosition(snake4Position);

    CHECK(snake1.FrameIsWall() == false);
    CHECK(snake2.FrameIsWall() == true);
    CHECK(snake3.FrameIsWall() == false);
    CHECK(snake4.FrameIsWall() == false);
}

TEST_CASE("Frame is apple")
{
    Apple apple;
    Snake snake1;
    Snake snake2;
    Snake snake3;
    Snake snake4;

    sf::Vector2f applePosition{0,0};
    sf::Vector2f snake1Position{0,FrameLength};
    sf::Vector2f snake2Position{FieldSIze,FieldSIze};   // into the wall
    sf::Vector2f snake3Position{FrameLength, 0};
    sf::Vector2f snake4Position{0, 0};

    char snake1Direction = 'U';
    char snake2Direction = 'D';
    char snake3Direction = 'L';
    char snake4Direction = 'D';

    snake1.SetDirection(snake1Direction);
    snake1.SetHeadPosition(snake1Position);
    snake2.SetDirection(snake2Direction);
    snake2.SetHeadPosition(snake2Position);
    snake3.SetDirection(snake3Direction);
    snake3.SetHeadPosition(snake3Position);
    snake4.SetDirection(snake4Direction);
    snake4.SetHeadPosition(snake4Position);

    CHECK(snake1.FrameISApple(apple) == false);
    CHECK(snake1.FrameISApple(apple) == false);
    CHECK(snake1.FrameISApple(apple) == true);
    CHECK(snake4.FrameISApple(apple) == false);
}
