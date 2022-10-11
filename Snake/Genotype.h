#pragma once
#include"Matrix.h"

class Genotype
{
private:
	Matrix firstLayer{ 22, 9 };					// count of column, rows
	Matrix secondLayer{ 10, 3 };					// count of column, rows

public:
	Genotype();
	Genotype(Genotype* bestParents);
	Row GetStepPosobility(int inputs[]);

	void operator =(Genotype g2)
	{
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 22; j++)
			{
				this->firstLayer[i][j] = g2.firstLayer[i][j];
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				this->secondLayer[i][j] = g2.secondLayer[i][j];
			}
		}
	}
};