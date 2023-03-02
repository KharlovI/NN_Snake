#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "Snake.h"


TEST_CASE("Distance to wall")
{
    Snake snake;
    sf::Vector2f position{10*FrameLength,0};
    snake.SetHeadPosition(position);
    char direction = 'U';
    snake.SetDirection(direction);

    int LDistance = snake.DistanceToWall('L');
    int RDistance = snake.DistanceToWall('R');
    int UDistance = snake.DistanceToWall('U');
    
    CHECK(UDistance == 0);
    CHECK(RDistance == 9);
    CHECK(LDistance == 10);
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
    
    char direction = 'U';
    snake.SetDirection(direction);

    int UpDistance = snake.DistanceToTail('U');
    int RightDistance = snake.DistanceToTail('R');
    int LeftDistance = snake.DistanceToTail('L');
    
    CHECK(UpDistance == 2);
    CHECK(RightDistance == 2);
    CHECK(LeftDistance == 19);
}

TEST_CASE("Distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 0};
    char direction = 'U';
    Apple apple;
    sf::Vector2f applePosition{0,0};

    snake.SetDirection(direction);
    snake.SetHeadPosition(snakePosition);
    apple.SetPosition(applePosition);

    
    int UDistance = snake.DistanceToApple('U', apple);
    int RDistance = snake.DistanceToApple('R', apple);
    int LDistance = snake.DistanceToApple('L', apple); 

    CHECK(UDistance == 19);
    CHECK(RDistance == 19);
    CHECK(LDistance == 10);
}

TEST_CASE("Diagonal distance to apple")
{
    Snake snake;
    sf::Vector2f snakePosition{10*FrameLength, 10*FrameLength};
    Apple apple;
    sf::Vector2f applePosition{0,0};
    char direction = 'U';
    snake.SetDirection(direction);

    snake.SetHeadPosition(snakePosition);
    apple.SetPosition(applePosition);

    int LDistance = snake.DiagonalDistanceToApple('L', apple);
    int RDistance = snake.DiagonalDistanceToApple('R', apple);


    CHECK(LDistance == 20);
    CHECK(RDistance == 38);   
}

TEST_CASE("Next position")
{
    Snake snake1;
    Snake snake2;

    sf::Vector2f firstSnakePosition{10*FrameLength, 0};
    char firstSnakeDirection = 'U';
    sf::Vector2f secondSnakePosition{0, 10*FrameLength};
    char secondSnakeDirection = 'D';

    snake1.SetHeadPosition(firstSnakePosition);
    snake1.SetDirection(firstSnakeDirection);
    snake2.SetHeadPosition(secondSnakePosition);
    snake2.SetDirection(secondSnakeDirection);
   
    sf::Vector2f nextPosition1 = snake1.NextPosition();
    sf::Vector2f nextPosition2 = snake2.NextPosition();

    CHECK(nextPosition1.x == 10*FrameLength);
    CHECK(nextPosition1.y == 0);
    CHECK(nextPosition2.x == 0  );
    CHECK(nextPosition2.y == 11*FrameLength);
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

    apple.SetPosition(applePosition);

    snake1.SetDirection(snake1Direction);
    snake1.SetHeadPosition(snake1Position);
    snake2.SetDirection(snake2Direction);
    snake2.SetHeadPosition(snake2Position);
    snake3.SetDirection(snake3Direction);
    snake3.SetHeadPosition(snake3Position);
    snake4.SetDirection(snake4Direction);
    snake4.SetHeadPosition(snake4Position);

    CHECK(snake1.FrameISApple(apple) == true);
    CHECK(snake2.FrameISApple(apple) == false);
    CHECK(snake3.FrameISApple(apple) == true);
    CHECK(snake4.FrameISApple(apple) == false);
}

TEST_CASE("Imposible direction")
{
    Snake snake;
    sf::Vector2f position{FrameLength, FrameLength};
    char direction = 'R';
    snake.SetDirection(direction);
    snake.SetHeadPosition(position);

    CHECK(snake.ImpossibleDirection() == 'L' );
}

TEST_CASE("Model")
{
    Genotype genotype;
    genotype.SetFromFile();

   int* inputs = new int[CountOfInputs];
   inputs[0] = 20;
   inputs[1] = 20;
   inputs[2] = 20;
   inputs[3] = 2;
   inputs[4] = 3;
   inputs[5] = 17;
   inputs[6] = 20;
   inputs[7] = 40;
   inputs[8] = 20;
   inputs[9] = 40;
   inputs[10] = 20;

   Row answer = genotype.GetStepPossibility(inputs);
   CHECK(answer[2] == 0);
   CHECK(answer[1] == 1);
   CHECK(answer[0] == 0);
   
   delete inputs;
}