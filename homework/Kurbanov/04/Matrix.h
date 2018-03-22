class Matrix 
{
	size_t _cols, _rows;
	int** _m;
	class Proxy 
	{
		size_t _row;
		int* data;
	public:
		Proxy(size_t row, int *d) :
			_row(row), data(d) {}
		int& operator[](size_t row)
		{
			if (row >= _row)
				throw std::out_of_range("");
			return data[row];
		}
		const int& operator[](size_t row) const
		{
			if (row >= _row)
				throw std::out_of_range("");
			return data[row];
		}
	};
public:
	Matrix(size_t c, size_t r) :
		_cols(c), _rows(r), _m(new int*[c]) {
		for (size_t i = 0; i < _cols; i++) {
			_m[i] = new int[r];
		}
	}
	~Matrix() {
		for (size_t i = 0; i < _cols; i++) {
			delete[] _m[i];
		}
		delete[] _m;
	}
	int getRows() {return _rows;}
	int getColumns() {return _cols;}
	Proxy operator[](size_t col)
	{
		if (col < 0 || col >= _cols)
			throw std::out_of_range("");
		return Proxy(_rows, _m[col]);
	}
	const Proxy operator[](size_t col) const 
	{
		if (col < 0 || col >= _cols)
			throw std::out_of_range("");
		return Proxy(_rows, _m[col]);
	}

	bool operator==(const Matrix &R) const
	{
		if (this->_cols != R._cols || this->_rows != R._rows)
			return false;

		for (size_t i = 0; i < _cols; i++)
			for (size_t j = 0; j < _rows; j++)
				if (_m[i][j] != R[i][j]) return false;
		return true;
	}

	bool operator!=(Matrix& R) const {return !(*this == R);}
	
	Matrix* operator*=(int factor)
	{
		for (int i = 0; i < _cols; ++i)
			for(int j=0; j<_rows;++j)
				_m[i][j] *= factor;
		return this;
	}
};
