#include <vector>
#include <cassert>
#include "matrix.h"

using std::size_t;
using std::vector;

Proxy::Proxy(size_t size_check) {
    if (size_check == 0) {
        assert(!"could not create a row with zero size_check");
    }
    vec.resize(size_check);
}

size_t Proxy::getsize() const {
    return vec.size();
}

double& Proxy::operator[] (size_t idx) {
    if (idx >= vec.size()) {
        assert(!"index out of range");
    }
    return vec[idx];
}

Proxy& Proxy::multconst(double c) {
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        *it *= c;
    }
    return *this;
}

Proxy& Proxy::multvect(const vector<double>& mul_vec) {
    if (vec.size() != mul_vec.size()) {
        assert(!"the lengths of the vectors are not identical");
    }
    auto it2 = mul_vec.cbegin();
    for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
        *it1 *= *it2;
    }
    return *this;
}

bool Proxy::operator== (const Proxy& row) const {
    if (vec.size() != row.vec.size()) {
        return false;
    }
    auto it2 = row.vec.cbegin();
    for (auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
        if (*it1 != *it2) {
            return false;
        }
    }
    return true;
}

Proxy::~Proxy() {}


Matrix::Matrix(size_t rows, size_t cols) {
	if(!rows || !cols) {
		assert(!"zero rows or columns");
	}
	vec.resize(rows, Proxy(cols));
}

Proxy& Matrix::operator[] (size_t idx) {
	if(idx >= vec.size()) {
		assert(!"index out of range");
	}
	return vec[idx];
}

size_t Matrix::getcols() const {
    return vec[0].getsize();
}

size_t Matrix::getrows() const {
    return vec.size();
}

Matrix& Matrix::operator*= (double c) {
	for(auto it = vec.begin(); it != vec.end(); it++) {
		it->multconst(c);
	}
	return *this;
}

Matrix& Matrix::operator*= (const vector<double>& mul_vect) {
	for(auto it = vec.begin(); it != vec.end(); ++it) {
		it->multvect(mul_vect);
	}
	return *this;
}

bool Matrix::operator== (Matrix& matrix) {
	if(getrows() != matrix.getrows() || getcols() != matrix.getcols()) {
		return false;
	}
	auto it2 = matrix.vec.cbegin();
	for(auto it1 = vec.begin(); it1 != vec.end(); ++it1, ++it2) {
		if (!(*it1 == *it2)) {
			return false;
		}
	}
	return true;
}

bool Matrix::operator!= (Matrix & matrix) {
    return !(*this == matrix);
}

Matrix::~Matrix() {
}