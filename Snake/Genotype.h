#pragma once
#include"Matrix.h"

class Genotype
{
private:
	Matrix firstLayer{10,5};				// ������ ���� ����� 
	Matrix secondLayer{5,3};				// ������ ���� ����� 
public:
	Genotype();
	Genotype(int generation, Genotype bestParents[]); // if(generation == 0) ��������� ������� ���������� ������
	Row GetStepPosobility(Row& inputs);
};