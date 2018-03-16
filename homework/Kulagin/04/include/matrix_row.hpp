#ifndef MATRIX_ROW_HPP
#define MATRIX_ROW_HPP

#include <vector>

using namespace std;


class MatrixRow {

public:
	// CONSTRUCTOR BEGINS
	MatrixRow(int _ncols): ncols(_ncols) {
		if (ncols <= 0) {
			cout << "Error: cannot initialize matrix_row with " << ncols << " columns" << endl;

			exit(1);
		}

		data.resize(ncols);
	}
	// CONSTRUCTOR ENDS

	// OPERATORS BEGINS
	double& operator[](const int _ncol);

	const double& operator[](const int _ncol) const;
	// OPERATORS ENDS

	// DESTRUCTOR BEGINS
	~MatrixRow() {
		data.clear();
	};
	// DESTRUCTOR ENDS

private:
	vector<double> data;

	int ncols;
};

#endif
