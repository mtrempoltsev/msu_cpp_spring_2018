#pragma once

#include <vector>
#include <algorithm>

class Array
{
public:
	const int& operator[](int row_) const
	{
		int row = array.size();
		if (row_ >= row)
			throw std::out_of_range("");

		return array[row_];
	}

	int& operator[](int row_)
	{
		int row = array.size();
		if (row_ >= row)
			throw std::out_of_range("");

		return array[row_];
	}

	Array& operator*=(int val)
	{
		std::for_each(array.begin(), array.end(), [val](int &n) { n *= val; });
		return *this;
	}

	bool operator==(const Array& other) const
	{
		return array == other.array;
	}

	bool operator!=(const Array& other) const
	{
		array != other.array;
	}

	void resize(size_t new_size)
	{
		array.resize(new_size);
	}

private:
	std::vector<int> array;
};

class Matrix
{
private:
	std::vector<Array> matrix;

	int row;
	int col;

public:

	int getRows() { return row; }
	int getColumns() { return col; }

	Matrix(const int col_, const int row_)
	{
		row = row_;
		col = col_;

		matrix.resize(col);

		for (int i = 0; i < col; i++)
			matrix[i].resize(row);
	}

	const Array& operator[](int row_) const
	{
		if (row_ > row || row == 0)
			throw std::out_of_range("");
		return matrix[row_];
	}

	Array& operator[](int row_)
	{
		if (row_ > row || row == 0)
			throw std::out_of_range("");
		return matrix[row_];
	}

	Matrix& operator*=(int val)
	{
		std::for_each(matrix.begin(), matrix.end(), [val](Array &vec) { vec *= val; });
		return *this;
	}

	bool operator==(const Matrix& other) const
	{
		if (!(row == other.row && col == other.col))
			return false;

		for (int i = 0; i < row; i++)
		{
			if (!(matrix[i] == other[i]))
				return false;
		}

		return true;
	}

	bool operator!=(const Matrix& other) const
	{
		if (!(row == other.row && col == other.col))
			return true;

		return !(*this == other);
	}
};