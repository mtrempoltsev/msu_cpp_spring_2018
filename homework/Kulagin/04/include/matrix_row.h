#pragma once

#include <vector>

#include "Assert.h"


class MatrixRow {

public:
	// BEGIN---------------------------------------------- CONSTRUCTOR ------------------------------------------------
	MatrixRow(int ncols): ncols_(ncols) {
		Assert(ncols_ > 0, "cannot initialize matrix_row with " + to_string(ncols_) + " columns", __FILE__, __LINE__);

		data.resize(ncols_);
	}
	// END------------------------------------------------ CONSTRUCTOR ------------------------------------------------

	// BEGIN---------------------------------------------- OPERATORS --------------------------------------------------
	double& operator[](const int ncol);

	const double& operator[](const int ncol) const;
	// END------------------------------------------------ OPERATORS --------------------------------------------------


	// BEGIN---------------------------------------------- DESTRUCTOR -------------------------------------------------
	~MatrixRow() {}
	// END------------------------------------------------ DESTRUCTOR -------------------------------------------------

private:
	vector<double> data;

	int ncols_;
};
