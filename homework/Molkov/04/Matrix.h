#pragma once

class Matrix {
private:
	int** arr = nullptr;
	int rows;
	int cols;

	class proxy	{
	private:
		int* mas = nullptr;
		int size;
	public:
		proxy(int* arr, int size):
			mas(arr), size(size) {}

		int& operator[](int id)	{
			if (id < this->size)
				return mas[id];
			else
				throw std::out_of_range("");
		}
		const int& operator[](int id) const {
			if (id < this->size)
				return mas[id];
			else
				throw std::out_of_range("");
		}
	};

public:


	proxy operator[](int id) {
		if (id < this->cols && id >= 0) {
			return proxy(arr[id], this->rows);
		}
		else {
			throw std::out_of_range("");
		}
	}
	
	const proxy operator[](int id) const {
		if (id < this->cols && id >= 0) {
			return proxy(arr[id], this->rows);
		}
		else {
			throw std::out_of_range("");
		}
	}

	Matrix(int _cols, int _rows) : cols(_cols), rows(_rows) {
		arr = new int*[cols];
		for (int i = 0; i < cols; i++)
			arr[i] = new int[rows];
	}

	Matrix& operator*=(const int& n) {
		for (int i = 0; i < this->cols; i++) {
			for (int j = 0; j < this->rows; j++)
				arr[i][j] *= n;
		}
		return *this;
	}

	bool operator==(const Matrix& other) const {
		if (this->cols != other.cols && this->rows != other.rows)
			return false;

		for (int i = 0; i < this->cols; i++) {
			for (int j = 0; j < this->rows; j++)
				if (arr[i][j] != other.arr[i][j])
					return false;
		}
		return true;
	}

	bool operator!=(const Matrix& other) const {
		return !(*this == other);
	}

	int getRows() {
		return this->rows;
	}
	int getColumns() {
		return this->cols;
	}

	~Matrix() {
		for (int i = 0; i < this->cols; i++)
			delete[] arr[i];
		delete[] arr;
	}
};