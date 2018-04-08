#include <iostream>

class BigInt
{
	short* bi_;
	bool isnegative;
	int capacity;
	int size;
	void mem(int s) { bi_ = new short[s]; capacity = s; size = s * 2; }
	const BigInt check()
	{
		for (int i = 0; i < capacity; i++)
			if (bi_[i] != 0)
				return *this;
		return BigInt();
	}
	BigInt add_capacity()
	{
		BigInt tmp;
		tmp.size = size*2;
		tmp.capacity = capacity;
		tmp.bi_ = new short[tmp.size];
		for (int i = 0; i < capacity; i++)
			tmp.bi_[i] = bi_[i];
		for (int i = capacity; i < tmp.size; i++)
			tmp.bi_[i] = 0;
		tmp.isnegative = isnegative;
		return tmp;
	}
	BigInt check_null()
	{
		if (capacity == 1)
			if (bi_[0] == 0)
				return BigInt(0);
		BigInt tmp;
		for (int i = capacity - 1; i>0; i--)
			if (bi_[i] != 0)
			{
				tmp.capacity = i + 1;
				break;
			}
		tmp.isnegative = isnegative;
		tmp.size = size;
		tmp.bi_ = new short[tmp.capacity];
		for (int j = 0; j<tmp.capacity; j++)
			tmp.bi_[j] = bi_[j];
		return tmp;
	}
public:
	BigInt() : bi_(new short[1]), isnegative(false), capacity(1),size(1) { bi_[0] = 0; }
	BigInt(long long int c)
	{
		capacity = 0;
		if (c == 0)
			capacity = 1;
		isnegative = false;
		long long int tmp = c;
		while (tmp)
		{
			tmp /= 10;
			capacity++;
		}
		if (c < 0)
		{
			isnegative = true;
			c = std::abs(c);
		}
		size =capacity*2;
		bi_ = new short[size];
		for (int i = 0; i < capacity; i++) {
			bi_[i] = c % 10;
			c /= 10;
		}
		for (int i = capacity; i < size; ++i)
			bi_[i] = 0;
	}
	BigInt(BigInt&& R)
	{
		size = R.size;
		capacity = R.capacity;
		isnegative = R.isnegative;
		bi_ = R.bi_;
		R.bi_ = nullptr;
	}
	BigInt(const BigInt& R)
	{
		size = R.size;
		capacity = R.capacity;
		isnegative = R.isnegative;
		bi_ = new short[size];
		for (int i = 0; i < size; i++)
			bi_[i] = R.bi_[i];
	}
	BigInt& operator = (BigInt && R)
	{
		delete[]bi_;
		size = R.size;
		capacity = R.capacity;
		isnegative = R.isnegative;
		bi_ = R.bi_;
		R.bi_ = nullptr;
		return *this;
	}
	BigInt& operator=(const BigInt& R)
	{
		delete[] bi_;
		size = R.size;
		isnegative = R.isnegative;
		capacity = R.capacity;
		if (isnegative) {
			bi_ = new short[size];
			for (int i = 0; i < size; i++)
				bi_[i] = R.bi_[i];
		}
		else {
			bi_ = new short[size];
			for (int i = 0; i < size; i++)
				bi_[i] = R.bi_[i];
		}
		return *this;
	}
	friend std::ostream& operator<<(std::ostream& out, const BigInt& R);
	int show_size() { return size; }
	bool operator==(const BigInt& R) const
	{
		if (isnegative != R.isnegative)
			return false;
		if (capacity != R.capacity)
			return false;
		for (int i = 0; i < capacity; i++)
			if (bi_[i] != R.bi_[i])
				return false;
		return true;
	}
	bool operator!=(const BigInt& R) const
	{
		return !(*this == R);
	}
	bool operator<(const BigInt& R) const
	{
		if (*this == R)
			return false;
		if (R.isnegative < isnegative)
			return true;
		if (isnegative < R.isnegative)
			return false;
		if (isnegative == 0)
		{
			if (capacity < R.capacity)
				return true;
			if (capacity > R.capacity)
				return false;
			for (int i = capacity - 1; i >= 0; i--)
				if (bi_[i] > R.bi_[i])
					return false;
				else
					if (bi_[i] < R.bi_[i])
						return true;
			return true;
		}
		if (capacity > R.capacity)
			return true;
		if (capacity < R.capacity)
			return false;
		for (int i = capacity - 1; i >= 0; i--)
			if (bi_[i] < R.bi_[i])
				return false;
			else
				if (bi_[i] > R.bi_[i])
					return true;
		return true;
	}
	bool operator>(const BigInt& R) const
	{
		if (*this == R)
			return false;
		if (isnegative < R.isnegative)
			return true;
		if (isnegative > R.isnegative)
			return false;
		if (isnegative == 0)
		{
			if (capacity > R.capacity)
				return true;
			if (capacity < R.capacity)
				return false;
			for (int i = capacity - 1; i >= 0; i--)
				if (bi_[i] > R.bi_[i])
					return true;
				else
					if (bi_[i] < R.bi_[i])
						return false;
			return false;
		}
		if (capacity < R.capacity)
			return true;
		if (capacity > R.capacity)
			return false;
		for (int i = capacity - 1; i >= 0; i--)
			if (bi_[i] > R.bi_[i])
				return false;
			else
				if (bi_[i] < R.bi_[i])
					return true;
		return true;
	}
	bool operator<=(const BigInt& R) const
	{
		if (*this == R)
			return true;
		return *this < R;

	}
	bool operator>=(const BigInt& R) const
	{
		if (*this == R)
			return true;
		return *this > R;
	}
	BigInt operator-() const
	{
		if (capacity == 1)
			if (bi_[0] == 0)
				return *this;
		BigInt R_(*this);
		R_.isnegative = !isnegative;
		return R_;
	}
	BigInt abs() const
	{
		if (this->isnegative == true)
			return -*this;
		else
			return *this;
	}
	BigInt operator+(const BigInt& R) const
	{
		BigInt l(*this);
		BigInt r(R);

		if (l.isnegative == true && r.isnegative == false)
			return r - (-l);
		if (l.isnegative == false && r.isnegative == true)
			return l - (-r);
		r = -r;
		return l - r;
	}
	BigInt operator-(const BigInt& R) const
	{
		BigInt left(*this);
		BigInt right(R);
		if (left.isnegative == false && right.isnegative == false)
		{
			if (left.capacity > right.capacity)
			{
				for (int i = 0; i < right.capacity; i++)
				{
					if (left.bi_[i] < right.bi_[i])
					{
						int j;
						for (j = i + 1; left.bi_[j] == 0; j++) {}
						left.bi_[j]--;
						for (int k = j - 1; k > i; k--)
							left.bi_[k] = 9;
						left.bi_[i] += (10 - right.bi_[i]);
					}
					else {
						left.bi_[i] -= right.bi_[i];
					}

				}
				return left.check_null();

			}
			if (left.capacity == right.capacity)
			{
				if (right == left)
					return BigInt();
				if (right > left)
				{
					BigInt tmp = std::move(left);
					left = std::move(right);
					right = std::move(tmp);
					left.isnegative = true;
				}
				for (int i = 0; i < capacity; i++)
				{
					if (right.bi_[i] > left.bi_[i])
					{
						int j = i + 1;
						while (left.bi_[j] == 0)
						{
							j++;
						}
						left.bi_[j]--;
						left.bi_[i] += (10 - right.bi_[i]);
						for (int k = j - 1; k > i; k--)
							left.bi_[k] = 9;
						continue;
					}
					left.bi_[i] -= right.bi_[i];
				}
				return left.check_null();;
			}
			for (int i = 0; i < left.capacity; i++)
			{
				if (left.bi_[i] > right.bi_[i])
				{
					int j;
					for (j = i + 1; right.bi_[j] == 0; j++) {}
					right.bi_[j]--;
					for (int k = j - 1; k > i; k--)
						right.bi_[k] = 9;
					right.bi_[i] += (10 - left.bi_[i]);
				}
				else {
					right.bi_[i] -= left.bi_[i];
				}

			}
			right.isnegative = true;
			return right.check_null();
		}
		if (left.isnegative == true && right.isnegative == true)
		{
			left.isnegative = false;
			right.isnegative = false;
			return right - left;
		}
		if (left.isnegative == true && right.isnegative == false)
		{
			if (left.capacity > right.capacity)
			{
				for (int i = 0; i < right.capacity; i++)
				{
					left.bi_[i] += right.bi_[i];
					if (left.bi_[i] > 9) {
						int j;
						for (j = i + 1; j < left.capacity; ++j)
							if (left.bi_[j] != 9)
								break;
						if (j == left.capacity) {
							for (int k = j - 2; k > i; k--)
								left.bi_[k] = 0;
							left.bi_[j - 1]++;
						}
						else {
							left.bi_[j]++;
							for (int k = j - 1; k > i; k--)
								left.bi_[k] = 0;
						}
						left.bi_[i] %= 10;
					}
				}
				if (left.bi_[left.capacity - 1] > 9)
				{
					left.capacity++;
					if(left.capacity==left.size)
						left = left.add_capacity();
					left.bi_[left.capacity - 1]++;
					left.bi_[left.capacity - 2] %= 10;
				}
				return left.check_null();
			}
			if (left.capacity < right.capacity)
			{
				for (int i = 0; i < left.capacity; i++)
				{
					right.bi_[i] += left.bi_[i];
					if (right.bi_[i] > 9) {
						int j;
						for (j = i + 1; j < right.capacity; ++j)
							if (right.bi_[j] != 9)
								break;
						if (j == right.capacity) {
							for (int k = j - 2; k > i; k--)
								right.bi_[k] = 0;
							right.bi_[j - 1]++;
						}
						else {
							right.bi_[j]++;
							for (int k = j - 1; k > i; k--)
								right.bi_[k] = 0;
						}
						right.bi_[i] %= 10;
					}
				}
				if (right.bi_[left.capacity - 1] > 9)
				{
					right.capacity++;
					if (right.capacity == right.size)
						right = right.add_capacity();
					right.bi_[right.capacity - 1]++;
					right.bi_[right.capacity - 2] %= 10;
				}
				right.isnegative = true;
				return right.check_null();
			}
			for (int i = 0; i < left.capacity; i++)
				left.bi_[i] += right.bi_[i];
			for (int i = 0; i < left.capacity - 1; i++)
			{
				if (left.bi_[i] > 9)
				{
					left.bi_[i + 1]++;
					left.bi_[i] %= 10;
				}
			}
			if (left.bi_[left.capacity - 1] > 9)
			{
				left.capacity++;
				if (left.capacity == left.size)
					left = left.add_capacity();
				left.bi_[left.capacity - 1]++;
				left.bi_[left.capacity - 2] %= 10;
			}
			return left.check_null();
		}
		if (left.isnegative == false && right.isnegative == true)
		{
			BigInt tmp = std::move(left);
			left = std::move(right);
			right = std::move(tmp);
			if (left.capacity < right.capacity)
			{
				for (int i = 0; i < left.capacity; i++)
				{
					right.bi_[i] += left.bi_[i];
					if (right.bi_[i] > 9) {
						int j;
						for (j = i + 1; j < right.capacity; ++j)
							if (right.bi_[j] != 9)
								break;
						if (j == right.capacity) {
							for (int k = j - 2; k > i; k--)
								right.bi_[k] = 0;
							right.bi_[j - 1]++;
						}
						else {
							right.bi_[j]++;
							for (int k = j - 1; k > i; k--)
								right.bi_[k] = 0;
						}
						right.bi_[i] %= 10;
					}
				}
				if (right.bi_[right.capacity - 1] > 9)
				{
					right.capacity++;
					if (right.capacity == right.size)
						right = right.add_capacity();
					right.bi_[right.capacity - 1]++;
					right.bi_[right.capacity - 2] %= 10;
				}
				return right.check_null();
			}
			if (left.capacity > right.capacity)
			{
				left.isnegative = !left.isnegative;
				for (int i = 0; i < right.capacity; i++)
				{
					left.bi_[i] += right.bi_[i];
					if (left.bi_[i] > 9) {
						int j;
						for (j = i + 1; j < left.capacity; ++j)
							if (left.bi_[j] != 9)
								break;
						if (j == left.capacity) {
							for (int k = j - 2; k > i; k--)
								left.bi_[k] = 0;
							left.bi_[j - 1]++;
						}
						else {
							left.bi_[j]++;
							for (int k = j - 1; k > i; k--)
								left.bi_[k] = 0;
						}
						left.bi_[i] %= 10;
					}
				}
				if (left.bi_[left.capacity - 1] > 9)
				{
					left.capacity++;
					if (left.capacity == left.size)
						left = left.add_capacity();
					left.bi_[left.capacity - 1]++;
					left.bi_[left.capacity - 2] %= 10;
				}
				return left.check_null();
			}
			left.isnegative = false;
			right.isnegative = true;
			for (int i = 0; i < left.capacity; i++)
				left.bi_[i] += right.bi_[i];
			for (int i = 0; i < left.capacity - 1; i++)
			{
				if (left.bi_[i] > 9)
				{
					left.bi_[i + 1]++;
					left.bi_[i] %= 10;
				}
			}
			if (left.bi_[left.capacity - 1] > 9)
			{
				left.capacity++;
				if(left.capacity==left.size)
					left = left.add_capacity();
				left.bi_[left.capacity - 1]++;
				left.bi_[left.capacity - 2] %= 10;
			}
			left.isnegative = left.isnegative;
			return left.check_null();
		}
		return BigInt();

	}
	BigInt operator*(const BigInt& R) const
	{
		if (R == 0 || *this == 0)
			return BigInt(0);
		BigInt* a = new BigInt[R.capacity];
		for (int i = 0; i < R.capacity; i++)
		{
			a[i].mem(capacity + i);
			for (int j = 0; j < capacity; j++)
				a[i].bi_[j + i] = bi_[j] * R.bi_[i];
			for (int k = 0; k < i; k++)
				a[i].bi_[k] = 0;
			for (int m = 0; m < a[i].capacity - 1; m++)
			{
				if (a[i].bi_[m] > 9)
				{
					a[i].bi_[m + 1] += a[i].bi_[m] / 10;
					a[i].bi_[m] %= 10;
				}
			}
			if (a[i].bi_[a[i].capacity - 1] > 9)
			{
				a[i].capacity++;
				if (a[i].capacity == a[i].size)
					a[i] = a[i].add_capacity();
				a[i].bi_[a[i].capacity - 1] = a[i].bi_[a[i].capacity - 2] / 10;
				a[i].bi_[a[i].capacity - 2] %= 10;
			}
			if (i != 0) {
				for (int k = 0; k < a[i - 1].capacity; k++)
					a[i].bi_[k] += a[i - 1].bi_[k];
				for (int m = 0; m < a[i].capacity - 1; m++)
				{
					if (a[i].bi_[m] > 9)
					{
						a[i].bi_[m + 1] += a[i].bi_[m] / 10;
						a[i].bi_[m] %= 10;
					}
				}
				if (a[i].bi_[a[i].capacity - 1] > 9)
				{
					a[i].capacity++;
					if (a[i].capacity == a[i].size)
						a[i] = a[i].add_capacity();
					a[i].bi_[a[i].capacity - 1] = a[i].bi_[a[i].capacity - 2] / 10;
					a[i].bi_[a[i].capacity - 2] %= 10;
				}
			}
		}
		BigInt r(a[R.capacity - 1]);
		if ((isnegative == true && R.isnegative == false) || (isnegative == false && R.isnegative == true))
			r = -r;
		return r;
	}
	BigInt& operator+=(const BigInt& R)
	{
		*this = *this + R;
		return *this;
	}
	BigInt& operator-=(const BigInt& R)
	{
		*this = *this - R;
		return *this;
	}
	BigInt& operator*=(const BigInt& R)
	{
		*this = *this * R;
		return *this;
	}
	BigInt operator/(const BigInt& R) const
	{
		if (*this == 0)
			return BigInt(0);
		BigInt left(*this);
		BigInt right(R);
		left.isnegative = false;
		right.isnegative = false;
		if (capacity < R.capacity)
			return BigInt();
		BigInt tmp;
		while (left >= right)
		{
			left -= right;
			tmp += 1;
		}
		if ((isnegative == true && R.isnegative == false) || (isnegative == false && R.isnegative == true))
			tmp.isnegative = true;
		return tmp.check_null();
	}
	~BigInt() { delete[]bi_; }
};


std::ostream& operator<<(std::ostream& out, const BigInt& R)
{
	if (R.isnegative)
		out << "-";
	for (int i = R.capacity - 1; i >= 0; i--)
		out << R.bi_[i];
	return out;
}
