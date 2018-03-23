#include <new>

class proxy
{
	int* proxyArray;
	size_t size;
public:
	proxy() : size(0)
	{
		proxyArray = NULL;
	}

	proxy(size_t a) : size(a)
	{
		proxyArray = new int[a];
	}

	~proxy()
	{
		delete[] proxyArray;
	}

	int& operator[](size_t a)
	{
		if (a >= size)
			throw std::out_of_range("");
		return proxyArray[a];
	}

	const int& operator[](size_t a) const
	{
		if (a >= size)
			throw std::out_of_range("");
		return proxyArray[a];
	}
};

class Matrix
{
	size_t columns;
	size_t rows;
	proxy* matrix;
public:
	Matrix(size_t c, size_t r) : columns(c), rows(r)
	{
		matrix = static_cast<proxy*>(operator new[] (columns * sizeof(proxy(rows))));
		 for (size_t i = 0; i < columns; i++)
			 new (matrix + i) proxy(rows); //здесь память для объекта не выделяется, но инициализируется
	}

	~Matrix()
	{
		 for (size_t i = 0; i < columns; i++)
			 matrix[i].~proxy();
		 operator delete[] (matrix);
	}

	int getColumns() const
	{
		return columns;
	}

	int getRows() const
	{
		return rows;
	}

	proxy& operator[](size_t a)
	{
		if (a >= columns)
			throw std::out_of_range("");
		return matrix[a];
	}

	const proxy& operator[](size_t a) const
	{
		if (a >= columns)
			throw std::out_of_range("");
		return matrix[a];
	}

	Matrix& operator*=(int n)
	{
		for (size_t i = 0; i < columns; i++)
			for (size_t j = 0; j < rows; j++)
				(*this)[i][j] *= n;
		return *this;
	}

	bool operator==(const Matrix& m)
	{
		if ((columns != m.columns) || (rows != m.rows))
			return false;
		for (size_t i = 0; i < columns; i++)
			for (size_t j = 0; j < rows; j++)
				if ((*this)[i][j] != m[i][j])
					return false;
		return true;
	}
	bool operator!=(const Matrix& m)
	{
		return (!((*this) == m));
	}
};
