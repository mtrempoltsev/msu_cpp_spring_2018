class Matrix
{
private:
	int*M;
	size_t row, column;
public:
	class Helper
	{
	private:
		int* L;
		size_t c;
	public:
		Helper(size_t cc, int*line)
		{
			c = cc;
			L = line;
		}
		int& operator[](const size_t i) const
		{
			if (i >= c)
				throw std::out_of_range("");
			else
				return L[i];
		}
		~Helper() {}
	};
	size_t getRows() const
	{
		return column;
	}
	size_t getColumns() const
	{
		return row;
	}
	Matrix(size_t x, size_t y)
	{
		row = x;
		column = y;
		M = new int[row*column];
	}
	Helper operator[](const size_t i) const
	{
		if (i >= row)
			throw std::out_of_range("");
		else
			return Helper(this->getRows(), M + i*row);
	}
	bool operator==(const Matrix& other) const
	{
		if ((this->getRows() != other.getRows()) || (this->getColumns() != other.getColumns()))
			return false;
		for (size_t i = 0; i < row; ++i)
			for (size_t j = 0; j < column;++j)
				if ((*this)[i][j] != other[i][j])
					return false;
		return true;
	}
	bool operator!=(const Matrix& other) const
	{
		return !(*this == other);
	}
	Matrix& operator*=(int a)
	{
		for (size_t i = 0; i < row; ++i)
			for (size_t j = 0; j < column; ++j)
				(*this)[i][j] *= a;
		return (*this);
	}
	~Matrix() {}
};