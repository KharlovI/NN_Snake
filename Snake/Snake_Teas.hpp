#include "doctest.h"
#include "Snake.h"


TEST_CASE("Distance to wall")
{
    Snake snake;
    sf::Vector2f position = snake.GetHeadPosition();

    float UpDistance = snake.DistanceToWall('U');
    float RightDistance = snake.DistanceToWall('R');
    float DownDistance = snake.DistanceToWall('D');
    float LeftDistance = snake.DistanceToWall('L');
    
    CHECK(UpDistance == position.y / FrameLength)
    CHECK(RightDistance == (FieldSIze - position.x) / FrameLength)
    CHECK(DownDistance == (FieldSIze - position.y) / FrameLength)
    CHECK(LeftDistance == position.x / FrameLength)
}

TEST_CASE("Distance to tail")
{
    Snake snake;
    sf::Vector2f headPosition = snake.GetHeadPosition();

    float UpDistance = snake.DistanceToTail('U');
    float RightDistance = snake.DistanceToTail('R');
    float DownDistance = snake.DistanceToTail('D');
    float LeftDistance = snake.DistanceToTail('L');
    
    CHECK(UpDistance == snakePosition.y / FrameLength)
    CHECK(RightDistance == (FieldSIze - headPosition.x) / FrameLength)
    CHECK(DownDistance == (FieldSIze - headPosition.y) / FrameLength)
    CHECK(LeftDistance == headPosition.x / FrameLength)
}

TEST_CASE()