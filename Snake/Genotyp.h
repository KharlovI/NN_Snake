#pragma once
#include"Matrix.h"

class Genotyp
{
private:
	Matrix firstLayer{10,5};				// первый слой весов 
	Matrix secondLayer{5,3};				// второй слой весов 
public:
	Genotyp();
	Genotyp(int generation, Genotyp bestParents[]); // if(generation == 0) заполняем матрицы случайными весами 
	Row GetStepPosobility(Row& inputs);
};