#pragma once

#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstring>

class BigIntDec {

public:
	BigIntDec(int size): size_(size) {
		data_ = new int[size_]();
	}

	BigIntDec& operator*=(const int value) {
		int mod = 0;

		for (int i = 0; i < size_ - 1; i++) {
			int mult = data_[i] * value + mod;

			mod = mult / 10;

			data_[i] = mult % 10;
		}
	}

	BigIntDec& operator+=(const int value) {
		int mod = value;

		for (int i = 0; i < size_ - 1; i++) {
			int mult = data_[i] + mod;

			mod = mult / 10;

			data_[i] = mult % 10;

			if (mod == 0) {
				break;
			}
		}
	}

	friend std::ostream& operator<<(std::ostream & out, const BigIntDec & x) {
		for (int i = x.left_ind(); i >= 0; i--) {
			out << x.data_[i];
		}

		return out;
	}

	~BigIntDec() {
		delete[] data_;
	}

private:
	// позиция старшего ненулевого бита
	int left_ind() const {
		int ind = 0;

		for (int i = size_ - 1; i >= 0; i--) {
			if (data_[i]) {
				ind = i;
				break;
			}
		}

		return ind;
	}

	int size_;
	int* data_;
};


class BigInt {

public:
	BigInt(int64_t value = 0) {
		sign_ = value < 0;
		value = std::abs(value);

		size_ = (value) ? ceil(log2(value)) : 1;
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

	bool operator>(const BigInt& other) const {
		if (positive() && other.negative()) {
			return true;
		}

		if (negative() && other.positive()) {
			return false;
		}

		if (negative() && other.negative()) {
			return (-other) > (-(*this));
		}

		size_t min_size = std::min(size(), other.size());

		for (int i = size() - 1; i >= min_size; i--) {
			if (at(i)) {
				return true;
			}
		}

		for (int i = other.size() - 1; i >= min_size; i--) {
			if (other.at(i)) {
				return false;
			}
		}

		for (int i = min_size - 1; i >= 0 ; i--) {
			if (at(i) > other.at(i)) {
				return true;
			} else if (at(i) < other.at(i)) {
				return false;
			}
		}

		return false;
	}

	bool operator>=(const BigInt& other) const {
		return operator>(other) || operator == (other);
	}

	bool operator<(const BigInt& other) const {
		return !operator>=(other);
	}

	bool operator<=(const BigInt& other) const {
		return operator<(other) || operator==(other);
	}

	bool operator!=(const BigInt& other) const {
		return !operator==(other);
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
		for (size_t i = pos; i < size_; i++) {
			data_[i - pos] = data_[i];
		}
		for (size_t i = size_ - 1; i > size_ - pos; i++) {
			data_[i] = 0;
		}

		return *this;
	}

	void clear() {
		if (size_) {
			delete[] data_;

			alloc();
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

		int a_1 = a_tmp.left_ind();
		int b_1 = b_tmp.left_ind();

		a_tmp.resize(a_tmp.size_ * 2);
		BigInt c(a_tmp);
		c.clear();

		for (size_t i = 0; i <= b_1; i++) {
			if (b_tmp.at(i)) {
				c = c + a_tmp;
			}

			a_tmp <<= 1;
		}

		c.sign_ = sign_ xor other.sign_;

		return c;
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

		int a_1 = a_tmp.left_ind();
		int b_1 = b_tmp.left_ind();

		int b_lshift = a_1 - b_1;

		if (b_lshift) {
			b_tmp <<= a_1 - b_1;
		}

		while (true) {
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

	friend std::ostream& operator<<(std::ostream & out, const BigInt & x) {
		if (x.size_ == 0) {
			return out;
		}

		bool sign = x.at(x.size_ - 1) == 1;

		if (x.sign_ && !x.is_zero()) {
			out << "-";
		}

		BigIntDec b(x.left_ind() + 2);

		int base = 2;

		b += x.data_[x.left_ind()];

		for (int i = x.left_ind() - 1; i >= 0; i--) {
			b *= base;
			b += x.data_[i];
		}

		return out << b;
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
	static const int BLOCK_SIZE = 8;

	void alloc() {
		data_ = new bool[size_]();
	}

	void resize(size_t new_size) {
		if (new_size == size_) {
			return;
		}

		bool *new_data_ = new bool[new_size]();

		std::copy(data_, data_ + std::min(size_, new_size), new_data_);

		delete[] data_;

		data_ = new_data_;
		size_ = new_size;
	}

	size_t size() const {
		return size_;
	}

	void bit_flip(const size_t pos) {
		data_[pos] = !data_[pos];
	}

	// позиция старшего ненулевого бита
	int left_ind() const {
		int ind = 0;

		for (int i = size_ - 1; i >= 0; i--) {
			if (at(i)) {
				ind = i;
				break;
			}
		}

		return ind;
	}

	bool at(size_t index) const {
		return data_[index];
	}

	size_t size_;
	bool sign_;

	bool* data_;
};
