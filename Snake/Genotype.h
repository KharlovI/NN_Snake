#pragma once
#include"Matrix.h"
constexpr double delta = 0.005;
constexpr int CountOfInputs = 14;

class Genotype
{
private:
	Matrix firstLayer{ CountOfInputs, 7};					// count of column, rows
	Matrix secondLayer{ 8, 3 };

public:
	Genotype();
	Genotype(Genotype* bestParents);
	Row GetStepPossibility(int inputs[]);

	Matrix GetFirstLayer() { return this->firstLayer; }
	Matrix GetSecondLayer() { return this->secondLayer; }
	void SetFromFile();

	/*void SetLayer(Matrix temp);*/
	void operator =(Genotype g2)
	{
		for (int i = 0; i < 7; i++)
		{
			for (int j = 0; j < CountOfInputs; j++)
			{
				this->firstLayer[i][j] = g2.firstLayer[i][j];
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				this->secondLayer[i][j] = g2.secondLayer[i][j];
			}
		}
	}


};