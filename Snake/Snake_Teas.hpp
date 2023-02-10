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
    
    CHECK(UpDistance == headPosition.y / FrameLength);
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

    CHECK(UpDistance == snakePosition.y / FrameLength);
    CHECK(RightDistance == (FieldSIze - snakePosition.x) / FrameLength);
    CHECK(DownDistance == (FieldSIze - snakePosition.y) / FrameLength);
    CHECK(LeftDistance == (snakePosition.x - applePosition.x) / FrameLength);
}

TEST_CASE("Diagonal distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 0};
    Apple apple;
    sf::Vector2f applePosition{0,0};

    int LUDistance = snake.DiagonalDistanceToApple('L','U', apple);
    int URDistance = snake.DiagonalDistanceToApple('U','R', apple);
    int RDDistance = snake.DiagonalDistanceToApple('R','D', apple);
    int DLDistance = snake.DiagonalDistanceToApple('D','L',apple); 

    int xSquare = pow(snakePosition.x / FieldSIze,2);
    int ySquare = pow(snakePosition.y / FieldSIze,2);
    int sum = pow(xSquare + ySquare,0.5);

    CHECK(LUDistance == sum);
    CHECK(URDistance == sum);
    CHECK(RDDistance == sum);
    CHECK(DLDistance == sum);
    
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
    char secondSnakeDirection = 'U';
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
   
    CHECK(snake1.NextPosition() == snake1.GetHeadPosition());
    CHECK(snake2.NextPosition() == sf::Vector2f{snake2.GetHeadPosition().x,snake2.GetHeadPosition().y - FrameLength});
    CHECK(snake3.NextPosition() == sf::Vector2f{snake3.GetHeadPosition().x,snake3.GetHeadPosition().y});
    CHECK(snake4.NextPosition() == sf::Vector2f{snake4.GetHeadPosition().x,snake4.GetHeadPosition().y - FrameLength});
}