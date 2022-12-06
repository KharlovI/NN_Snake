#include"Genotype.h"
#include<fstream>

Row Norm(Row layer)
{
	for (int i = 0; i < 7; i++)
	{
		if (layer[i] < 0)
			layer[i] = 0;
	}

	return layer;
}


Genotype::Genotype()
{
	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{

			if (rand() % 2 == 0)
				firstLayer[i][j] = -1.f / ((rand() % 100) + 1);

			else
				firstLayer[i][j] = 1.f / ((rand() % 100) + 1);
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (rand() % 2 == 0)
				secondLayer[i][j] = -1.f / ((rand() % 100) + 1);

			else
				secondLayer[i][j] = 1.f / ((rand() % 100) + 1);
		}
	}
}
Genotype::Genotype(Genotype* bestParents)
{

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{
			if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					firstLayer[i][j] = -1.f / ((rand() % 100) + 1);

				else
					firstLayer[i][j] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				firstLayer[i][j] = bestParents[1].firstLayer[i][j];

			else
				firstLayer[i][j] = bestParents[0].firstLayer[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					secondLayer[i][j] = -1.f / ((rand() % 100) + 1);

				else
					secondLayer[i][j] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				secondLayer[i][j] = bestParents[1].secondLayer[i][j];

			else
				secondLayer[i][j] = bestParents[0].secondLayer[i][j];
		}
	}
}

Row Genotype::GetStepPosobility(int inputs[])
{
	Row inputTemp{ CountOfInputs };												// 3 distances for 3 directions + offset

	for (int i = 0; i < CountOfInputs; i++)
	{
		inputTemp[i] = inputs[i];
	}

	Row secondLayer{ 7 };
	Row answerTemp{ 3 };

	secondLayer = this->firstLayer * inputTemp;
	secondLayer = Norm(secondLayer);

	secondLayer.add((double)1);									// add = push_beck() 
	answerTemp = this->secondLayer * secondLayer;




	int a = answerTemp[0] * 1000;
	int b = answerTemp[1] * 1000;
	int c = answerTemp[2] * 1000;
	int abc = a + b + c;

	if (abc > 0)
	{
		while (true)
		{
			if (rand() % abc <= a && a >= 0)
			{
				answerTemp[0] = 1;
				answerTemp[1] = 0;
				answerTemp[2] = 0;
				return answerTemp;
			}

			if (rand() % abc <= b && b >= 0)
			{
				answerTemp[0] = 0;
				answerTemp[1] = 1;
				answerTemp[2] = 0;
				return answerTemp;
			}

			if (rand() % abc <= c && c >= 0)
			{
				answerTemp[0] = 0;
				answerTemp[1] = 0;
				answerTemp[2] = 1;
				return answerTemp;
			}
		}
	}
	if (answerTemp[0] >= answerTemp[1] && answerTemp[0] >= answerTemp[2])
	{
		answerTemp[0] = 1;
		answerTemp[1] = 0;
		answerTemp[2] = 0;
		return answerTemp;
	}

	if (answerTemp[1] >= answerTemp[0] && answerTemp[1] >= answerTemp[2])
	{
		answerTemp[0] = 0;
		answerTemp[1] = 1;
		answerTemp[2] = 0;
		return answerTemp;
	}

	else
	{
		answerTemp[0] = 0;
		answerTemp[1] = 0;
		answerTemp[2] = 1;
		return answerTemp;
	}
}

void Genotype::SetFromeFile()
{
	std::ifstream file1;
	std::ifstream file2;
    file1.open("firstLayer.txt", std::ifstream::in);
    file2.open("secondLayer.txt",std::ifstream::in);

    if(file1.is_open()) std::cout << "First layer file loaded." << std::endl;
    if(file2.is_open()) std::cout << "Second layer file loaded." << std::endl;

	for (int i = 0; i < 7; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{
			file1 >> this->firstLayer[i][j];
		}
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			file2 >> this->secondLayer[i][j];
		}
	}

	file1.close();
	file2.close();
}
