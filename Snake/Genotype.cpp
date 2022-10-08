#include"Genotype.h"

Genotype::Genotype()
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

Genotype::Genotype(int generation, Genotype bestParents[])
{
	// ���� ������ ��������� - ��������� ������� ���������� ������

	if (generation == 0)
	{

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if(rand() % 2 == 0)
				firstLayer[i][j] = -1.f / (float)rand();				// ������������???
				
				else
					firstLayer[i][j] = 1.f / (float)rand();
			}
		}

		for (int i = 0; i < 3; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				if (rand() % 2 == 0)
					secondLayer[i][j] = -1.f / (float)rand();				// ������������???

				else
					secondLayer[i][j] = 1.f / (float)rand();
			}
		}
	}


	// ����������� ������� ��������� 

	else   
	{
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (rand() % 97 == 0)				//   1/97 - ����������� ���������� �������� ����� (�������) 
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
				if (rand() % 97 == 0)				//   1/97 - ����������� ���������� �������� ����� 
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

Row Genotype::GetStepPosobility(Row& inputs)								// ����� - 10 ��������, ���� �� ������� - ��������(1)
{
	Row secondLayer{5};													// ������ ���� - 4 ��������� ����������� +  ��������(1)
	Row answer{3};															// �� ������ - ������ �� 3 ��������(����������� ��� ���� ��������� �����������)

	secondLayer = this->firstLayer * inputs;
	answer = this->secondLayer * secondLayer;

	return answer;
}