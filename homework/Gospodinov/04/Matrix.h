class Matrix
{
private:
	int** data;
	size_t row_size;
	size_t col_size;
public:
	class Array
	{
	private:
		int* data;
		size_t size;
	public:
		int& operator[](size_t i)
		{
			if (i < size)
				return data[i];
			else
				throw std::out_of_range("");
		}
		Array(int* data, size_t size)
		{
			this->data = data;
			this->size = size;
		}
	};
	Array operator[](size_t i)
	{
		if (i < col_size)
			return Array(data[i], row_size);
		else
			throw std::out_of_range("");
	}
	Matrix(size_t cols, size_t rows)
	{
		row_size = rows;
		col_size = cols;
		data = new int*[cols];
		for (size_t i = 0; i < cols; i++)
			data[i] = new int[rows];
	}
	size_t getRows(void)
	{
		return row_size;
	}
	size_t getColumns(void)
	{
		return col_size;
	}
	const Matrix& operator*=(int n)
	{
		for (size_t i = 0; i < col_size; i++)
		{
			for (size_t j = 0; j < row_size; j++)
				data[i][j] *= n;
		}
		return *this;
	}
	bool operator==(const Matrix& other) const
	{
		if (col_size != other.col_size || row_size != other.row_size)
			return false;
		for (size_t i = 0; i < col_size; i++)
		{
			for (size_t j = 0; j < row_size; j++)
			{
				if (data[i][j] != other.data[i][j])
					return false;
			}
		}
		return true;
	}
	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}
	~Matrix()
	{
		for (size_t i = 0; i < col_size; i++)
		{
			delete[] data[i];
		}
		delete[] data;
	}
};