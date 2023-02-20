#include"Genotype.h"
#include<fstream>
#include <random>

Row ReLU(Row layer)
{
	for (int i = 0; i < Weights; i++)
	{
		if (layer[i] < 0)
			layer[i] = 0;
	}

	return layer;
}

Genotype::Genotype()
{
	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{

			if (rand() % 2 == 0)
				layer_1[i][j] = -1.f / ((rand() % 100) + 1);

			else
				layer_1[i][j] = 1.f / ((rand() % 100) + 1);
		}
		if (rand() % 2 == 0)
			{
				intersept_1[i][0] = -1.f / ((rand() % 100) + 1);
			}
		else
			{
				intersept_1[i][0] = 1.f / ((rand() % 100) + 1);
			}
	}

	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			if (rand() % 2 == 0)
			{
				layer_2[i][j] = -1.f / ((rand() % 100) + 1);
				layer_3[i][j] = -1.f / ((rand() % 100) + 1);
				layer_4[i][j] = -1.f / ((rand() % 100) + 1);
			}
			else
			{
				layer_2[i][j] = 1.f / ((rand() % 100) + 1);
				layer_3[i][j] = 1.f / ((rand() % 100) + 1);
				layer_4[i][j] = 1.f / ((rand() % 100) + 1);
			}
		}

		if (rand() % 2 == 0)
			{
				intersept_2[i][0] = -1.f / ((rand() % 100) + 1);
				intersept_3[i][0] = -1.f / ((rand() % 100) + 1);
				intersept_4[i][0] = -1.f / ((rand() % 100) + 1);
			}
		else
			{
				intersept_2[i][0] = 1.f / ((rand() % 100) + 1);
				intersept_3[i][0] = 1.f / ((rand() % 100) + 1);
				intersept_4[i][0] = 1.f / ((rand() % 100) + 1);
			}
	}
	for (int i = 0; i < Outputs; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			if (rand() % 2 == 0)
			{
				layer_5[i][j] = -1.f / ((rand() % 100) + 1);
			}
			else
			{
				layer_5[i][j] = 1.f / ((rand() % 100) + 1);
			}
		}

		if (rand() % 2 == 0)
			{
				intersept_5[i][0] = -1.f / ((rand() % 100) + 1);
			}
		else
			{
				intersept_5[i][0] = 1.f / ((rand() % 100) + 1);
			}
	}
}
Genotype::Genotype(Genotype* bestParents)
{

	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{
			if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					layer_1[i][j] = -1.f / ((rand() % 100) + 1);

				else
					layer_1[i][j] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				layer_1[i][j] = bestParents[1].layer_1[i][j];

			else
				layer_1[i][j] = bestParents[0].layer_1[i][j];
		}

		if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					intersept_1[i][0] = -1.f / ((rand() % 100) + 1);

				else
					intersept_1[i][0] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				intersept_1[i][0] = bestParents[1].intersept_1[i][0];

			else
				intersept_1[i][0] = bestParents[0].intersept_1[i][0];
	}

	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
				{
					layer_2[i][j] = -1.f / ((rand() % 100) + 1);
					layer_3[i][j] = -1.f / ((rand() % 100) + 1);
					layer_4[i][j] = -1.f / ((rand() % 100) + 1);
				}

				else
				{
					layer_2[i][j] = 1.f / ((rand() % 100) + 1);
					layer_3[i][j] = 1.f / ((rand() % 100) + 1);
					layer_4[i][j] = 1.f / ((rand() % 100) + 1);
				}
			}

			else if (rand() % 3 > 0)
			{
				layer_2[i][j] = bestParents[1].layer_2[i][j];
				layer_3[i][j] = bestParents[1].layer_3[i][j];
				layer_4[i][j] = bestParents[1].layer_4[i][j];
			}

			else
			{
				layer_2[i][j] = bestParents[0].layer_2[i][j];
				layer_3[i][j] = bestParents[0].layer_3[i][j];
				layer_4[i][j] = bestParents[0].layer_4[i][j];
			}
		}
		if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
				{
					intersept_1[i][0] = -1.f / ((rand() % 100) + 1);
					intersept_2[i][0] = -1.f / ((rand() % 100) + 1);
					intersept_3[i][0] = -1.f / ((rand() % 100) + 1);
				}

				else
				{
					intersept_1[i][0] = 1.f / ((rand() % 100) + 1);
					intersept_2[i][0] = 1.f / ((rand() % 100) + 1);
					intersept_3[i][0] = 1.f / ((rand() % 100) + 1);
				}
			}

			else if (rand() % 3 > 0)
			{
				intersept_1[i][0] = bestParents[1].intersept_1[i][0];
				intersept_2[i][0] = bestParents[1].intersept_2[i][0];
				intersept_3[i][0] = bestParents[1].intersept_3[i][0];
			}

			else
			{
				intersept_1[i][0] = bestParents[0].intersept_1[i][0];
				intersept_3[i][0] = bestParents[0].intersept_3[i][0];
				intersept_2[i][0] = bestParents[0].intersept_2[i][0];
			}
	}
	for (int i = 0; i < Outputs; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					layer_5[i][j] = -1.f / ((rand() % 100) + 1);

				else
					layer_5[i][j] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				layer_5[i][j] = bestParents[1].layer_5[i][j];

			else
				layer_5[i][j] = bestParents[0].layer_5[i][j];
		}
		if (rand() % 40 == 0)
			{
				if (rand() % 2 == 0)
					intersept_5[i][0] = -1.f / ((rand() % 100) + 1);

				else
					intersept_5[i][0] = 1.f / ((rand() % 100) + 1);
			}

			else if (rand() % 3 > 0)
				intersept_5[i][0] = bestParents[1].intersept_5[i][0];

			else
				intersept_5[i][0] = bestParents[0].intersept_5[i][0];
	}
}

void Sum(Row& r, Matrix& m)
{
	for(int i = 0; i < r.size(); i++)
	{
		r[i] += m[i][0];
	}
}
Row Genotype::GetStepPossibility(int inputs[])
{
	Row inputTemp{ CountOfInputs };												// 3 distances for 3 directions + offset

	for (int i = 0; i < CountOfInputs; i++)
	{
		inputTemp[i] = inputs[i];
	}

	Row L1{ Weights };
	Row L2{ Weights };
	Row L3{ Weights };
	Row L4{ Weights };

	Row answerTemp{ Outputs };

	L1 = this->layer_1 * inputTemp;
	Sum(L1, this->intersept_1);
	L1 = ReLU(L1);

	L2 = this->layer_2 * L1;
	Sum(L2, this->intersept_2);
	L2 = ReLU(L2);

	L3 = this->layer_3 * L2;
	Sum(L3, this->intersept_3);
	L3 = ReLU(L3);

	L4 = this->layer_4 * L3;
	Sum(L4, this->intersept_4);
	L4 = ReLU(L4);

										// add = push_beck() 
	answerTemp = this->layer_5 * L4;
	Sum(answerTemp, this->intersept_5);


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
	std::ifstream layer_1;
	std::ifstream layer_2;
	std::ifstream layer_3;
	std::ifstream layer_4;
	std::ifstream layer_5;
	std::ifstream intercepts_1;
	std::ifstream intercepts_2;
	std::ifstream intercepts_3;
	std::ifstream intercepts_4;
	std::ifstream intercepts_5;

    layer_1.open("layer_1.txt", std::ifstream::in);
    layer_2.open("layer_2.txt",std::ifstream::in);
	layer_3.open("layer_3.txt", std::ifstream::in);
    layer_4.open("layer_4.txt",std::ifstream::in);
	layer_5.open("layer_5.txt", std::ifstream::in);
    intercepts_1.open("intercepts_1.txt",std::ifstream::in);
	intercepts_2.open("intercepts_2.txt", std::ifstream::in);
    intercepts_3.open("intercepts_3.txt",std::ifstream::in);
	intercepts_4.open("intercepts_4.txt", std::ifstream::in);
    intercepts_5.open("intercepts_5.txt",std::ifstream::in);

    if(layer_1.is_open()) std::cout << "l1 loaded." << std::endl;
    if(layer_2.is_open()) std::cout << "l2 file loaded." << std::endl;
	if(layer_3.is_open()) std::cout << "l3 file loaded." << std::endl;
    if(layer_4.is_open()) std::cout << "l4 file loaded." << std::endl;
	if(layer_5.is_open()) std::cout << "l5 file loaded." << std::endl;
    if(intercepts_1.is_open()) std::cout << "i1 file loaded." << std::endl;
	if(intercepts_2.is_open()) std::cout << "i2 file loaded." << std::endl;
    if(intercepts_3.is_open()) std::cout << "i3 file loaded." << std::endl;
	if(intercepts_4.is_open()) std::cout << "i4 file loaded." << std::endl;
    if(intercepts_5.is_open()) std::cout << "i5 file loaded." << std::endl;

	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < CountOfInputs; j++)
		{
			layer_1 >> this->layer_1[i][j];
			intercepts_1 >> this->intersept_1[i][j];
		}
	}

	for (int i = 0; i < Weights; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			layer_2 >> this->layer_2[i][j];
			layer_3 >> this->layer_3[i][j];
			layer_4 >> this->layer_4[i][j];

			intercepts_2 >> this->intersept_2[i][j];
			intercepts_3 >> this->intersept_3[i][j];
			intercepts_4 >> this->intersept_4[i][j];
		}
	}

	for (int i = 0; i < Outputs; i++)
	{
		for (int j = 0; j < Weights; j++)
		{
			layer_5 >> this->layer_5[i][j];
			intercepts_5 >> this->intersept_5[i][j];
		}
	}

	layer_1.close();
	layer_2.close();
	layer_3.close();
	layer_4.close();
	layer_5.close();

	intercepts_1.close();
	intercepts_2.close();
	intercepts_3.close();
	intercepts_4.close();
	intercepts_5.close();
}