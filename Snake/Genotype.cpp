#include"Genotype.h"
#include<fstream>
#include <random>

Row ReLU(Row layer)
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

Row Genotype::GetStepPossibility(int inputs[])
{
	Row inputTemp{ CountOfInputs };												// 3 distances for 3 directions + offset

	for (int i = 0; i < CountOfInputs; i++)
	{
		inputTemp[i] = inputs[i];
	}

	Row secondLayer{ 7 };
	Row answerTemp{ 3 };

	secondLayer = this->firstLayer * inputTemp;
	secondLayer = ReLU(secondLayer);

	secondLayer.add((double)1);									// add = push_beck() 
	answerTemp = this->secondLayer * secondLayer;


	std::random_device randomDevice;
 	std::mt19937 engine{randomDevice()};

	if(answerTemp[0] < 0 && answerTemp[1] < 0 && answerTemp[2] < 0)			// search max when all values < 0
	{
		if(answerTemp[0] >= answerTemp[1] && answerTemp[0] >= answerTemp[2])
		{
			answerTemp[0] = 1;
			answerTemp[1] = 0;
			answerTemp[2] = 0;
		}
		if(answerTemp[1] >= answerTemp[0] && answerTemp[1] >= answerTemp[2])
		{
			answerTemp[0] = 0;
			answerTemp[1] = 1;
			answerTemp[2] = 0;
		}
		else
		{
			answerTemp[0] = 0;
			answerTemp[1] = 0;
			answerTemp[2] = 1;
		}
		return answerTemp;
	}


	/*
	1)summation all non-zero values 
	2)generate value between 0 and sum 
	3)find Interval with this value
	*/

	if(answerTemp[0] >= 0)
	{
		if(answerTemp[1] >=0)
		{
			if(answerTemp[2]>=0)
			{
				double sum = answerTemp[0] + answerTemp[1] + answerTemp[2];
				std::uniform_real_distribution <double> dist{0, sum};

				float firstInterval = answerTemp[0] / sum;
				float secondInterval = answerTemp[1] / sum + firstInterval;
				float a = dist(engine);

				if(a <= firstInterval)
				{
					answerTemp[0] = 1;
					answerTemp[1] = 0;
					answerTemp[2] = 0;
					return answerTemp;
				}
				if(a <= secondInterval)
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
			else
			{
				double sum = answerTemp[0] + answerTemp[1];
				std::uniform_real_distribution<double> dist{0, sum};

				float firstInterval = answerTemp[0] / sum;
				float a = dist(engine);

				if(a <= firstInterval)
				{
					answerTemp[0] = 1;
					answerTemp[1] = 0;
					answerTemp[2] = 0;
					return answerTemp;
				}
				else
				{
					answerTemp[0] = 0;
					answerTemp[1] = 1;
					answerTemp[2] = 0;
					return answerTemp;
				}
			}
		}
		else if(answerTemp[2] >=0)
		{
			double sum = answerTemp[0] + answerTemp[2];
			std::uniform_real_distribution<double> dist{0, sum};

			float firstInterval = answerTemp[0] / sum;
			float a = dist(engine);

			if(a <= firstInterval)
			{
				answerTemp[0] = 1;
				answerTemp[1] = 0;
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
		else
		{
			answerTemp[0] = 1;
			answerTemp[1] = 0;
			answerTemp[2] = 0;
			return answerTemp;
		}
	}
	else if(answerTemp[1]>=0)
	{
		if(answerTemp[2] >= 0)
		{
			float sum = answerTemp[1] + answerTemp[2];
			std::uniform_real_distribution<double> dist{0, sum};

			float firstInterval = answerTemp[1] / sum;
			float a = dist(engine);

			if(a <= firstInterval)
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
		else
		{
			answerTemp[0] = 0;
			answerTemp[1] = 1;
			answerTemp[2] = 0;
			return answerTemp;
		}
	}
	else
	{
		answerTemp[0] = 0;
		answerTemp[1] = 0;
		answerTemp[2] = 1;
		return answerTemp;
	}


	
	/*
	int a = answerTemp[0] * 1000;
	int b = answerTemp[1] * 1000;
	int c = answerTemp[2] * 1000;
	int abc = a + b + c;

	if (abc > 0)
	{
		while (true)
		{
			if (a >= 0 && rand() % abc <= a)
			{
				answerTemp[0] = 1;
				answerTemp[1] = 0;
				answerTemp[2] = 0;
				return answerTemp;
			}

			if (b >= 0 && rand() % abc <= b)
			{
				answerTemp[0] = 0;
				answerTemp[1] = 1;
				answerTemp[2] = 0;
				return answerTemp;
			}

			if (c >= 0 && rand() % abc <= c)
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
	*/
}

void Genotype::SetFromFile()
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