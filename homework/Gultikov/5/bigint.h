#ifndef BIGINT_H_INCLUDED
#define BIGINT_H_INCLUDED
#pragma once

using cell_type = signed char;

class BigInt
{
    ///main variables
    //sign = 0 +
    //sign = 1 -
    bool sign;
    size_t size;
    size_t cells = 10;
    cell_type* elements = nullptr;

    ///to control cells
    void push_back(cell_type new_element);
    void push_front(cell_type new_element);
    void allocate();
    void delete_zeros();
    void normalization(size_t idx);
    cell_type binSearch(const BigInt &dividend, const BigInt &divisor) const;

public:
    ///constructos, destructors
    BigInt();
    BigInt(int64_t new_element);
    BigInt(const BigInt& other);
    ~BigInt();

    ///operators and functions
    BigInt abc() const;
    BigInt operator+(const BigInt& other) const;
    BigInt operator-() const;
    BigInt operator-(const BigInt& other) const;
    BigInt operator*(const BigInt& other) const;
    BigInt operator/(const BigInt& other) const;
    bool operator==(const BigInt& other) const;
    bool operator!=(const BigInt& other) const;
    bool operator<(const BigInt& other) const;
    bool operator>(const BigInt& other) const;
    bool operator<=(const BigInt& other) const;
    bool operator>=(const BigInt& other) const;
    BigInt& operator=(const BigInt& other);
    friend std::ostream& operator << (std::ostream& os, const BigInt& num);
};

///to control cells
void BigInt::push_back(cell_type new_element)
{
    elements[size++] = new_element;
    if(size >= cells)
        allocate();
}

void BigInt::push_front(cell_type new_element)
{
    for (size_t i = size; i > 0; i--)
		elements[i] = elements[i - 1];

	size++;
	if (cells == size)
		allocate();

	elements[0] = new_element;
}

void BigInt::allocate()
{
    cells *= 2;
    cell_type* new_elements = new cell_type[cells];
    for(size_t i = 0; i<size; ++i){
        new_elements[i] = elements[i];
    }
    delete[] elements;
    elements = new_elements;
}

void BigInt::delete_zeros()
{
    for (size_t i = size - 1; i != 0; --i)
	{
		if (elements[i] != 0 )
			break;
		size--;
	}
}

void BigInt::normalization(size_t idx)
{
    size_t i = idx + 1;
    while(i > idx && i < size){
        if(elements[i] == 0)
            ++i;
        else if(elements[i] != 0){
            elements[i] -= 1;
            --i;
            elements[i] += 10;
        }
    }
}

///constructos, destructors
BigInt::BigInt(): sign(0), size(0)
{
    elements = new cell_type[cells];
    push_back(0);
}

BigInt::BigInt(int64_t new_element):size(0)
{
    if(new_element < 0){
        sign = 1;
        new_element  *= -1;
    }
    else
        sign = 0;

    elements = new cell_type[cells];

    if(new_element == 0)
        push_back(0);
    else{
        for(size_t i = 0; new_element>0; ++i){
            push_back(new_element % 10);
            new_element /= 10;
        }
    }
}

BigInt::BigInt(const BigInt& other):sign(other.sign), size(other.size), cells(other.cells)
{
    elements = new cell_type[cells];
    for(size_t i = 0; i<size; ++i){
        elements[i] = other.elements[i];
    }
}

BigInt::~BigInt()
{
    delete[] elements;
}

///operators and functions
BigInt BigInt::abc() const
{
    if(sign)
        return (-*this);
    else
        return *this;
}

BigInt BigInt::operator+(const BigInt& other) const
{
    BigInt ans;
    // a+b
    ans.size = 0;
    cell_type remainder = 0;
    BigInt a;
    BigInt b;
    cell_type a_sign, b_sign;

    if(abc() < other.abc()){
        a = other;
        b = *this;
    }
    else{
        b = other;
        a = *this;
    }
    a_sign = a.sign ? -1: 1;
    b_sign = b.sign ? -1: 1;

    for(size_t i = 0; i < b.size; ++i){
            cell_type n = a_sign*(a.elements[i] * a_sign + b.elements[i] * b_sign + remainder);
        if(a.sign != b.sign && (n<0)){
            a.normalization(i);
        }
        ans.push_back((a.elements[i] * a_sign + b.elements[i] * b_sign + remainder)%10);
        remainder = (a.elements[i] * a_sign + b.elements[i] * b_sign + remainder)/10;
    }
    for(size_t i = b.size; i < a.size; ++i){
        ans.push_back((a.elements[i] * a_sign + remainder)%10);
        remainder = (a.elements[i] * a_sign + remainder)/10;
    }
    if(remainder != 0){
        ans.push_back(remainder);
    }

    ans.delete_zeros();

    if(ans.elements[ans.size-1] >= 0)
        ans.sign = 0;
    else
        ans.sign = 1;

    for(size_t i = 0; i < ans.size; ++i){
        if(ans.elements[i] < 0)
            ans.elements[i] *= -1;
    }
    return ans;
}

BigInt BigInt::operator-() const
{
    BigInt ans(*this);
    if(size == 1 && elements[0] == 0)
        ans.sign = sign;
    else
        ans.sign = !sign;
    return ans;
}

BigInt BigInt::operator-(const BigInt& other) const
{
    return(*this+(-other));
}

BigInt BigInt::operator*(const BigInt& other) const
{
    BigInt ans(0);
    cell_type remainder = 0;

    for(size_t i = 0; i<size; ++i){
        if(elements[i] == 0)
            continue;
        else{
            BigInt num(0);
            num.size = 0;

            for(size_t k = 0; k<i; ++k){
                num.push_back(0);
            }

            for(size_t j = 0; j<other.size; ++j){
                num.push_back((elements[i] * other.elements[j] + remainder)%10);
                remainder = (elements[i] * other.elements[j] + remainder)/10;
            }
            while(remainder != 0){
                num.push_back(remainder%10);
                remainder = remainder/10;
            }
            ans = ans + num;
        }
    }

    if(sign == other.sign || ans.elements[ans.size - 1] == 0)
        ans.sign = 0;
    else
        ans.sign = 1;

    return ans;
}

cell_type BigInt::binSearch(const BigInt &dividend, const BigInt &divisor) const
{
	//max(divisor * x <= dividend)
	cell_type ans = 0;
	cell_type min = 0;
	cell_type max = 10;

	while (min <= max)
	{
		cell_type curr = (max + min) / 2;
		if (BigInt(curr) * divisor <= dividend)
		{
			ans = curr;
			min = curr + 1;
		}
		else
			max = curr - 1;
	}
	return ans;
}

BigInt BigInt::operator/(const BigInt& other) const
{
    BigInt ans;
	BigInt aux;
	aux.size = 0;
	BigInt abs_num = other.abc();
	for (size_t i = 0; i < size; i++)
	{
		aux.push_front(elements[size - 1 - i]);
		aux.delete_zeros();
		cell_type div = binSearch(aux, abs_num);
		ans.push_front(div);
		aux = aux - abs_num * BigInt(div);
	}
	ans.delete_zeros();
	if(sign == other.sign || ans.elements[ans.size - 1] == 0)
        ans.sign = 0;
    else
        ans.sign = 1;
	return ans;
}

bool BigInt::operator==(const BigInt& other) const
{
    if(size != other.size || sign != other.sign)
        return false;
    else{
        for(size_t i = 0; i < size; ++i){
            if(elements[i] != other.elements[i])
                return false;
        }
    }
    return true;
}

bool BigInt::operator!=(const BigInt& other) const
{
    return!(*this==other);
}

BigInt& BigInt::operator=(const BigInt& other)
{
    sign = other.sign;
    size = other.size;
    cells = other.cells;

    delete[] elements;
    elements = new cell_type[cells];
    for(size_t i = 0; i < size; ++i)
    {
        elements[i] = other.elements[i];
    }
    return *this;
}

bool BigInt::operator<(const BigInt& other) const
{
    if(*this == other)
        return false;
    else if(sign == other.sign && size == other.size){
        for(size_t i = size - 1; i!= -1; --i){
            if(sign){
                if(elements[i] > other.elements[i] && elements[i] != other.elements[i])
                    return true;
                else if(elements[i] < other.elements[i] && elements[i] != other.elements[i])
                    return false;
            }
            else{
                if(elements[i] < other.elements[i] && elements[i] != other.elements[i])
                    return true;
                else if(elements[i] > other.elements[i] && elements[i] != other.elements[i])
                    return false;
            }
        }
    }
    else if(sign == other.sign && size != other.size){
        if(sign){
            if(size > other.size)
                return true;
            else
                return false;
        }
        else{
            if(size > other.size)
                return false;
            else
                return true;
        }
    }
    else if(sign > other.sign){
        return true;
    }
    else
        return false;
}

bool BigInt::operator>(const BigInt& other) const
{
    if(*this == other)
        return false;
    else
        return !(*this < other);
}

bool BigInt::operator<=(const BigInt& other) const
{
    if(*this == other)
        return true;
    else
        return !(*this > other);
}

bool BigInt::operator>=(const BigInt& other) const
{
    if(*this == other){
       return true;
    }
    else
        return !(*this < other);
}

std::ostream& operator << (std::ostream& os, const BigInt& num)
{
    if(num.sign)
        os << '-';
    for(int i = num.size - 1; i>-1; --i)
        os << static_cast<cell_type>('0' + num.elements[i]);
    return os;
}

#endif // BIGINT_H_INCLUDED
