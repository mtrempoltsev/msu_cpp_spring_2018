#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;
#include <chrono>

int LOG2(int64_t x) {
	try {
		int cnt = 0;

		do {
			x >>= 1;
			cnt++;
		} while (x);

		return cnt - 1;
	} catch (const std::exception& e) {
		cout << e.what() << endl;
		exit(1);
	}
}

class BigInt {

public:
	void alloc() {
		try {
			data_ = new bool[size_];
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt(int64_t value = 0) {
		sign_ = value < 0;
		value = abs(value);

		size_ = (value) ? (LOG2(value) + 1) : 1;

		if (size_) {
			alloc();

			size_t i = 0;

			do {
				data_[i++] = value & 1;
				value >>= 1;
			} while (value);
		}
	}

	BigInt(const BigInt& value) {
		size_ = value.size_;
		sign_ = value.sign_;

		alloc();

		memcpy(data_, value.data_, size_);
	}

	BigInt& operator=(const BigInt& value) {
		if (size_)
			delete[] data_;

		size_ = value.size();

		if (size_) {
			alloc();
			sign_ = value.sign_;

			memcpy(data_, value.data_, size_);
		}

		return (*this);
	}

	BigInt& operator=(const int64_t value) {
		(*this) = BigInt(value);

		return (*this);
	}

	void resize(size_t new_size) {
		try {
			data_ = (bool*)realloc(data_, new_size);
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}

		if (size_ < new_size) {
			for (size_t i = size_; i < new_size; i++) {
				data_[i] = 0;
			}
		}

		size_ = new_size;
	}

	bool operator==(const BigInt& b) const {
		if (sign_ != b.sign_) {
			return (is_zero() && b.is_zero());
		}

		size_t min_size = std::min(size(), b.size());

		if (size() - 1 >= min_size)
			for (size_t i = size() - 1; i >= min_size; i--) {
				if (at(i)) {
					return false;
				}
			}

		if (b.size() - 1 >= min_size)
			for (size_t i = b.size() - 1; i >= min_size; i--) {
				if (b.at(i)) {
					return false;
				}
			}

		for (ssize_t i = min_size - 1; i >= 0 ; i--) {
			if (at(i) != b.at(i)) {
				return false;
			}
		}

		return true;
	}

	bool positive() const {
		return !sign_;
	}

	bool negative() const {
		return sign_;
	}

	bool operator>(const BigInt& b) const {
		if (positive() && b.negative()) {
			return true;
		}

		if (negative() && b.positive()) {
			return false;
		}

		if (negative() && b.negative()) {
			return (-b) > (-(*this));
		}

		size_t min_size = std::min(size(), b.size());

		for (int i = size() - 1; i >= min_size; i--) {
			if (at(i)) {
				return true;
			}
		}

		for (int i = b.size() - 1; i >= min_size; i--) {
			if (b.at(i)) {
				return false;
			}
		}

		for (int i = min_size - 1; i >= 0 ; i--) {
			if (at(i) > b.at(i)) {
				return true;
			} else if (at(i) < b.at(i)) {
				return false;
			}
		}

		return false;
	}

	bool operator>=(const BigInt& b) const {
		return operator>(b) || operator == (b);
	}

	bool operator<(const BigInt& b) const {
		return !operator>=(b);
	}

	bool operator<=(const BigInt& b) const {
		return operator<(b) || operator==(b);
	}

	bool operator!=(const BigInt& b) const {
		return !operator==(b);
	}

	BigInt& operator <<= (int pos) {
		resize(size_ + pos);

		for (int i = size_ - 1; i >= pos; i--) {
			std::swap(data_[i], data_[i - pos]);
		}

		return *this;
	}
	BigInt& operator>>=(int pos) {
		for (size_t i = 0; i < size_ - pos; i++) {
			std::swap(data_[i + pos], data_[i]);
		}

		if (size_ - pos <= 0) {
			cout << "err";
		}

		size_ = size_ - pos;

		return *this;
	}

	void clear() {
		if (size_) {
			delete[] data_;
			try {
				data_ = new bool[size_]();
			} catch (const std::exception& e) {
				cout << e.what() << endl;
				exit(1);
			}
		}
	}

	BigInt operator*(const BigInt& other) const {
		BigInt a_tmp(*this);
		BigInt c(*this);

		c.clear();

		for (size_t i = 0; i < other.size_; i++) {
			if (other.at(i)) {
				c = c + a_tmp;
			}

			a_tmp <<= 1;
		}

		c.sign_ = sign_ xor other.sign_;

		return c;
	}

	int64_t tol() const {
		size_t i = size_ - 1;

		int64_t v = 0;

		bool sign = at(size_ - 1) == 1;

		do {
			v <<= 1;
			v += at(i);
		} while (i-- != 0);

		if (sign_ && !is_zero()) {
			v *= -1;
		}

		return v;
	}

	BigInt operator/(const BigInt& other) const {
		BigInt a_tmp(*this);
		BigInt b_tmp(other);

		a_tmp.sign_ = false;
		b_tmp.sign_ = false;

		if (a_tmp < b_tmp) {
			BigInt c(0);
			c.sign_ = sign_ xor other.sign_;
			return c;
		}

		BigInt b_tmp_l(b_tmp);

		BigInt c(a_tmp);

		int res = 0;

		b_tmp <<= (a_tmp.size_ - other.size_);

		while (b_tmp >= b_tmp_l && b_tmp.size_) {
			if (c < b_tmp) {
				b_tmp >>= 1;

				res <<= 1;

				continue;
			}

			c = c - b_tmp;

			res <<= 1;
			res ++;

			if (c.is_zero()) {
				for (int t = 0; t < b_tmp.size() - other.size(); t++) {
					res <<= 1;
				}

				break;
			}

			b_tmp >>= 1;
		}

		c = BigInt(res);
		c.sign_ = sign_ xor other.sign_;

		return c;
	}

	BigInt operator-() const {
		BigInt tmp(*this);

		tmp.sign_ = !sign_;

		return tmp;
	}

	bool is_zero() const {
		for (size_t i = 0; i < size_; i++) {
			if (at(i)) {
				return false;
			}
		}

		return true;
	}

	BigInt operator+(const BigInt& other) const {
		// A < 0 | B < 0
		if (negative() && other.negative()) {
			return -(-(*this) + -other);
		}

		// A < 0 | B > 0
		if (negative() && other.positive()) {
			return other - (-(*this));
		}

		// A > 0 | B < 0
		if (positive() && other.negative()) {
			return (*this) - (-other);
		}

		if (size_ < other.size_) {
			return other + (*this);
		}

		BigInt c = (*this);

		c.resize(size_ + 2);
		// c.bit_print();
		bool bubble = false;

		for (size_t i = 0; i < other.size(); i++) {
			int sum = (c.at(i) + other.at(i) + bubble);
			c.data_[i] = sum & 1;
			bubble = sum >> 1;
		}

		for (size_t i = other.size(); i < c.size() - 1; i++) {
			int sum = (c.at(i) + bubble);
			c.data_[i] = sum & 1;
			bubble = sum >> 1;
		}

		c.sign_ = sign_ xor other.sign_;

		return c;
	}

	size_t size() const {
		return size_;
	}

	void bit_flip(const size_t pos) {
		data_[pos] = !data_[pos];
	}

	BigInt operator-(const BigInt & other) const {
		if (negative() && other.negative()) {
			return ((*this) + (-other));
		}

		if (negative() && other.positive()) {
			return -(-(*this) + other);
		}

		if (positive() && other.negative()) {
			return (*this) + (-other);
		}

		if (positive() && other.positive()) {
			if (*this < other) {
				return -(other - (*this));
			}
		}

		BigInt c(*this);

		for (size_t i = 0; i < other.size(); i++) {
			bool bubble = !c.at(i) && other.at(i);

			if (bubble) {
				for (size_t j = i + 1; j < c.size_; j++) {
					if (c.at(j)) {
						c.bit_flip(j);
						break;
					} else {
						c.bit_flip(j);
					}
				}
			}

			c.data_[i] -= other.at(i);
		}

		return c;
	}

	bool at(size_t index) const {
		return data_[index];
	}

	friend std::ostream& operator<<(std::ostream & out, const BigInt & big_int) {
		if (big_int.size_ == 0) {
			return out;
		}

		size_t i = big_int.size_ - 1;

		int64_t v = 0;

		bool sign = big_int.at(big_int.size_ - 1) == 1;

		if (big_int.sign_ && !big_int.is_zero()) {
			out << "-";
		}

		do {
			v <<= 1;
			v += big_int.at(i);
		} while (i-- != 0);

		out << v;
		return out;
	}

	void bit_print() const {
		size_t i = size_ - 1;

		do {
			std::cout << at(i);
		} while (i-- != 0);

		std::cout << std::endl;
	}

	~BigInt() {
		// if (data_) {
		delete[] data_;
		// }
	}

private:
	size_t size_;
	bool sign_;

	bool* data_;
};