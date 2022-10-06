#include"Genotyp.h"

Genotyp::Genotyp(int generation)
{
	if (generation == 0)
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if(rand() % 2 == 0)
				firstLayer[i][j] = -1.f / (float)rand();				// Ограничивать???
				
				else
					firstLayer[i][j] = 1.f / (float)rand();
			}
		}
	}
}

Row Genotyp::GetStepPosobility(Row& inputs)
{
	Row secondLayer;
	Row answer;

	secondLayer = this->firstLayer * inputs;
	answer = this->secondLayer * secondLayer;

	return answer;
}
