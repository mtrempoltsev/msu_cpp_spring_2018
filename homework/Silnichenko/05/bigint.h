#ifndef BIGINT_H__
#define BIGINT_H__
#include <iostream>
#include <exception>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#define base__ 16
class BigInt
{
	friend BigInt operator+(const BigInt &a, const BigInt &b);
	friend BigInt operator-(const BigInt &a, const BigInt &b);
	friend BigInt operator*(const BigInt &a, const BigInt &b);
	friend BigInt operator/(const BigInt &a, const BigInt &b);
	friend std::ostream& operator<<(std::ostream &out, const BigInt &a);
	friend int BICmp(const BigInt &a, const BigInt &b);
	private:
	int64_t size_;
	int64_t csz_;
	char *digits_;
	char sign_;
	void Enlarge(const int64_t a=2);
	void Multen(const int64_t a=1);
	void KillZeroes();
	char FirstDigit() const;
	void LowLevelMinus(const BigInt& a);
	void LowLevelPlus(const BigInt& a);
	void LowLevelMul(const BigInt& a, const BigInt& b);
	public:
	BigInt();
	BigInt(int64_t a);
	BigInt(const BigInt& a);
	~BigInt();
	/*operators below*/
	BigInt operator=(const BigInt& a);
	bool operator>(const BigInt& a) const;
	bool operator>=(const BigInt& a) const;
	bool operator==(const BigInt& a) const;
	bool operator<=(const BigInt& a) const;
	bool operator<(const BigInt& a) const;
	bool operator!=(const BigInt& a) const;
	BigInt operator-() const;
};
BigInt operator+(const BigInt &a, const BigInt &b);
BigInt operator-(const BigInt &a, const BigInt &b);
BigInt operator*(const BigInt &a, const BigInt &b);
BigInt operator/(const BigInt &a, const BigInt &b);
std::ostream& operator<<(std::ostream &out, const BigInt &a);
int BICmp(const BigInt &a, const BigInt &b);
void BigInt::Enlarge(const int64_t a)
{
	int size=size_*a;
	char *digits=(char *)malloc(size);
	if(digits==nullptr)
	{
		throw std::bad_alloc();
	}
	memcpy(digits, digits_, size_);
	free(digits_);
	digits_=digits;
	size_=size;
}
void BigInt::Multen(const int64_t a)
{
	int64_t size=size_;
	int64_t b=1;
	if(a<1)
	{
		return;
	}
	while((csz_+a-1)>=size)
	{
		size*=2;
		b*=2;
	}
	if(b>1)
	{
		Enlarge(b);
	}
	memmove(digits_+a, digits_, csz_);
	for(int i=0; i<a; i++)
	{
		digits_[i]=0;
	}
	csz_+=a;
}
void BigInt::KillZeroes()
{
	while(digits_[csz_-1]==0 && csz_>1)
	{
		csz_--;
	}
	if(csz_==1 && digits_[0]==0)
	{
		sign_=0;
	}
}
char BigInt::FirstDigit() const
{
	return digits_[csz_-1];
}
void BigInt::LowLevelMinus(const BigInt &b)
{//used when this>a
	int d=0, t;
	int64_t i;
	for(i=0; i<b.csz_; i++)
	{
		t=digits_[i]-b.digits_[i]-d;
		if(t<0)
		{
			digits_[i]=t+10;
			d=1;
		}
		else
		{
			digits_[i]=t;
			d=0;
		}
	}
	while(d>0)
	{
		t=digits_[i]-d;
		if(t<0)
		{
			digits_[i]=t+10;
			d=1;
		}
		else
		{
			digits_[i]=t;
			d=0;
		}
		i++;
	}
	KillZeroes();
}
void BigInt::LowLevelPlus(const BigInt &b)
{//sign_==a.sign_
	int64_t i;
	char t=0, d=0;
	if(size_<b.size_)
	{
		if(b.size_/size_ * size_!=b.size_)
		{
			throw std::overflow_error("lowlevel+ fail");
		}
		Enlarge(b.size_/size_);
	}
	for(i=0; i<b.csz_; i++)
	{
		if(i<csz_)
		{
			t=digits_[i]+b.digits_[i]+d;
			if(t>9)
			{
				d=1;
				digits_[i]=t-10;
			}
			else
			{
				d=0;
				digits_[i]=t;
			}
		}
		else
		{
			t=b.digits_[i]+d;
			if(t>9)
			{
				d=1;
				digits_[i]=t-10;
			}
			else
			{
				d=0;
				digits_[i]=t;
			}
			csz_++;
		}
	}
	while(d==1)
	{//beyond the minimum
		if(i<csz_)
		{
			t=digits_[i]+d;
			if(t>9)
			{
				d=1;
				digits_[i]=t-10;
			}
			else
			{
				d=0;
				digits_[i]=t;
			}
		}
		else
		{
			if(csz_==size_)
			{
				Enlarge();
			}
			digits_[i]=1;
			d=0;
			csz_++;
		}
		i++;
	}
}
void BigInt::LowLevelMul(const BigInt &a, const BigInt &b)
{//signs equal
	int64_t i=1, size=size_, d, k;
	const int64_t sz=a.csz_+b.csz_-1;
	while(sz>=size)
	{
		i*=2;
		size*=2;
	}
	Enlarge(i);//now ret is of correct size
	d=0;
	for(k=0; k<sz; k++)
	{
		for(i=0; (i<=k && i<a.csz_); i++)
		{
			if(k-i<b.csz_)
			{
				d+=a.digits_[i]*b.digits_[k-i];
			}
		}
		digits_[k]=d%10;
		d/=10;
	}
	while(d>0)
	{
		if(k==size_)
		{
			Enlarge();
		}
		digits_[k]=d%10;
		d=d/10;
		k++;
	}
	csz_=k;
}
BigInt::BigInt(): size_(base__), csz_(1), sign_(0)
{
	digits_=(char *)malloc(base__);
	digits_[0]=0;
}
BigInt::BigInt(int64_t a)
{
	if(a<0)
	{
		sign_=-1;
		a=-a;
	}
	else
	{
		if(a>0)
		{
			sign_=1;
		}
		else
		{
			sign_=0;
		}
	}
	size_=base__;
	csz_=0;
	digits_=(char *)malloc(size_);
	while(a>0)
	{
		if(csz_==size_)
		{
			Enlarge();
		}
		digits_[csz_]=a%10;
		a/=10;
		csz_++;
	}
	if(csz_==0)
	{
		if(csz_==size_)
		{
			Enlarge();
		}
		digits_[0]=0;
		csz_++;
	}
}
BigInt::BigInt(const BigInt &a): size_(a.size_), csz_(a.csz_), sign_(a.sign_)
{
	digits_=(char *)malloc(size_);
	memcpy(digits_, a.digits_, csz_);
}
BigInt::~BigInt()
{
	if(digits_!=0)
	{
		free(digits_);
	}
}
BigInt BigInt::operator=(const BigInt &a)
{
	if(this==&a)
	{
		return *this;
	}
	if(size_<a.size_)
	{
		if(digits_!=nullptr)
		{
			free(digits_);
		}
		digits_=(char *)malloc(a.size_);
	}
	sign_=a.sign_;
	size_=a.size_;
	csz_=a.csz_;
	memcpy(digits_, a.digits_, csz_);
	return *this;
}
bool BigInt::operator>(const BigInt& a) const
{
	if(BICmp(*this, a)==1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigInt::operator>=(const BigInt& a) const
{
	if(BICmp(*this, a)>=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigInt::operator==(const BigInt& a) const
{
	if(BICmp(*this, a)==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigInt::operator<=(const BigInt& a) const
{
	if(BICmp(*this, a)<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigInt::operator<(const BigInt& a) const
{
	if(BICmp(*this, a)<0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool BigInt::operator!=(const BigInt& a) const
{
	return !(*this==a);
}
BigInt BigInt::operator-() const
{
	BigInt b(*this);
	b.sign_=-b.sign_;
	return b;
}
std::ostream& operator<<(std::ostream &out, const BigInt &a)
{
	if(a.sign_==-1)
	{
		out << '-';
	}
	for(int i=a.csz_-1; i>-1; i--)
	{
		out << (int)a.digits_[i];
	}
	//out << '\0';
	return out;
}
BigInt operator+(const BigInt &a, const BigInt &b)
{
	BigInt ret(a);
	if(a.sign_==0)
	{
		return b;
	}
	if(b.sign_==0)
	{
		return a;
	}
	if(a.sign_==b.sign_)
	{
		ret.LowLevelPlus(b);
	}
	else
	{
		//redirect to operator-
		if(b.sign_<0)
		{
			return a-(-b);
		}
		else
		{
			return b-(-a);
		}
	}
	return ret;
}
BigInt operator-(const BigInt &a, const BigInt &b)
{
	if(a.sign_==0)
	{
		return -b;
	}
	if(b.sign_==0)
	{
		return a;
	}
	if(b.sign_<0)
	{
		return a+(-b);
	}
	if(a.sign_<0)
	{
		return -((-a)+b);
	}
	if(a>=b)
	{
		BigInt ret(a);
		ret.LowLevelMinus(b);
		return ret;
	}
	else
	{
		return -(b-a);
	}
}
BigInt operator*(const BigInt &a, const BigInt &b)
{
	if(a.sign_==0 || b.sign_==0)
	{
		return 0;
	}
	if(a.csz_<b.csz_)
	{
		return b*a;
	}
	BigInt ret(0);
	ret.LowLevelMul(a, b);
	ret.sign_=a.sign_*b.sign_;
	return ret;
}
BigInt operator/(const BigInt &a, const BigInt &b)
{
	if(b.sign_==0)
	{
		throw std::overflow_error("Division by zero"); //
	}
	if(a.sign_==0)
	{
		return 0;
	}
	int64_t i, flag=0, dig;
	BigInt ret(0), d;
	BigInt ra=(a.sign_==1) ? a : -a;
	const BigInt rb=(b.sign_==1) ? b : -b;
	const BigInt one(1);
	while(ra>=rb)
	{ //eliminate rb?
		BigInt tmp(rb);
		if(flag==0)
		{
			ret.sign_=1;
			d=one;
			if(ra.FirstDigit()>rb.FirstDigit())
			{
				tmp.Multen(ra.csz_-rb.csz_);
				d.Multen(ra.csz_-rb.csz_);
			}
			else
			{
				tmp.Multen(ra.csz_-rb.csz_-1);
				d.Multen(ra.csz_-rb.csz_-1);
			}
			i=0;
			while(tmp<=ra)
			{
				ra.LowLevelMinus(tmp);
				i++;
			}
			//ret=ret+d*i; //mb it's faster
			ret.LowLevelPlus(d*i);
			flag=1;
		}
		else
		{
			if(ra.FirstDigit()>rb.FirstDigit())
			{
				tmp.Multen(ra.csz_-rb.csz_);
				dig=ra.csz_-rb.csz_;
			}
			else
			{
				tmp.Multen(ra.csz_-rb.csz_-1);
				dig=(ra.csz_-rb.csz_-1>=0) ? ra.csz_-rb.csz_-1 : 0;
			}
			i=0;
			while(tmp<=ra)
			{
				ra.LowLevelMinus(tmp);
				i++;
			}
			if(i<10)
			{
				ret.digits_[dig]=i;
			}
			else
			{
				int td=i/10+ret.digits_[dig+1];
				ret.digits_[dig]=i%10;
				while(td>9)
				{
					dig++;
					int tr=td%10;
					td=tr/10+ret.digits_[dig+1];
					ret.digits_[dig]=tr;
				}
				ret.digits_[dig+1]=td;
			}
		}
	}
	if(ret.sign_>0)
	{
		ret.sign_=(a.sign_*b.sign_);
	}
	else
	{
		ret.sign_=0;
	}
	//std::cout << ret.csz_ << " size " << int(ret.sign_) << " sign\n";
	return ret;
}
int BICmp(const BigInt &b, const BigInt &a)
{
	if(b.sign_>a.sign_)
	{
		return 1;
	}
	if(b.sign_<a.sign_)
	{
		return -1;
	}
	if(b.sign_==0)
	{
		return 0;
	}
	if(b.sign_==1)
	{
		if(a.csz_<b.csz_)
		{
			return 1;
		}
		if(a.csz_>b.csz_)
		{
			return -1;
		}
		for(int i=b.csz_-1; i>-1; i--)
		{
			if(a.digits_[i]<b.digits_[i])
			{
				return 1;
			}
			if(a.digits_[i]>b.digits_[i])
			{
				return -1;
			}
		}
		return 0;
	}
	else
	{
		if(a.csz_<b.csz_)
		{
			return -1;
		}
		if(a.csz_>b.csz_)
		{
			return 1;
		}
		for(int i=b.csz_-1; i>-1; i--)
		{
			if(a.digits_[i]<b.digits_[i])
			{
				return -1;
			}
			if(a.digits_[i]>b.digits_[i])
			{
				return 1;
			}
		}
		return 0;
	}
}
#endif
