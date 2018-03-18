class Matrix 
{
	size_t _cols, _rows;
	int* _m;
	class Proxy
	{
		size_t _col;
		Matrix* data;
	public:
		Proxy(size_t col, Matrix* d):
			_col(col), data(d) {}
		int& operator[](size_t row)
		{
			if (row < 0 || row >= data->_rows)
				throw std::out_of_range("жопа");
			return data->_m[row * data->_cols + _col];
		}
	};
public:
	Matrix(size_t c, size_t r) :
		_cols(c), _rows(r), _m(new int[c*r]) {}
	~Matrix() {delete[] _m;}
	int getRows() {return _rows;}
	int getColumns() {return _cols;}
	Proxy operator[](size_t col)
	{
		if (col < 0 || col >= _cols)
			throw std::out_of_range("");
		return Proxy(col, this);
	}

	bool operator==(const Matrix &R) const
	{
		if (this->_cols != R._cols || this->_rows != R._rows)
			return false;

		for (int i = 0; i < _rows*_cols; ++i)
		{
			if (this->_m[i] != R._m[i])
				return false;
		}
		return true;
	}

	bool operator!=(Matrix& R) const {return !(*this == R);}
	
	Matrix* operator*=(int factor)
	{
		for (int i = 0; i < _rows*_cols; ++i)
			_m[i] *= factor;
		return this;
	}
};
