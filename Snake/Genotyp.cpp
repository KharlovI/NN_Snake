#include"Genotyp.h"

Genotyp::Genotyp()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			this->firstLayer[i][j] = NULL;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			this->secondLayer[i][j] = NULL;
		}
	}
}

Genotyp::Genotyp(int generation, Genotyp bestParents[])
{
	// Если первое поколение - заполняем генотип случайными весами

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

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (rand() % 2 == 0)
					secondLayer[i][j] = -1.f / (float)rand();				// Ограничивать???

				else
					secondLayer[i][j] = 1.f / (float)rand();
			}
		}
	}


	// Комбинируем генотип родителей 

	else   
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (rand() % 97 == 0)				//   1/97 - вероятность случайного значения весов (мутации) 
				{
					firstLayer[i][j] = 1.f / (float)(rand() % 100);
				}

				if (rand() % 2 == 0)
					firstLayer[i][j] = bestParents[0].firstLayer[i][j];				

				else
					firstLayer[i][j] = bestParents[1].firstLayer[i][j];
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (rand() % 97 == 0)				//   1/97 - вероятность случайного значения весов 
				{
					firstLayer[i][j] = 1.f / (float)(rand() % 100);
				}

				if (rand() % 2 == 0)
					secondLayer[i][j] = bestParents[0].secondLayer[i][j];				

				else
					secondLayer[i][j] = bestParents[1].secondLayer[i][j];
			}
		}
	}
}

Row Genotyp::GetStepPosobility(Row& inputs)								// інпут - 10 значений, одно из которых - смещение(1)
{
	Row secondLayer{5};													// второй слой - 4 возможных направления +  смещение(1)
	Row answer{3};															// на выходе - вектор из 3 значений(коеффициент для всех ДОСТУПНЫХ направлений)

	secondLayer = this->firstLayer * inputs;
	answer = this->secondLayer * secondLayer;

	return answer;
}