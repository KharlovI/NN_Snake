#pragma once
#include <vector>

class Row
{
private:
	float* row;
	int lenth;
public:
	Row();
	Row(int lenth);

	int GetLenth() { return this->lenth; }

	float& operator[](int position) { return this->row[position]; }
	//Row& operator *(Row& r2);
	Row& operator +(Row& r2);
};

class Matrix
{
private:
	int countOfRow;
	int countOfColumn;

	std::vector<Row> matrix;

public:
	Matrix();
	Matrix(int countOfRow, int countOfColumn);				// Генерируем рандомные значения

	int GetCountOfRow();
	int GetCountOfColumn();
	std::vector<Row>& GetMatrix();
	

	void SetMatrix(Matrix prevGeneration[]);				// Передаем 2 лучших родителей 
	void SetSize(int countOfRow, int countOfColumn);											//?????

	Matrix& operator +(Matrix& m2);
	Matrix& operator -(Matrix& m2);
	Row& operator *(Row& r);								// Матрица * вектор

	Row& operator[](int indexI) { return this->matrix[indexI]; }
};

Matrix& RowToMatrix(Row& r);
Row& MatrixToRow(Matrix& m);								// матрицу размером m x n перевожу в строку m*n длины 