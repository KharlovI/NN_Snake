#pragma once
#include"Matrix.h"
constexpr int CountOfInputs = 11;
constexpr int Weights = 12;
constexpr int Outputs = 3;

class Genotype
{
private:
	Matrix layer_1{ CountOfInputs, Weights};				
	Matrix layer_2{ Weights, Weights };
	Matrix layer_3{ Weights, Weights };
	Matrix layer_4{ Weights, Weights };
	Matrix layer_5{ Weights, Outputs};

	Matrix intersept_1{1,Weights};
	Matrix intersept_2{1,Weights};
	Matrix intersept_3{1,Weights};
	Matrix intersept_4{1,Weights};
	Matrix intersept_5{1,Outputs};
public:
	Genotype();
	Genotype(Genotype* bestParents);
	Row GetStepPossibility(int inputs[]);

	Matrix GetFirstLayer() { return this->layer_1; }
	Matrix GetSecondLayer() { return this->layer_2; }
	Matrix GetThirdLayer() { return this->layer_3; }
	Matrix GetFourthLayer() { return this->layer_4; }
	Matrix GetFifthLayer() { return this->layer_5; }

	Matrix GetFirstIntercepts() { return this->intersept_1; }
	Matrix GetSecondIntercepts() { return this->intersept_2; }
	Matrix GetThirdIntercepts() { return this->intersept_3; }
	Matrix GetFourthIntercepts() { return this->intersept_4; }
	Matrix GetFifthIntercepts() { return this->intersept_5; }
	void SetFromFile();
	void operator =(Genotype g2)
	{
		for (int i = 0; i < Weights; i++)
		{
			for (int j = 0; j < CountOfInputs; j++)
			{
				this->layer_1[i][j] = g2.layer_1[i][j];
			}
			this->intersept_1[i][0] = g2.intersept_1[i][0];
		}

		for (int i = 0; i < Weights; i++)
		{
			for (int j = 0; j < Weights; j++)
			{
				this->layer_2[i][j] = g2.layer_2[i][j];
			}
			this->intersept_2[i][0] = g2.intersept_2[i][0];
		}

		for (int i = 0; i < Weights; i++)
		{
			for (int j = 0; j < Weights; j++)
			{
				this->layer_3[i][j] = g2.layer_3[i][j];
			}
			this->intersept_3[i][0] = g2.intersept_3[i][0];
		}

		for (int i = 0; i < Weights; i++)
		{
			for (int j = 0; j < Weights; j++)
			{
				this->layer_4[i][j] = g2.layer_4[i][j];
			}
			this->intersept_4[i][0] = g2.intersept_4[i][0];
		}

		for (int i = 0; i < Outputs; i++)
		{
			for (int j = 0; j < Weights; j++)
			{
				this->layer_5[i][j] = g2.layer_5[i][j];
			}
			this->intersept_5[i][0] = g2.intersept_5[i][0];
		}
	}
};