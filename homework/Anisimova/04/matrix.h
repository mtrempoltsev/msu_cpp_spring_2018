#include <iostream>
#include <stdio.h>

class Matrix
{
private:
	int **matr;
	int rows;
	int cols;

	class Array
	{
		int *arr;
		int arr_len;
	public:
		Array(int *a, int len)
		{
			arr_len = len;
			arr = a;
                }

                int &operator[](int i) const
		{
                        if(i < arr_len && i>-1)
			{
				return arr[i];
			}
			else 
				throw std::out_of_range("");
		}
	};

public:
	Matrix(int x, int y)
	{
                cols = x;
		rows = y;
		matr = new int* [cols];
		for (int i = 0; i < cols; i ++)
			matr[i] = new int[rows];
        }
	~Matrix()
	{
		for (int i = 0; i < cols; i ++)
			delete [] matr[i];
		delete [] matr;
	}
	int getRows() const
	{
		return rows;
	}
	int getColumns () const
	{
		return cols;
	}

	const Array operator[](int j) const
	{
		if(j < cols && j >-1)
		{
			Array arr(matr[j], rows);
			return arr;
		}
		else
			throw std::out_of_range("");
	}


    const int& operator()(int i, int j) const {
        return matr[i][j];
    }

    int& operator()(int i, int j){
        return matr[i][j];
    }


    bool operator == (const Matrix &matr_2) const
    {
        if (rows != matr_2.rows || cols != matr_2.cols)
            return false;
        else  
            for (int i = 0; i < rows; i ++)
                for (int j = 0; j < cols; j ++)
                {
                    if (matr[i][j] != matr_2.matr[i][j])
                        return false;
                }
        return true;        
    }


    bool operator != (const Matrix &matr_2) const
    {
        return !((*this) == matr_2);
    }

    Matrix& operator *= (int C)
    {
		for (int i = 0; i < cols; i ++)
			for (int j = 0; j < rows; j++)
			{
				(*this)[i][j] *= C;
			}
                return *this;
    }
};
