#include"Matrix.h"
#include "ctime"
#include<iostream>

Row::Row()
{
	this->lenth = 0;
}
Row::Row(int lenth)
{
	srand(time(NULL));

	this->lenth = lenth;
	this->row = new float[lenth];

	for (int i = 0; i < lenth; i++)
		this->row[i] = NULL;
}

Matrix::Matrix()
{
	this->countOfColumn = 0;
	this->countOfRow = 0;
}
Matrix::Matrix(int countOfRow, int countOfColumn)
{
	srand(time(NULL));

	this->countOfColumn = countOfColumn;
	this->countOfRow = countOfRow;

	for (int i = 0; i < countOfRow; i++)
	{
		Row temp{ countOfColumn };
		this->matrix.push_back(temp);
	}
}

int Matrix::GetCountOfRow()
{
	return this->countOfRow;
}
int Matrix::GetCountOfColumn()
{
	return this->countOfColumn;
}
std::vector<Row>& Matrix::GetMatrix()
{
	return this->matrix;
}
void Matrix::SetMatrix(Matrix prevGeneration[])
{
	const int countOfRow = prevGeneration[0].GetCountOfRow();
	const int countOfColumn = prevGeneration[0].GetCountOfColumn();

	std::vector<Row> child;

	for (int i = 0; i < countOfRow; i++)
	{
		Row temp{ countOfColumn };
		child.push_back(temp);
	}

	for (int i = 0; i < countOfRow; i++)
	{
		for (int j = 0; j < countOfColumn; j++)
		{

			// "Мутация"
			// С маленькой вероятность может сгенерироваться случайные весы (Ограничить?)

			if (rand() % 98 == 0)											
			{
				child[i][j] = 1.f / (float)rand();							
			}

			// 50 / 50 - выбираем случайную комбинацию весов 2-ух наилучших робителей 

			else if (rand() % 2 == 0)
			{
				child[i][j] = prevGeneration[0].GetMatrix()[i][j];				
			}
			else
			{
				child[i][j] = prevGeneration[1].GetMatrix()[i][j];
			}
		}
	}

	this->matrix = child;
}
void Matrix::SetSize(int countOfRow, int countOfColumn)
{
	this->countOfColumn = countOfColumn;
	this->countOfRow = countOfRow;
}

Matrix& Matrix::operator+(Matrix& m2)
{
	const int countOfRow = m2.GetCountOfRow();
	const int countOfColumn = m2.GetCountOfColumn();

	std::vector<Row> temp = m2.GetMatrix();

	for (int i = 0; i < countOfRow; i++)
	{
		for (int j = 0; j < countOfColumn; j++)
		{
			this->matrix[i][j] += temp[i][j];
		}
	}

	return *this;
}
Matrix& Matrix::operator-(Matrix& m2)
{
	const int countOfRow = m2.GetCountOfRow();
	const int countOfColumn = m2.GetCountOfColumn();

	std::vector<Row> temp = m2.GetMatrix();

	for (int i = 0; i < countOfRow; i++)
	{
		for (int j = 0; j < countOfColumn; j++)
		{
			this->matrix[i][j] -= temp[i][j];
		}
	}

	return *this;
}
Row& Matrix::operator*(Row& r)
{
	Row ans{ this->GetCountOfRow() };

	std::vector<Row> temp = this->GetMatrix();

	const int countOfRow = this->countOfRow;
	const int countOfColumn = this->countOfColumn;

	for (int i = 0; i < countOfRow; i++)
	{
		for (int j = 0; j < countOfColumn; j++)
		{
			ans[i] += temp[i][j] * r[j];
		}
	}

	return ans;
}
Row& Row::operator+(Row& r2)
{
	if (this->lenth != r2.GetLenth())
		return *this;

	for (int i = 0; i < this->lenth; i++)
	{
		this->row[i] += r2[i];
	}

	return *this;
}

Matrix& RowToMatrix(Row& r, int layer)								// слой весов (1 или 2) нужно посчитать количество весов для первого и второго слоя																	
{																	// 1 слой : 5х10 * 10х1	(4 направления + смещение 9 инпутов + смещение),	2 слой: 3x5 * 5x1
	int pointer = 0;
	if (layer == 1)
	{
		Matrix temp{ 5,10 };

		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				temp[i][j] = r[pointer];
				pointer++;
			}
		}

		return temp;
	}

	Matrix temp{3,5};

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			temp[i][j] = r[pointer];
			pointer++;
		}
	}
	
	return temp;
}
Row& MatrixToRow(Matrix& m)
{
	const int countOfRow = m.GetCountOfRow();
	const int countOfColumn = m.GetCountOfColumn();

	int lenth = countOfColumn * countOfRow;

	Row temp{lenth};

	int pointer = 0;

	for (int i = 0; i < countOfRow; i++)
	{
		for (int j = 0; j < countOfColumn; j++, pointer++)
		{
			temp[pointer] = m[i][j];
		}
	}

	return temp;
}