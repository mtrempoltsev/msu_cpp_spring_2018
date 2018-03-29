#pragma once

#include <cmath>
#include <fstream>
#include <iomanip>
#include <cstring>

using namespace std;
#include <chrono>

// bool fair = true;
bool fair = false;

int CNT = 0;

std::chrono::high_resolution_clock::time_point t1;
std::chrono::high_resolution_clock::time_point t2;


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

int CNT_c = 0;

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
		try {
			// CNT++;
			if (CNT_c == 0) {
				CNT_c++;
				t1 = std::chrono::high_resolution_clock::now();
			}
			// cout << value << " " << size_ << endl;

			sign_ = value < 0;
			value = abs(value);

			size_ = (value) ? (LOG2(value) + 1) : 1;
			size_ = (size_ / 8 + 1) * 8;
			// cout << "size = " << size_ << endl;

			if (size_) {
				alloc();

				size_t i = 0;

				do {
					data_[i++] = value & 1;
					value >>= 1;
				} while (value);
			}
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
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
			// cout << "yes2" << endl;

			return (*this);
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	void resize(size_t new_size) {
		// try {
		try {
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

		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}

		// if (size_ < new_size) {
		// 	for (size_t i = size_; i < new_size; i++) {
		// 		data_[i] = 0;
		// 	}
		// }

		// } catch (const std::exception& e) {
		// 	cout << e.what() << endl;
		// 	exit(1);
		// }
	}

	bool operator==(const BigInt& b) const {
		try {
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
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	bool positive() const {
		return !sign_;
	}

	bool negative() const {
		return sign_;
	}

	bool operator>(const BigInt& b) const {
		try {
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
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
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
		// cout << size_ - 1 - pos << endl;
		for (int i = size_ - 1 - pos; i >= 0; i--) {
			data_[i + pos] = data_[i];
		}
		for (int i = pos - 1; i >= 0; i--) {
			data_[i] = 0;
		}
		// try {
		// 	resize(size_ + pos);

		// 	for (int i = size_ - 1; i >= pos; i--) {
		// 		std::swap(data_[i], data_[i - pos]);
		// 	}

		// 	return *this;
		// } catch (const std::exception& e) {
		// 	cout << e.what() << endl;
		// 	exit(1);
		// }
	}
	BigInt& operator>>=(int pos) {
		try {
			for (size_t i = pos; i < size_; i++) {
				data_[i - pos] = data_[i];
			}
			for (size_t i = size_ - 1; i > size_ - pos; i++) {
				data_[i] = 0;
			}
			// for (size_t i = 0; i < size_ - pos; i++) {
			// 	std::swap(data_[i + pos], data_[i]);
			// }

			// if (size_ - pos <= 0) {
			// 	cout << "err";
			// }

			// size_ = size_ - pos;

			return *this;
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	void clear() {
		try {
			if (size_) {
				delete[] data_;
				try {
					data_ = new bool[size_]();
				} catch (const std::exception& e) {
					cout << e.what() << endl;
					exit(1);
				}
			}
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt operator*(const BigInt& other) const {
		// if (!fair) {
		// 	return tol() * other.tol();
		// }

		BigInt a_tmp(*this);
		BigInt b_tmp(other);

		a_tmp.sign_ = false;
		b_tmp.sign_ = false;

		if (a_tmp.size_ > b_tmp.size_) {
			b_tmp.resize(a_tmp.size_);
		} else if (b_tmp.size_ > a_tmp.size_) {
			a_tmp.resize(b_tmp.size_);
		}

		// int a_1 = 0;
		// for (int i = a_tmp.size_ - 1; i >= 0; i--) {
		// 	if (a_tmp.at(i)) {
		// 		a_1 = i;
		// 		break;
		// 	}
		// }

		int b_1 = 0;
		for (int i = b_tmp.size_ - 1; i >= 0; i--) {
			if (b_tmp.at(i)) {
				b_1 = i;
				break;
			}
		}

		BigInt c(*this);
		c.clear();
		a_tmp.resize(b_1 + a_tmp.size_);

		// cout << "b1 = " << b_1 << endl;

		// cout << "b_tmp: "; b_tmp.bit_print();

		// cout << "a_tmp:";
		// a_tmp.bit_print();
		// cout << "b_tmp:";
		// b_tmp.bit_print();

		for (size_t i = 0; i <= b_1; i++) {
			if (b_tmp.at(i)) {
				c = c + a_tmp;
			}

			a_tmp <<= 1;
		}

		// cout << "c: "; c.bit_print();
		// cout << "420: "; BigInt(420).bit_print();

		c.sign_ = sign_ xor other.sign_;

		return c;
		// }
	}

	int64_t tol() const {
		try {
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
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt operator/(const BigInt& other) const {
		// if (!fair) {
		// 	return tol() / other.tol();
		// }

		BigInt a_tmp(*this);
		BigInt b_tmp(other);

		a_tmp.sign_ = false;
		b_tmp.sign_ = false;

		if (a_tmp < b_tmp) {
			BigInt c(0);
			c.sign_ = sign_ xor other.sign_;
			return c;
		}

		// BigInt b_tmp_l(b_tmp);

		BigInt c(a_tmp);
		// cout << "--------------------" << endl;
		// cout << "b_tmp =";
		// b_tmp.bit_print();

		if (b_tmp == 1) {
			c.sign_ = sign_ xor other.sign_;
			return c;
		}

		if (c.size_ > b_tmp.size_) {
			b_tmp.resize(c.size_);
		}
		else if (b_tmp.size_ > c.size_) {
			c.resize(b_tmp.size_);
		}

		// cout << "b_tmp_after =";
		// b_tmp.bit_print();

		int res = 0;

		// b_tmp.bit_print();

		// int l_shift_size;
		// for (int l_shift_size = b_tmp.size_; l_shift_size >= 0; l_shift_size--) {
		// 	// cout << l_shift_size << endl;
		// 	if (b_tmp.at(l_shift_size))
		// 		break;
		// 	// l_shift_size++;
		// }
		// l_shift_size = b_tmp.size_ - l_shift_size;
		// if (l_shift_size)
		// 	b_tmp <<= l_shift_size;
		int cnt = 0;
		// a_tmp.bit_print();
		// b_tmp.bit_print();
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
		// cout << "a1 = " << a_1 << endl;
		// cout << "b1 = " << b_1 << endl;
		// b_tmp <<= 2;
		// b_tmp.bit_print();

		int b_lshift = a_1 - b_1;

		// cout << "b_lshift = " << b_lshift << endl;
		if (b_lshift) {
			b_tmp <<= a_1 - b_1;
		}

		// if (c < b_tmp) {
		// 	return 0;
		// }
		// while (!b_tmp.at(b_tmp.size_ - 1 + cnt)) {
		// 	b_tmp <<= 1;
		// 	b_tmp.bit_print();

		// 	cnt++;
		// }
		// b_tmp.resize(b_tmp.size_ - cnt);

		// c.bit_print();
		// return c;
		while (1) {
			// cout << "-----------------------------" << endl;
			// while (b_tmp >= b_tmp_l && b_tmp.size_) {
			if (c < b_tmp) {
				if (b_lshift == 0) {
					// cout << "14" << endl;
					break;
				}

				if (b_lshift == 0) {
					break;
				}
				b_tmp >>= 1;
				b_lshift--;
				// cout << "bb: " << endl;
				// b_tmp.bit_print();
				res <<= 1;
				// cout << "res = " << res << endl;

				continue;
			}


			// cout << "c: " << endl;
			// c.bit_print();

			// cout << "b: " << endl;
			// b_tmp.bit_print();

			c = c - b_tmp;
			// cout << "c_after: " << endl;
			// c.bit_print();
			// b_tmp.bit_print();



			// res <<= 1;
			res ++;

			// cout << "res = " << res << endl;

			// if (c.is_zero()) {
			// 	if (b_lshift)
			// 		res <<= b_lshift;

			// 	break;
			// }

			// if (b_lshift == 0) {
			// 	cout << "bre" << endl;
			// 	break;
			// }

			// b_tmp >>= 1;
			// b_lshift--;

			// cout << "b_after: " << endl;
			// b_tmp.bit_print();

			// cout << "c >= b_tmp" << (c >= b_tmp) << endl;
			// cout << "blshi" << b_lshift << endl;
			// b_tmp.bit_print();

		}
		// while (b_lshift);

		// cout << "1" << endl;
		// b_tmp.bit_print();

		c = BigInt(res);
		c.sign_ = sign_ xor other.sign_;

		return c;

	}

	BigInt operator-() const {
		try {
			BigInt tmp(*this);

			tmp.sign_ = !sign_;

			return tmp;
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	bool is_zero() const {
		try {
			for (size_t i = 0; i < size_; i++) {
				if (at(i)) {
					return false;
				}
			}

			return true;
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt operator+(const BigInt& other) const {
		try {
			// if (!fair) {
			// 	return tol() + other.tol();
			// }

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

			// if (size_ < other.size_) {
			// 	return other + (*this);
			// }

			BigInt c(*this);

			// if (at(size_ - 1) || other.at(size_ - 1))
			c.resize(size_ + 8);

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
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	size_t size() const {
		return size_;
	}

	void bit_flip(const size_t pos) {
		try {
			data_[pos] = !data_[pos];
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	BigInt operator-(const BigInt & other) const {
		try {
			if (!fair) {
				return tol() - other.tol();
			}

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
		try {
			return data_[index];
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	friend std::ostream& operator<<(std::ostream & out, const BigInt & mid) {
		try {
			if (mid.size_ == 0) {
				return out;
			}

			size_t i = mid.size_ - 1;

			int64_t v = 0;

			bool sign = mid.at(mid.size_ - 1) == 1;

			if (mid.sign_ && !mid.is_zero()) {
				out << "-";
			}

			do {
				v <<= 1;
				v += mid.at(i);
			} while (i-- != 0);

			out << v;
			return out;
		} catch (const std::exception& e) {
			cout << e.what() << endl;
			exit(1);
		}
	}

	void bit_print() const {
		size_t i = size_ - 1;

		do {
			std::cout << at(i);
		} while (i-- != 0);

		std::cout << std::endl;
	}

	~BigInt() {
		// if (CNT++ == 212241) {
		// 	t2 = std::chrono::high_resolution_clock::now();
		// 	auto t = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
		// 	std::cout << "Time: " << t / 1e6 << std::endl;
		// }
		// if (data_) {
		// cout << "value = " << CNT++ << endl;
		delete[] data_;
		// }
	}

private:
	size_t size_;
	bool sign_;

	bool* data_;
};
