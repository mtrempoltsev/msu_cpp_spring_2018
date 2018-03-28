#include <iostream>


class Matrix
{
public:
	struct Proxy {
		size_t len;
		int* row;
		Proxy(int row[], size_t len) {
			this->len = len;
			this->row = row;
		}
		int& operator[](size_t i) const{
			if (i >= len)
				throw std::out_of_range("index out of range");
			return row[i];
		}
	};
	Matrix(size_t r, size_t c): rowCount(r), columnCount(c) {
		matrix = new int*[rowCount];
		for (size_t i = 0; i < rowCount; i++) {
			matrix[i] = new int[columnCount];
			for (size_t j = 0; j < columnCount; j++)
				matrix[i][j] = 0;
		}
	}
	~Matrix(){
		for (size_t i = 0; i < rowCount; i++)
			delete[] matrix[i];
		delete[] matrix;
	}
	size_t getRows() const{
		return rowCount;
	}
	size_t getColumns() const{
		return columnCount;
	}
	Proxy operator[](size_t i) const{
		if (i >= rowCount)
			throw std::out_of_range("index out of range");
		return Proxy(matrix[i], columnCount);
	}
	Matrix operator*=(int number) {
		for (size_t i = 0; i < rowCount; i++) {
			for (size_t j = 0; j < columnCount; j++) {
				matrix[i][j] = matrix[i][j] * number;
			}
		}
		return *this;
	}
	bool operator==(Matrix other) const{
		if (other.rowCount != rowCount || other.columnCount != columnCount)
			return 0;
		for (size_t i = 0; i < rowCount; i++) {
			for (size_t j = 0; j < columnCount; j++) {
				if (matrix[i][j] != other[i][j])
					return 0;
			}
		}
		return 1;
	}
	bool operator!=(Matrix other) const{
		return !(*this == other);
	}

private:
	
	int** matrix;
	size_t rowCount;
	size_t columnCount;
};
