class Matrix
{
private:
	size_t column, row;
	int* M;
	class Helper
	{
	private:
		int* L;
		size_t c;
	public:
		Helper(int*line, size_t cc)
			: L(line)
			, c(cc)
		{}
		int& operator[](const size_t i)
		{
			if (i >= c)
				throw std::out_of_range("");
			else
				return L[i];
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
public:
	size_t getRows() const
	{
		return row;
	}
	size_t getColumns() const
	{
		return column;
	}
	Matrix(size_t x, size_t y)
		: column(x)
		, row(y)
	{
		M = new int[column*row];
	}
	Helper operator[](const size_t i)
	{
		if (i >= column)
			throw std::out_of_range("");
		else
			return Helper(M + i*row, this->getRows());
	}
	Helper operator[](const size_t i) const
	{
		if (i >= column)
			throw std::out_of_range("");
		else
			return Helper(M + i*row, this->getRows());
	}
	bool operator==(const Matrix& other) const
	{
		if ((this->getRows() != other.getRows()) || (this->getColumns() != other.getColumns()))
			return false;
		for (size_t i = 0; i < column; ++i)
			for (size_t j = 0; j < row;++j)
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
		for (size_t i = 0; i < column; ++i)
			for (size_t j = 0; j < row; ++j)
				(*this)[i][j] *= a;
		return (*this);
	}
	~Matrix()
	{
		delete [] M;
	}
};
