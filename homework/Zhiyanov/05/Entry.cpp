#include <iostream>
#include <cmath>

class BigInt{
private:
	int sign;
	int len;
	int size;
	int *data;

    int getlen(int num){
        if (num == 0){
            return 1;
        }

        int res = 0;

        while (num != 0){
            res++;
            num /= 10;
        }

        return res;
    }

    BigInt(int nlen, int nsize){
    	sign = 1;
        size = nsize;
        len = (nlen < nsize) ? nlen : 0;
        data = new int[size];
        for (int i = 0; i < size; i++)
            data[i] = 0;
    }

public:

 	BigInt(int num = 0){
        if (num < 0)
        	sign = -1;
        else 
        	sign = 1;

        num = (num > 0) ? num : -num;
        len = getlen(num);
        size = len * 2 + 10;
        data = new int[size];

        for (int i = 0; i < size; ++i){
            if (num > 0){
                data[i] = num % 10;
                num /= 10;
            } else {
                data[i] = 0;
            }
        }
    }

    BigInt(const BigInt& num) : sign(num.sign), len(num.len), size(num.size){
    	data = new int[size];

    	for (int i = 0; i < size; ++i)
            data[i] = num.data[i];
    }

    ~BigInt(){
    	if (data)
    		delete [] data;
    }

    int getLen(){
    	return len;
    }

    int getSize(){
    	return size;
    }

    BigInt& operator=(const BigInt& num){
    	if (*this == num)
    		return *this;

    	if (size < num.len){
    		if (data)
    			delete [] data;

    		size = num.len * 2 + 10;
    		data = new int[size];
    	}

    	sign = num.sign;
    	len = num.len;
    	for (int i = 0; i < size; ++i)
    		if (i < num.len){
    			data[i] = num.data[i];
    		} else {
    			data[i] = 0;
    		}

		return *this;
    }

    bool operator==(const BigInt& num) const{
    	if (len != num.len || sign == num.sign)
    		return false;

    	for (int i = 0; i < len; ++i)
    		if (data[i] != num.data[i])
    			return false;

    	return true;
    }

    bool operator!=(const BigInt& num) const{
    	return !(operator==(num));
    }

    bool operator<(const BigInt& num) const{
    	if (sign < num.sign)
    		return true;

    	if (len < num.len)
    		return true;

    	if (sign > num.sign)
    		return false;

    	if (len > num.len)
    		return false;

    	for (int i = len - 1; i >= 0; --i){
    		if (data[i] == num.data[i])
    			continue;

    		return data[i] < num.data[i];
    	}

    	return false;
    }

    bool operator>(const BigInt& num) const{
    	if (sign > num.sign)
    		return true;

    	if (len > num.len)
    		return true;

    	if (sign < num.sign)
    		return false;

    	if (len < num.len)
    		return false;

    	for (int i = len - 1; i >= 0; --i){
    		if (data[i] == num.data[i])
    			continue;

    		return data[i] > num.data[i];
    	}

    	return false;
    }

    bool operator<=(const BigInt& num) const{
    	return !(operator>(num));
    }

    bool operator>=(const BigInt& num) const{
    	return !(operator<(num));
    }

    BigInt operator-() {
        BigInt num(*this);
        num.sign = -num.sign;
        return num;
    }

    friend BigInt abs(const BigInt& a);
    friend BigInt operator+(const BigInt& a, const BigInt& b);
    friend BigInt operator-(const BigInt& a, const BigInt& b);
    friend BigInt operator*(const BigInt& a, const BigInt& b);
    friend BigInt operator/(const BigInt& a, const BigInt& b);
    friend BigInt operator%(const BigInt& a, const BigInt& b);
    friend std::ostream& operator<<(std::ostream& out, const BigInt& num);
};

std::ostream& operator<<(std::ostream& out, const BigInt& num){
	if (num.len == 0){
    	out << 0;
    	return out;
	}

    if (num.sign == -1)
    	out << '-';
    for (int i = num.len - 1; i >= 0; --i)
    	out << num.data[i];

    return out;
}

BigInt abs(const BigInt& a){
    BigInt num = a;
    num.sign = 1;
    return num;
}

BigInt operator+(const BigInt& a, const BigInt& b){
	int buf = 0;
	int maxlen = std::max(a.len, b.len);
	int minlen = std::min(a.len, b.len);
	BigInt num(0, maxlen * 2 + 10);

	if (a.sign == b.sign){
		for (int i = 0; i < minlen; ++i){
			int tmp = buf + a.data[i] + b.data[i];
			num.data[i] = tmp % 10;
			buf = tmp / 10;
		}

		if (a.len < b.len)
			for (int i = minlen; i < maxlen; ++i){
				int tmp = buf + b.data[i];
				num.data[i] = tmp % 10;
				buf = tmp / 10;
			}
		else
			for (int i = minlen; i < maxlen; ++i){
				int tmp = buf + a.data[i];
				num.data[i] = tmp % 10;
				buf = tmp / 10;
			}

		if (buf != 0)
			num.data[maxlen] = buf;

		num.sign = a.sign;

		int tmp = num.size - 1;
		while(num.data[tmp] == 0 && tmp > -1)
			--tmp;
		num.len = tmp + 1;

		return num;
	}

	if (abs(a) > abs(b)){
		for (int i = 0; i < b.len; ++i){
			int tmp = buf + a.data[i] - b.data[i];
			if (tmp < 0){
				num.data[i] = 10 + tmp;
				buf = -1;
			} else {
				num.data[i] = tmp;
				buf = 0;
			}
		}

		for (int i = b.len; i < a.len; ++i){
			int tmp = buf + a.data[i];
			if (tmp < 0){
				num.data[i] = 10 + tmp;
				buf = -1;
			} else {
				num.data[i] = tmp;
				buf = 0;
			}
		}

		num.sign = a.sign;

		int tmp = num.size - 1;
		while(num.data[tmp] == 0 && tmp > -1)
			--tmp;
		num.len = tmp + 1;

		return num;
	}

	for (int i = 0; i < a.len; ++i){
		int tmp = buf + b.data[i] - a.data[i];
		if (tmp < 0){
			num.data[i] = 10 + tmp;
			buf = -1;
		} else {
			num.data[i] = tmp;
			buf = 0;
		}
	}

	for (int i = a.len; i < b.len; ++i){
		int tmp = buf + b.data[i];
		if (tmp < 0){
			num.data[i] = 10 + tmp;
			buf = -1;
		} else {
			num.data[i] = tmp;
			buf = 0;
		}
	}

	num.sign = b.sign;

	int tmp = num.size - 1;
	while(num.data[tmp] == 0 && tmp > -1)
		--tmp;
	num.len = tmp + 1;

	return num;
}


BigInt operator-(const BigInt& a, const BigInt& b) {
    BigInt c = b;
    c.sign = -c.sign;
    return operator+(a,c);
}

BigInt operator*(const BigInt& a, const BigInt& b) {
   	int maxlen = std::max(a.len, b.len);
	BigInt num(0, maxlen * 2 + 10);

	num.sign = a.sign * b.sign;

	for (int i = 0; i < a.len; ++i){
		int buf = 0;
		for (int j = 0; j < b.len; ++j){
			int tmp = a.data[i] * b.data[j] + buf;
			num.data[i + j] += tmp;
			buf = num.data[i + j] / 10;
			num.data[i + j] %= 10;
		}

		num.data[i + b.len] += buf;
	}

	int tmp = num.size - 1;
	while (num.data[tmp] == 0 && tmp > -1)
		--tmp;
	num.len = tmp + 1;

	return num;
}

BigInt operator/(const BigInt& a, const BigInt& b) {
    BigInt count(0), one(1), absa(abs(a)), absb(abs(b));
    count.sign = a.sign * b.sign;
    one.sign = a.sign * b.sign;
    while(absa >= absb) {
        count = count + one;
        absa = absa - absb;
    }
    return count;
}

BigInt operator%(const BigInt& a, const BigInt& b) {
    BigInt num(a), zero(0);
    num = num - ((a / b) * b) ;
    return num;
}

int main(int argc, char *argv[]) {
    BigInt a(12);
    BigInt b(5);
    std::cout << a << "\n";
    std::cout << b << "\n";
    std::cout << a % b << "\n";
    return 0;
}