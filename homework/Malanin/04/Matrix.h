#pragma once

#include <iostream>

class Proxy
{
	int *col;
	int num;
public:
	Proxy();
	void setnum(int _num);
	int& operator[](int i);
	const int& operator[](int i) const;
	~Proxy();
};

Proxy::Proxy()
{
	num = 0;
}

void Proxy::setnum(int _num)
{
	num = _num;
	col = new int[num];
}



int& Proxy::operator[](int i)
{
	if ((i < 0) || (i >= num)) throw std::out_of_range("");
	return col[i];
}

const int& Proxy::operator[](int i) const
{
	if ((i < 0) || (i >= num)) throw std::out_of_range("");
	return col[i];
}

Proxy::~Proxy()
{
	delete[] col;
}


class Matrix
{
	int num_cols;
	int num_rows;
	Proxy* cols;
public:
	Matrix(int _cols, int _rows);
	~Matrix();
	int getColumns() const;
	int getRows() const;
	Proxy& operator[](int i);
	const Proxy& operator[](int i) const;
	bool operator==(const Matrix& m2);
	bool operator!=(const Matrix& m2);
	Matrix& operator*=(int m);
};


Matrix::Matrix(int _cols, int _rows) :num_cols(_cols), num_rows(_rows)
{
	cols = new Proxy[num_cols];
	for (int i = 0; i < num_cols; i++)
	{
		cols[i].setnum(num_rows);
	}
}

Matrix::~Matrix()
{
	delete[] cols;
}

int Matrix::getColumns() const
{
	return num_cols;
}

int Matrix::getRows() const
{
	return num_rows;
}

Proxy& Matrix::operator[](int i)
{
	if ((i < 0) || (i >= num_cols)) throw std::out_of_range("");
	return cols[i];
}

const Proxy& Matrix::operator[](int i) const
{
	if ((i < 0) || (i >= num_cols)) throw std::out_of_range("");
	return cols[i];
}

bool Matrix::operator==(const Matrix& m2)
{
	if ((num_cols != m2.num_cols) || (num_rows != m2.num_rows)) return false;
	for (int i = 0; i < num_cols; i++)
		for (int j = 0; j < num_rows; j++)
		{
			if ((*this)[i][j] != m2[i][j]) return false;
		}
	return true;
}

bool Matrix::operator!=(const Matrix& m2)
{
	return (!((*this) == m2));
}

Matrix& Matrix::operator*=(int m)
{
	for (int i = 0; i < num_cols; i++)
		for (int j = 0; j < num_rows; j++)
		{
			(*this)[i][j] *= m;
		}
	return *this;
}
