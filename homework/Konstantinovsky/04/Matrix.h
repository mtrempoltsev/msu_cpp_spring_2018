#include <iostream>
#include <stdio.h>

class Matrix {
private:
	int **m;
	int num_rows, num_cols;

	class Column {
		int *column;
		int len;
	public:
		Column(int *column, int len) {
			this->len = len;
			this->column = column;
		};

		int &operator[](int i) const {
			if (i < len && i >= 0) {
				return column[i];
			}
			else {
				throw std::out_of_range("");
			}
		}
	};

public:
	Matrix(int num_cols, int num_rows) {
		this->num_cols = num_cols;
		this->num_rows = num_rows;

		m = new int*[num_cols];

		for (int i = 0; i < num_cols; i++) {
			m[i] = new int[num_rows];
		}
	};

	~Matrix() {
		for (int i = 0; i < num_cols; i++) {
			delete[] m[i];
		}
		delete[] m;
	}

	int getRows() const {
		return num_rows;
	}

	int getColumns() const {
		return num_cols;
	}

	const Column operator[](int i) const {
		if (i < num_cols && i >=0) {
			Column arr(m[i], num_rows);
			return arr;
		}
		else {
			throw std::out_of_range("");
		}
	}


	int& getNumber(int i, int j) const {
		return m[i][j];
	}

	bool operator == (const Matrix &m2) const {
		if (num_rows != m2.getRows() || num_cols != m2.getColumns()) {
			return false;
		} else {
			for (int i = 0; i < num_rows; i++) {
				for (int j = 0; j < num_cols; j++) {
					if (m[i][j] != m2.m[i][j]) {
						return false;
					}
				}
			}
		}
		return true;
	}


	bool operator != (const Matrix &m2) const {
		if (num_rows != m2.getRows() || num_cols != m2.getColumns()) {
			return true;
		}
		else {
			for (int i = 0; i < num_rows; i++) {
				for (int j = 0; j < num_cols; j++) {
					if (m[i][j] != m2.m[i][j]) {
						return true;
					}
				}
			}
		}

		return false;
	}

	void operator *= (int a) {
		for (int i = 0; i < num_cols; i++) {
			for (int j = 0; j < num_rows; j++) {
				m[i][j] *= a;
			}
		}
	}
};
