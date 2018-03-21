#pragma once
#include <exception>

class Matrix
{
	const size_t rows;
	const size_t cols;
	friend class str;
public:
	class str
	{
		int *a;
		const size_t cols;
		public:
			str(size_t _s, int *_arr): cols(_s), a(_arr) {}

			~str()
			{
				delete [] a;
			}

			int& operator[](int ind) 
			{
				if ( (-1 >= ind) || (ind >= cols) )
					throw std::out_of_range("");
				return a[ind];
			}
			
	};

private:
	int **a;
public:
	Matrix(size_t _rows, size_t _cols): rows(_rows), cols(_cols) 
	{
		a = new int*[rows];
		for(int i = 0; i < rows; i++) {
			try {
				a[i] = new int[cols];
			} 
			catch(std::bad_alloc &ex) {
				for(int j = 0; j < i; j++) delete a[i];
				throw ex;
			}
		}
	}

	~Matrix()
	{
		for(int i = 0; i < rows; i++) delete a[i];
		delete [] a;
	}

	str operator[](int ind) const
	{
		if ( (-1 >= ind) || (ind >= rows) )
			throw std::out_of_range("");
		str s(cols, a[ind]);
		return s;
	}

	void operator*=(int mult)
	{
		for(int i = 0; i < rows; i++)
		{
			for(int j = 0; j < cols; j++)
			{
				a[i][j] *= mult;
			}
		}
	}

	bool operator==(const Matrix &b) const
	{
		bool flag = true;
		for(int i = 0; (i < rows) && flag; i++)
		{
			for(int j = 0; (j < cols) && flag; j++)
			{
				flag = (a[i][j] == b[i][j]);
			}
		}
		return flag;	
	}

	bool operator!=(const Matrix &b) const
	{
		bool flag = true;
		for(int i = 0; (i < rows) && flag; i++)
		{
			for(int j = 0; (j < cols) && flag; j++)
			{
				flag = (a[i][j] != b[i][j]);
			}
		}
		return flag;	
	}

	int getRows() const
	{
		return rows;
	}

	int getColumns() const
	{
		return cols;
	}

};
