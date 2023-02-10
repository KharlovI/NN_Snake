#include "doctest.h"
#include "Snake.h"


TEST_CASE("Distance to wall")
{
    Snake snake;
    sf::Vector2f position = snake.GetHeadPosition();

    int UpDistance = snake.DistanceToWall('U');
    int RightDistance = snake.DistanceToWall('R');
    int DownDistance = snake.DistanceToWall('D');
    int LeftDistance = snake.DistanceToWall('L');
    
    CHECK(UpDistance == position.y / FrameLength);
    CHECK(RightDistance == (FieldSIze - position.x) / FrameLength);
    CHECK(DownDistance == (FieldSIze - position.y) / FrameLength);
    CHECK(LeftDistance == position.x / FrameLength);
}

TEST_CASE("Distance to tail")
{
    Snake snake;
    sf::Vector2f headPosition = snake.GetHeadPosition();

    int UpDistance = snake.DistanceToTail('U');
    int RightDistance = snake.DistanceToTail('R');
    int DownDistance = snake.DistanceToTail('D');
    int LeftDistance = snake.DistanceToTail('L');
    
    CHECK(UpDistance == snakePosition.y / FrameLength);
    CHECK(RightDistance == (FieldSIze - headPosition.x) / FrameLength);
    CHECK(DownDistance == (FieldSIze - headPosition.y) / FrameLength);
    CHECK(LeftDistance == headPosition.x / FrameLength);
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

    CHECK(UpDistance == snakePosition.y);
    CHECK(RightDistance == (FieldSIze - snakePosition.x) / FrameLength);
    CHECK(DownDistance == (FieldSIze - snakePosition.y) / FrameLength);
    CHECK(LeftDistance == (snakePosition.x - applePosition.x) / FrameLength);
}

TEST_CASE("Diagol distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 0};
    Apple apple;
    sf::Vector2f applePosition{0,0};

    int UpDistance = snake.DiagonalDistanceToApple('U', apple);
    int RightDistance = snake.DiagonalDistanceToApple('R', apple);
    int DownDistance = snake.DiagonalDistanceToApple('D', apple);
    int LeftDistance = snake.DiagonalDistanceToApple('L',apple); 

    int xSquare = pow(snakePosition.x / FieldSIze,2);
    int ySquare = pow(snakePosition.y / FieldSIze,2);
    int sum = pow(xSquare + ySquare,0.5);

    CHECK(UpDistance == sum);
    CHECK(RightDistance == sum);
    CHECK(DownDistance == sum);
    CHECK(LeftDistance == sum);
}