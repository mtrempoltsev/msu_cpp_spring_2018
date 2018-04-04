// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
// PVS-settings
// PVS-settings end

#include<string>
#include<iostream>
#include<cstdlib>
#include<cstring>

typedef int64_t int64;
typedef uint64_t uint64;
typedef uint32_t uint;

const uint base = 0x80000000; // = 2^31 = 2147483648 = MAX_INT + 1
const uint basem1 = 0x7FFFFFFF; // = base - 1
const uint basestr = 1000000000; // для перевода из строки и в строку
const uint bsespow = 9; // = log(10, basestr)
const uint intsize = 4; // Goodbye UB if alloc > 2^29 digits and size_t is uint
const uint intshft = 2; // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
const size_t minblock = 16;

///<summary>
/// exceptions keywords
///</summary>
enum kekErr
{
	ok = 0,
	errarg = 1, // bad argument in base constructor
	erralc = 2, // bad allocation
	errbck = 4, // call back() on empty container
};

size_t min(size_t a, size_t b) { return (a < b) ? a : b; }
size_t max(size_t a, size_t b) { return (a > b) ? a : b; }

size_t getmaxdatasize(size_t size, size_t nmemb)
{
	if (nmemb == 0 || nmemb < size)
		nmemb = ((size == 0) ? minblock : size * 2);
	size_t al = nmemb << intshft;
	size_t max = al >> intshft;
	if (max != nmemb)
	{
		al = (nmemb = size + minblock) << intshft;
		max = al >> intshft;
	}
	if (max != nmemb)
	{
		al = (nmemb = size) << intshft;
		max = al >> intshft;
	}
	if (max != nmemb)
		throw errarg;
	return max;
}

///<summary>
///simple implementation of vector<unsigned int>
///</summary>
class kektor
{
private:

	mutable size_t size_; // current size of vector
	size_t max_; // number of allocated uints
	mutable size_t sht_; //shift in array, number of virtual empty cells
	uint * data_; // data array

public:

	//methods need:
	//back       +
	//pop_back   +
	//size       +
	//push_back  +
	//swap       +
	//insert ???
	//constructor from memory block (Karatsuba) ???

	///<summary>
	///base constructor
	///nmemb: number of uints allocated on create
	///</summary>
	kektor(size_t size = 0, uint * ptr = nullptr, size_t nmemb = 0) :
		   size_(size), sht_(0), data_(nullptr)
	{

		size_t al = (max_ = getmaxdatasize(size, nmemb)) << intshft;

		data_ = (ptr) ? (uint *)realloc(nullptr, al) :
			(uint *)calloc(max_, intsize);
		if (data_ == nullptr && max_ > size && size > 0)
		{
			al = (max_ = size) << intshft;
			data_ = (ptr) ? (uint *)realloc(nullptr, al) :
				(uint *)calloc(max_, intsize);
		}
		if (data_ == nullptr)
		{
			throw erralc;
			return;
		}
		if (ptr != nullptr)
		{
			std::copy(ptr, ptr + (al = (min(size, max_) << intshft)), data_);
			memset(data_, 0, (max_ << intshft) - al);
		}
	}

	///<summary>
	///copy constructor
	///</summary>
	kektor(const kektor & other) :
		size_(other.size_ + other.sht_), max_(max(other.max_, size_)), sht_(0)
	{
		data_ = (uint *)malloc(max_ * intsize);
		if (data_ == nullptr)
		{
			throw erralc;
		}
		else
		{
			memset(data_, 0, other.sht_ * intsize);
			std::copy(other.data_, other.data_ + other.size_ * intsize,
					  data_ + other.sht_ * intsize);
		}
	}

	///<summary>
	///move constructor
	///</summary>
	kektor(kektor && other) : size_(other.size_), max_(other.max_),
							  data_(other.data_), sht_(other.sht_)
	{
		other.data_ = nullptr;
		other.max_ = 0;
		other.size_ = 0;
		other.sht_ = 0;
	}

	///<summary>
	///copy operator =
	///</summary>
	kektor & operator = (const kektor & other)
	{
		if (this == &other)
			return *this;
		if (max_ >= other.size_ + other.sht_)
		{
			size_ = other.size_ + other.sht_;
			memset(data_, 0, other.sht_ * intsize);
			std::copy(other.data_, other.data_ + other.size_ * intsize,
					  data_ + other.sht_ * intsize);
		}
		else
		{
			size_ = other.size_ + other.sht_;
			max_ = max(other.max_, size_);
			free(data_);
			data_ = (uint *)realloc(nullptr, max_ * intsize);
			if (data_ == nullptr)
				throw erralc;
			else
			{
				memset(data_, 0, other.sht_ * intsize);
				std::copy(other.data_, other.data_ + other.size_ * intsize,
						  data_ + other.sht_ * intsize);
			}
		}
		return *this;
	}

	///<summary>
	///move operator =
	///</summary>
	kektor & operator = (kektor && other)
	{
		if (this == &other || this->data_ == other.data_)
			return *this;
		free(data_);
		max_ = other.max_;
		sht_ = other.sht_;
		size_ = other.size_;
		data_ = other.data_;
		other.data_ = nullptr;
		return *this;
	}

	///<summary>
	///destructor
	///</summary>
	~kektor() { free(data_); }

	//maybe will be useful
	const uint & operator [] (size_t pos) const
	{
		if (pos < sht_) return 0;
		return data_[pos - sht_];
	}

	uint & operator [] (size_t pos) { return data_[pos]; }

	///<summary>
	///return size of vector
	///</summary>
	size_t size() const { return size_; }

	///<summary>
	///if size > 0 return reference to the last element
	///</summary>
	uint & back()
	{
		if (size_ > 0)
			return data_[size_ - 1];
		throw errbck;
	}

	///<summary>
	///if size > 0 return const reference to the last element
	///</summary>
	const uint & back() const
	{
		if (size_ > 0)
			return data_[size_ - 1];
		throw errbck;
	}

	///<summary>
	///remove last element in vector
	///</summary>
	void pop_back() const
	{
		if (size_ > 0)
			--size_;
		else throw errbck;
	}

	///<summary>
	///add elem in the end of the vector
	///</summary>
	void push_back(uint elem)
	{
		if (size_ < max_)
		{
			data_[size_++] = elem;
			return;
		}

		size_t a;
		a = getmaxdatasize(max_, max_ * 2);
		if (a == max_) throw erralc;

		uint * tmp = (uint *)realloc(data_, a << intshft);
		if (tmp != nullptr)
		{
			data_[size_++] = elem;
			max_ = a;
			memset(data_ + size_ * intsize, 0,
				   (max_ - size_) * intsize);
			return;
		}
		if (max_ + minblock != a)
			tmp = (uint *)realloc(data_, max_ + minblock);
		if (tmp != nullptr)
		{
			data_[size_++] = elem;
			max_ += minblock;
			memset(data_ + size_ * intsize, 0,
				   (max_ - size_) * intsize);
			return;
		}
		throw erralc;
	}

	size_t getsht () const { return sht_; }

	size_t shift(size_t v) const { return sht_ = v; }

	void swap(kektor & other) // without std::swap (cause I can)
	{
		size_t tmp = max_;
		max_ = other.max_;
		other.max_ = tmp;
		tmp = sht_;
		sht_ = other.sht_;
		other.sht_ = tmp;
		tmp = size_;
		size_ = other.size_;
		other.size_ = tmp;
		uint * ptmp = data_;
		data_ = other.data_;
		other.data_ = ptmp;
	}

	void swap(kektor && other) // without std::swap (cause I can)
	{
		size_t tmp = max_;
		max_ = other.max_;
		other.max_ = tmp;
		tmp = sht_;
		sht_ = other.sht_;
		other.sht_ = tmp;
		tmp = size_;
		size_ = other.size_;
		other.size_ = tmp;
		uint * ptmp = data_;
		data_ = other.data_;
		other.data_ = ptmp;
	}

};

class BigInt
{
private:

	kektor kdata_; //me retard?

public:

	///<summary>
	///constructor from int
	///<para>num: int number</para>
	///</summary>
	BigInt(int num = 0)
	{
		kdata_.push_back(num); //what about 0x80000000 ?
		if (num == 0)
			kdata_.pop_back();
		if (num == 0x80000000)
		{
			kdata_[0] = 0;
			kdata_.push_back((uint)-1);
		}
	}

	BigInt(int64 num) : BigInt(std::to_string(num)) { }
	///<summary>
	///constructor with copy/fill with zeros
	///<para>size: size of mem needed</para>
	///<para>ptr: pointer to copy from, use nullptr to fill with zeros</para>
	///</summary>
	BigInt(size_t size, uint * ptr)
	{
		kdata_ = kektor(size, ptr);
	}

	///<summary>
	///copy constructor
	///</summary>
	BigInt(const BigInt & other) : kdata_(other.kdata_) {}

	///<summary>
	///move constructor
	///</summary>
	BigInt(BigInt && other) : kdata_(std::forward<kektor>(other.kdata_)) {}

	///<summary>
	///copy operator =
	///</summary>
	BigInt & operator = (const BigInt & other)
	{
		kdata_ = other.kdata_;
		return *this;
	}

	///<summary>
	///move operator =
	///</summary>
	BigInt & operator = (BigInt && other)
	{
		kdata_ = std::forward<kektor>(other.kdata_);
		return *this;
	}

	size_t size() const
	{
		while (kdata_.size() > 0 && kdata_.back() == 0)
			kdata_.pop_back();
		return (kdata_.size() > 0) ? kdata_.size() + kdata_.getsht() :
									 kdata_.shift(0);
	}

	uint isZero() const { return !size(); }

	void chsign()
	{
		size_t sz = size();
		for (size_t i = 0; i < sz; ++i)
			kdata_[i] = (uint)-((int)kdata_[i]);
	}

	void absinplace()
	{
		if (kdata_[size() - 1] >> 31)
			chsign();
	}

	BigInt abs () const
	{
		BigInt tmp(*this);
		tmp.absinplace();
		return tmp;
	}

	int divintinplace(int other)
	{
		if (kdata_.getsht() > 0)
		{
			kektor ktmp = kdata_;
			kdata_ = std::move(ktmp);
		}
		int carry = 0;
		size_t i = size();
		if (i == 0)
			return 0;
		do
		{
			int64 cur = ((int)kdata_[i - 1]) + carry * 1ll * base;
			kdata_[--i] = int(cur / other);
			carry = int(cur % other);
		} while (i > 0);
		size();
		return carry;
	}

	void divbig(const BigInt & other, BigInt * rdiv, BigInt * rmod) const
	{

		uint sgn1 = this->kdata_[this->size() - 1] >> 31,
			 sgn2 = other.kdata_[other.size() - 1] >> 31;
		BigInt dvd = this->abs();
		BigInt dvr = other.abs();
		BigInt div1 = 1;
		BigInt div2 = 2;

		sgn1 = sgn1 ^ sgn2;
		sgn2 = sgn1 ^ sgn2;

		if (dvd < dvr)
		{
			if (rdiv) rdiv->kdata_ = std::move(BigInt(0).kdata_);
			if (rmod) rmod->kdata_ = std::move(((sgn2) ? -dvd : dvd).kdata_);
			return;
		}

		if (dvd > dvr && dvd < dvr * 2)
		{
			if (rdiv) rdiv->kdata_ = std::move(((sgn1) ? -div1 : div1).kdata_);
			if (rmod) rmod->kdata_ =
				std::move(((sgn2) ? -(dvd - dvr) : (dvd - dvr)).kdata_);
			return;
		}

		div1 *= 4;

		while (div1 * dvr < dvd)
		{
			div1.kdata_.swap(div2.kdata_);
			div1 *= 4;
		}

		div1.kdata_.swap(div2.kdata_);

		BigInt m;
		while (div1 < div2)
		{
			m = (div1 + div2) / 2;
			if (m * dvr > dvd) div2 = m;
			else div1 = m + 1;
		}

		if (div1 * dvr > dvd) div1 -= 1;
		div2 = dvd - div1 * dvr;

		if (rdiv) rdiv->kdata_ = std::move(((sgn1) ? -div1 : div1).kdata_);
		if (rmod) rmod->kdata_ = std::move(((sgn2) ? -div2 : div2).kdata_);
	}

	BigInt mulnative(const BigInt other) const
	{
		size_t sz1 = this->size(), sz2 = other.size();
		BigInt res(0);
		BigInt t;
		const BigInt * his = this, * her = &other;
		const BigInt * tmp;
		if (sz2 > sz1)
		{
			tmp = his; his = her; her = tmp;
			std::swap(sz1, sz2);
		}
		for (size_t i = 0; i < sz2; i++)
		{
			t = *his * her->kdata_[i];
			t.kdata_.shift(i);
			res += t;
		}
		res.size();
		return res;
	}

	BigInt operator - () const
	{
		size();
		BigInt tmp(*this);
		tmp.chsign();
		return tmp;
	}

	BigInt operator + () const { size(); return *this; }

	BigInt & operator += (const BigInt & other)
	{
		if (kdata_.getsht() > 0)
		{
			kektor ktmp = kdata_;
			kdata_ = std::move(ktmp);
		}
		size_t sz1 = size(), sz2 = other.size(), sz = (sz1 > sz2) ? sz1 : sz2;
		if (!sz1)
		{
			kdata_ = other.kdata_;
			return *this;
		}
		if (!sz2)
			return *this;
		int carry = 0, sgn1 = this->kdata_[sz1 - 1] >> 31,
					   sgn2 = other.kdata_[sz2 - 1] >> 31;
		for (size_t i = 0; i < sz; ++i)
		{
			if (i >= sz1) kdata_.push_back(0);
			if (i < sz2) kdata_[i] += other.kdata_[i];
		}
		if ((sz = size()) == 0)
			return *this;
		int sgn = (sgn1 ^ sgn2) ? (kdata_[sz - 1] >> 31) : sgn1;
		int nsgn = sgn ^ sgn1 ^ sgn2;
		for (size_t i = 0; i < sz; ++i)
		{
			if (nsgn) kdata_[i] -= carry;
			else      kdata_[i] += carry;
			carry = kdata_[i] >> 31;
			if (kdata_[i] & basem1) carry ^= sgn;
			if (carry) kdata_[i] ^= base;
		}
		size();
		if (carry)
			kdata_.push_back((sgn) ? (uint)-1 : 1);
		return *this;
	}

	BigInt & operator *= (int other)
	{
		if (kdata_.getsht() > 0)
		{
			kektor ktmp = kdata_;
			kdata_ = std::move(ktmp);
		}
		size();
		int carry = 0;
		int64 cur;
		for (size_t i = 0; i < kdata_.size() || carry; ++i)
		{
			if (i == kdata_.size()) kdata_.push_back(0);
			cur = carry + ((int)kdata_[i]) * 1ll * other;
			kdata_[i] = int(cur % base);
			carry = int(cur / base);
		}
		size();
		return *this;
	}

	BigInt & operator *= (const BigInt & other)
	{
		BigInt tmp = mulnative(other);
		this->kdata_ = std::move(tmp.kdata_);
		return *this;
	}

	BigInt & operator -= (const BigInt & other)
	{
		if (kdata_.getsht() > 0)
		{
			kektor ktmp = kdata_;
			kdata_ = std::move(ktmp);
		}
		*this += -other;
		return *this;
	}

	BigInt & operator -= (BigInt && other)
	{
		if (kdata_.getsht() > 0)
		{
			kektor ktmp = kdata_;
			kdata_ = std::move(ktmp);
		}
		if (other.kdata_.getsht() > 0)
		{
			kektor ktmp = other.kdata_;
			other.kdata_ = std::move(ktmp);
		}
		other.chsign();
		*this += other;
		return *this;
	}

	BigInt & operator /= (const BigInt & other)
	{
		BigInt tmp;
		divbig(other, &tmp, nullptr);
		tmp.size();
		this->kdata_ = std::move(tmp.kdata_);
		return *this;
	}

	BigInt & operator %= (const BigInt & other)
	{
		BigInt tmp;
		divbig(other, nullptr, &tmp);
		tmp.size();
		this->kdata_ = std::move(tmp.kdata_);
		return *this;
	}

	BigInt & operator /= (int other)
	{
		divintinplace(other);
		return *this;
	}

	BigInt & operator %= (int other)
	{
		kdata_ = std::move(BigInt(divintinplace(other)).kdata_);
		return *this;
	}

	BigInt operator + (const BigInt & other) const //me am smart
	{
		BigInt tmp(*this);
		return tmp += other;
	}
	
	BigInt operator - (const BigInt & other) const
	{
		BigInt tmp(other);
		tmp.chsign();
		return tmp += *this;
	}

	BigInt operator * (const BigInt & other) const
	{
		return mulnative(other);
	}

	BigInt operator * (int other) const
	{
		BigInt tmp(*this);
		return tmp *= other;
	}

	BigInt operator / (const BigInt & other) const
	{
		BigInt tmp;
		divbig(other, &tmp, nullptr);
		tmp.size();
		return tmp;
	}

	BigInt operator % (const BigInt & other) const
	{
		BigInt tmp;
		divbig(other, nullptr, &tmp);
		tmp.size();
		return tmp;
	}

	BigInt operator / (int other) const
	{
		BigInt tmp(*this);
		return tmp /= other;
	}

	int operator % (int other) const
	{
		BigInt tmp(*this);
		return tmp.divintinplace(other);
	}

	bool operator < (const BigInt & other) const
	{
		size_t sz1 = size(), sz2 = other.size();
		if (sz1 == 0 && sz2 == 0)
			return false;
		if (sz1 == 0)
			return !(other.kdata_[sz2 - 1] >> 31);
		if (sz2 == 0)
			return this->kdata_[sz1 - 1] >> 31;
		uint sgn1 = this->kdata_[sz1 - 1] >> 31,
			sgn2 = other.kdata_[sz2 - 1] >> 31;
		if (sgn1 != sgn2)
			return sgn1;
		if (sz1 != sz2)
			return sgn1 ^ (sz1 < sz2);
		--sz1;
		while (sz1 > 0 && this->kdata_[sz1] == other.kdata_[sz1]) --sz1;
		return this->kdata_[sz1] != other.kdata_[sz1] &&
			   this->kdata_[sz1]  < other.kdata_[sz1];
	}

	bool operator > (const BigInt & other) const
	{
		size_t sz1 = size(), sz2 = other.size();
		if (sz1 == 0 && sz2 == 0)
			return false;
		if (sz1 == 0)
			return other.kdata_[sz2 - 1] >> 31;
		if (sz2 == 0)
			return !(this->kdata_[sz1 - 1] >> 31);
		uint sgn1 = this->kdata_[sz1 - 1] >> 31,
			sgn2 = other.kdata_[sz2 - 1] >> 31;
		if (sgn1 != sgn2)
			return sgn2;
		if (sz1 != sz2)
			return sgn1 ^ (sz1 > sz2);
		--sz1;
		while (sz1 > 0 && this->kdata_[sz1] == other.kdata_[sz1]) --sz1;
		return this->kdata_[sz1] != other.kdata_[sz1] &&
			   this->kdata_[sz1]  > other.kdata_[sz1];
	}

	bool operator == (const BigInt & other) const
	{
		size_t sz1 = size(), sz2 = other.size();
		if (sz1 != sz2)
			return false;
		if (sz1 == 0)
			return true;
		--sz1;
		while (sz1  > 0 && this->kdata_[sz1] == other.kdata_[sz1]) --sz1;
		return sz1 == 0 && this->kdata_[sz1] == other.kdata_[sz1];
	}

	bool operator >= (const BigInt & other) const { return !(*this  < other); }

	bool operator <= (const BigInt & other) const { return !(*this  > other); }

	bool operator != (const BigInt & other) const { return !(*this == other); }

	std::string ToString() const
	{
		BigInt temp(*this);
		if (temp.isZero()) return "0";
		bool sign = temp.kdata_[temp.size() - 1] >> 31;
		std::string res = "", c;
		while (!temp.isZero())
		{
			c = std::to_string(temp.divintinplace(basestr));
			if (sign) c = c.substr(1, c.length() - 1);
			res = c + res;
			if (c.length() < bsespow)
				for (int i = c.length(); i < bsespow; ++i) res = "0" + res;
		}
		while (res.length() > 1 && res[0] == '0')
			res = res.substr(1, res.length() - 1);
		if (sign) res = "-" + res;
		return res;
	}

	BigInt(std::string str)
	{
		BigInt res(0);
		int carry, sign = 0, a;
		size_t b;
		if (str[0] < '0' || str[0] > '9')
		{
			sign = str[0] == '-';
			str = str.substr(1, str.length() - 1);
		}
		b = str.length();
		if (b % 9) for (size_t i = 0; i < 9 - b % 9; ++i) str = "0" + str;
		for (size_t i = 0; i < str.length(); i += bsespow)
		{
			res *= basestr;
			a = atoi(str.substr(i, bsespow).c_str());
			if (sign) a = -a;
			if (res.isZero()) res.kdata_.push_back(0);
			res.kdata_[0] += (uint)a;
			carry = res.kdata_[0] >> 31;
			if (res.kdata_[0] & basem1) carry ^= sign;
			if (carry) res.kdata_[0] ^= base;
			if (res.size() > 1) res.kdata_[1] += (sign) ? -carry : carry;
			else res.kdata_.push_back((sign) ? -carry : carry);
			res.size();
		}
		kdata_ = std::move(res.kdata_);
	}
};

std::ostream & operator << (std::ostream & out, const BigInt & value)
{
	return out << value.ToString();
}


#include <iostream>
#include <limits>
#include <sstream>

//#include "bigint.h"

std::string toString(const BigInt& value)
{
	std::stringstream buf;
	buf << value;
	return buf.str();
}

void check(int64_t x, int64_t y)
{
	const BigInt bigX = x;
	const BigInt bigY = y;

	if (bigX + bigY != BigInt(x + y))
	{
		std::cout << x << " + " << y << " != " << x + y << " got " << bigX + bigY << '\n';
	}

	if (bigX - bigY != BigInt(x - y))
	{
		std::cout << x << " - " << y << " != " << x - y << " got " << bigX - bigY << '\n';
	}

	if (bigX * bigY != BigInt(x * y))
	{
		std::cout << x << " * " << y << " != " << x * y << " got " << bigX * bigY << '\n';
	}

	if (x != 0 && y != 0)
	{
		if (bigX / bigY != BigInt(x / y))
		{
			std::cout << x << " / " << y << " != " << x / y << " got " << bigX / bigY << '\n';
		}
	}
}

void doCheckEqual(const BigInt& actual, const char* expected, size_t line)
{
	const auto str = toString(actual);
	if (str != expected)
	{
		std::cout << "at line " << line << ": " << str << " != " << expected << '\n';
	}
}

#define checkEqual(x, y) do { doCheckEqual((x), (y), __LINE__); } while(0)
#define checkTrue(cond) do { if (!(cond)) std::cout << "at line " << __LINE__ << ": " << #cond << '\n'; } while(0)

int main()
{
	BigInt x = 3;
	checkEqual(x, "3");
	BigInt y = x;
	checkEqual(y, "3");
	BigInt z;
	checkEqual(z, "0");

	checkEqual(BigInt(-10), "-10");

	checkTrue(x == y);
	checkTrue(y == x);
	checkTrue(x != z);
	checkTrue(z != x);

	z = y;
	checkEqual(z, "3");

	x = 100;
	checkEqual(x, "100");

	checkTrue(!(x < x));
	checkTrue(x < 200);
	checkTrue(BigInt(50) < x);
	checkTrue(BigInt(-500) < x);
	checkTrue(BigInt(-500) < BigInt(-200));

	checkTrue(!(x > x));
	checkTrue(BigInt(200) > x);
	checkTrue(x > BigInt(50));
	checkTrue(x > BigInt(-500));
	checkTrue(BigInt(-200) > BigInt(-500));

	checkTrue(x <= x);
	checkTrue(x <= 200);
	checkTrue(BigInt(50) <= x);
	checkTrue(BigInt(-500) <= x);
	checkTrue(BigInt(-500) <= BigInt(-200));

	checkTrue(x >= x);
	checkTrue(BigInt(200) >= x);
	checkTrue(x >= BigInt(50));
	checkTrue(x >= BigInt(-500));
	checkTrue(BigInt(-200) >= BigInt(-500));
	checkTrue(BigInt(0) == -BigInt(0));

	checkEqual(BigInt(10) + BigInt(10), "20");
	checkEqual(BigInt(-10) + BigInt(10), "0");
	checkEqual(BigInt(10) + BigInt(-10), "0");
	checkEqual(BigInt(-10) + BigInt(-10), "-20");

	checkEqual(BigInt(10) - BigInt(10), "0");
	checkEqual(BigInt(-10) - BigInt(10), "-20");
	checkEqual(BigInt(10) - BigInt(-10), "20");
	checkEqual(BigInt(-10) - BigInt(-10), "0");

	checkEqual(BigInt(0) + BigInt(-1), "-1");
	checkEqual(BigInt(0) - BigInt(1), "-1");

	checkEqual(BigInt(100) - BigInt(100), "0");
	checkEqual(BigInt(99) - BigInt(100), "-1");
	checkEqual(BigInt(10) - BigInt(11), "-1");
	checkEqual(BigInt(20) - BigInt(19), "1");

	for (int i = -21; i <= 21; ++i)
	{
		for (int j = -21; j <= 21; ++j)
		{
			check(i, j);
		}
	}

	const int64_t step = std::numeric_limits<uint32_t>::max() / 99;
	const int64_t lower = std::numeric_limits<int32_t>::min() + step;
	const int64_t upper = std::numeric_limits<int32_t>::max() - step;

	for (int64_t i = lower; i < upper; i += step)
	{
		for (int64_t j = -99; j < 99; ++j)
		{
			check(i, j);
		}
	}

	return 0;
}
