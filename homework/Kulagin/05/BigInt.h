#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;

int LOG2(int64_t x) {
	int cnt = 0;

	do {
		x >>= 1;
		cnt++;
	} while (x);

	return cnt - 1;
}

const int BLOCK_SIZE = 8;

class BigInt {

public:
	void alloc() {
		try {
			data_ = new bool[size_]();
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt(int64_t value = 0) {
		sign_ = value < 0;
		value = abs(value);

		size_ = (value) ? (LOG2(value) + 1) : 1;
		size_ = (size_ / BLOCK_SIZE + 1) * BLOCK_SIZE;

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
		try {
			size_ = value.size_;
			sign_ = value.sign_;

			// cout << "yes2" << endl;

			alloc();

			memcpy(data_, value.data_, size_);
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt& operator=(const BigInt& value) {
		try {
			if (size_)
				delete[] data_;

			// cout << "yes3" << endl;

			size_ = value.size();

			if (size_) {
				alloc();
				sign_ = value.sign_;

				memcpy(data_, value.data_, size_);
			}

			return (*this);
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt& operator=(const int64_t value) {
		try {
			(*this) = BigInt(value);

			return (*this);
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	void resize(size_t new_size) {
		bool* NEWDATA = new bool[new_size]();

		// if (size_)
		memcpy(NEWDATA, data_, size_);
		// if (size_)
		// 	delete[] data_;

		// // data_ = (bool*)realloc(data_, new_size);
		size_ = new_size;
		// swap(new_data_, data_);

		if (size_) {
			delete[] data_;
		}

		data_ = NEWDATA;
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
		for (int i = size_ - 1 - pos; i >= 0; i--) {
			data_[i + pos] = data_[i];
		}
		for (int i = pos - 1; i >= 0; i--) {
			data_[i] = 0;
		}
	}
	BigInt& operator>>=(int pos) {
		try {
			for (size_t i = pos; i < size_; i++) {
				data_[i - pos] = data_[i];
			}
			for (size_t i = size_ - 1; i > size_ - pos; i++) {
				data_[i] = 0;
			}

			return *this;
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
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
		BigInt b_tmp(other);

		a_tmp.sign_ = false;
		b_tmp.sign_ = false;

		if (a_tmp.size_ > b_tmp.size_) {
			b_tmp.resize(a_tmp.size_);
		} else if (b_tmp.size_ > a_tmp.size_) {
			a_tmp.resize(b_tmp.size_);
		}

		int a_1 = 0;
		for (int i = a_tmp.size_ - 1; i >= 0; i--) {
			if (a_tmp.at(i)) {
				a_1 = i;
				break;
			}
		}

		int b_1 = 0;
		for (int i = b_tmp.size_ - 1; i >= 0; i--) {
			if (b_tmp.at(i)) {
				b_1 = i;
				break;
			}
		}

		a_tmp.resize(a_tmp.size_ * 2);
		BigInt c(a_tmp);
		c.clear();

		// if (b_1 > a_1) {
		// 	// if (b_tmp.size_ - b_1)
		// 	// a_tmp.resize(a_tmp.size_ + (b_tmp.size_ - b_1) + 1);

		// 	// cout << a_tmp.size() << endl;
		// 	a_tmp.resize(b_1 - a_1 + 1 + a_tmp.size_);
		// 	// a_tmp.resize(b_1 - a_1 + a_tmp.size_);
		// }
		// else if (a_1 > b_1) {
		// 	a_tmp.resize(a_1 - b_1 + 1 + a_tmp.size_);
		// }

		for (size_t i = 0; i <= b_1; i++) {
			if (b_tmp.at(i)) {
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

		BigInt c(a_tmp);

		if (b_tmp == 1) {
			c.sign_ = sign_ xor other.sign_;
			return c;
		}

		if (c.size_ > b_tmp.size_) {
			b_tmp.resize(c.size_);
		} else if (b_tmp.size_ > c.size_) {
			c.resize(b_tmp.size_);
		}

		int res = 0;

		int cnt = 0;
		int a_1 = 0;
		for (int i = a_tmp.size_ - 1; i >= 0; i--) {
			if (a_tmp.at(i)) {
				a_1 = i;
				break;
			}
		}

		int b_1 = 0;
		for (int i = b_tmp.size_ - 1; i >= 0; i--) {
			if (b_tmp.at(i)) {
				b_1 = i;
				break;
			}
		}

		int b_lshift = a_1 - b_1;

		if (b_lshift) {
			b_tmp <<= a_1 - b_1;
		}

		while (1) {
			if (c < b_tmp) {
				if (b_lshift == 0) {
					break;
				}

				b_tmp >>= 1;
				b_lshift--;

				res <<= 1;

				continue;
			}

			c = c - b_tmp;

			res ++;
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

		BigInt c(*this);

		c.resize(size_ + BLOCK_SIZE);

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
		try {
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
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}

	}

	bool at(size_t index) const {
		return data_[index];
	}

	friend std::ostream& operator<<(std::ostream & out, const BigInt & mid) {
		if (mid.size_ == 0) {
			return out;
		}

		size_t i = mid.size_ - 1;

		long double v = 0;

		bool sign = mid.at(mid.size_ - 1) == 1;

		if (mid.sign_ && !mid.is_zero()) {
			out << "-";
		}

		string s;

		do {
			v *= 2;
			v += mid.at(i);
			s += mid.at(i) ? '1' : '0';
		} while (i-- != 0);


		out << fixed << setprecision(0) << v;

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
		delete[] data_;
	}

private:
	size_t size_;
	bool sign_;

	bool* data_;
};
