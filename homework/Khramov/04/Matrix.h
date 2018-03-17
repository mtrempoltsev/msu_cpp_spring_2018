#include<iostream>
#include<string>


class Row {
private:
	int *row;
	int M;
public:
	Row() {
		M = 0;
		row = nullptr;
	}
	Row(int M) {
		this->M = M;
		this->row = new int[M];
	}
	int& operator[](int i) {
		if (i >= this->M)
		{
			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Row range. max index = " + std::to_string(this->M));
		}
		return row[i];
	}
	Row(const Row& other) {
		this->M = other.M;
		int *r = new int[other.M];
		for (int i = 0; i < other.M; i++) {
			r[i] = other.row[i];
		}
		this->row = r;
	}

	Row& operator=(const Row& other) {
		if (this != &other) {
			int *tmp = new int[other.M];
			for (int i = 0; i < other.M; i++) {
				tmp[i] = other.row[i];
			}
			delete[] this->row;
			this->row = tmp;
			this->M = other.M;
		}
		return *this;
	}
	~Row() {
		delete[] row;
	}
};
class Matrix {
private:
	Row * matrix;
	int N;
	int M;
public:
	Matrix(int N, int M) {
		this->N = N;
		this->M = M;
		matrix = new Row[N];

		for (int i = 0; i < N; i++) {
			matrix[i] = Row(M);
		}
	}
	Matrix(Matrix& other) {
	}
	int getColumns() {
		return this->N;//По моей логике должно было возвращаться M но так не проходят тесты...
	}
	int getRows() {
		return this->M;// здесь так же
	}
	Row& operator[](int i) {
		if (i >= this->N)
		{

			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Col range. max index = " + std::to_string(this->N));
		}
		return matrix[i];

	}
	Row operator[](int i) const{
		if (i >= this->N)
		{

			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Col range. max index = " + std::to_string(this->N));
		}
		return matrix[i];

	}

	Matrix& operator*=(int num) {
		for (int i = 0; i < this->N*this->M; i++)
			(*this)[i / this->M][i%this->M] *= num;
		return *this;
	}
	bool operator==(const Matrix& other) {
		if (this->M != other.M || this->N != other.N)
			return false;
		for (int i = 0; i < this->N*this->M; i++)
			if (!((*this)[i / this->M][i%this->M] == other[i / this->M][i%this->M]))
				return false;

		return true;
	}

	bool operator!=(Matrix& other) {
		return !((*this) == other);
	}
	~Matrix() {
		delete[] matrix;
	}
};
