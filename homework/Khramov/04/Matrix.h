class Arr_int {
private:
	int *arr_int;
	int M;
public:
	Arr_int() {
		M = 0;
		arr_int = nullptr;
	}
	Arr_int(int m) : M(m) {
		this->arr_int = new int[m];
	}
	int& operator[](int i) {
		if (i >= this->M || i<0)
		{
			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Arr_int range. max index = " + std::to_string(this->M));
		}
		return arr_int[i];
	}
	Arr_int(const Arr_int& other) {
		this->M = other.M;
		int *r = new int[other.M];
		for (int i = 0; i < other.M; i++) {
			r[i] = other.arr_int[i];
		}
		this->arr_int = r;
	}

	Arr_int& operator=(const Arr_int& other) {
		if (this != &other) {
			int *tmp = new int[other.M];
			for (int i = 0; i < other.M; i++) {
				tmp[i] = other.arr_int[i];
			}
			delete[] this->arr_int;
			this->arr_int = tmp;
			this->M = other.M;
		}
		return *this;
	}
	~Arr_int() {
		delete[] arr_int;
	}
};
class Matrix {
private:
	Arr_int * matrix;
	int cols;
	int rows;
public:
	Matrix(int co, int ro) : cols(co), rows(ro) {
		matrix = new Arr_int[co];
		for (int i = 0; i < co; i++) {
			matrix[i] = Arr_int(ro);
		}
	}

	int getColumns() {
		return this->cols;
	}
	int getRows() {
		return this->rows;
	}

	Arr_int& operator[](int i) {
		if (i >= this->cols || i<0)
		{

			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Col range. max index = " + std::to_string(this->cols));
		}
		return matrix[i];

	}
	Arr_int& operator[](int i) const{
		if (i >= this->cols || i<0)	{
			throw std::out_of_range(std::to_string(i) + " is " +
				"out of Col range. max index = " + std::to_string(this->cols));
		}
		return matrix[i];
	}

	Matrix& operator*=(int num) {
		for (int i = 0; i < this->cols; i++) {
			for (int j = 0; j < this->rows; j++) {
				matrix[i][j] *= num;
			}
		}
		return *this;
	}
	bool operator==(const Matrix& other) {
		if (this->cols != other.cols || this->rows != other.rows)
			return false;
		for (int i = 0; i < this->cols; i++) {
			for (int j = 0; j < this->rows; j++) {
				if ((*this)[i][j] != other[i][j])
					return false;
			}
		}
		return true;
	}

	bool operator!=(Matrix& other) {
		return !((*this) == other);
	}
	~Matrix() {
		delete[] matrix;
	}
};