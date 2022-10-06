#pragma once
#include"Matrix.h"

class Genotyp
{
private:
	Matrix firstLayer{5,10};
	Matrix secondLayer{3,5};
	int generation;
public:

	Genotyp(int generation); // if(generation == 0) заполняем матрицы случайными весами 
	Row GetStepPosobility(Row& inputs);
};