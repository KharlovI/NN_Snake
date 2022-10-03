#pragma once
#include <SFML/Graphics.hpp>

class List
{
private:
	struct Node
	{
		int posX;							// Ќачало координат в левом верхнем углу ??????
		int posY;							// 

		Node* next;
		Node(int x, int y);

	};

	Node* head;
	Node* tail;

public:
	
	List();
	void AddNode(int x, int y);
};


class Snake
{
private:
	List body;
	int  score;
	char direction;
public:
	Snake(List& list);
	void Rotation();						// Set diration
	void Move();							// Set coordinats 

	bool IsWall();							// (Map& map)
											// coordinats (0,0) ...... (x,0)
											//			  (0,1)        (x,1)
											//			    .            .
											//			  (0,y)....... (x,y)
											// -> return (this->x == 0 || this->x == w || this->y == 0 || this->y == h)




	bool IsApple();							//     (Apple& apple)       
											// ->  check direction  
											// ->  if(Dir == L) : return((this->x - 1) == apple.x && (this->y      == apple.y))
											// ->  if(Dir == R) : return((this->x + 1) == apple.x && (this->y      == apple.y))
											// ->  if(Dir == U) : return( this->x	   == apple.x &&((this->y - 1) == apple.y))																
											// ->  if(Dir == D) : return((this->x + 1) == apple.x && (this->y + 1) == apple.y))

	bool IsTail();							//  перебор всех элементов списка начина€ с головы - 3 ?? 
											// (змейка с длинной < 4 не может врезатьс€ в себ€) ??
	
	
	
	
	void SetStartPosition();				// rand x, rand y :  0 < x < w ; 0 < y < h
};