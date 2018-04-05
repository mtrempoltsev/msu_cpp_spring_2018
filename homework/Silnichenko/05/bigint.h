#ifndef BIGINT_H__
#define BIGINT_H__
#include <iostream>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
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
	void Enlarge();
	void Multen();
	void KillZeroes();
	public:
	BigInt();
	BigInt(int a);
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
void BigInt::Enlarge()
{
	int size=size_*2;
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
void BigInt::Multen()
{
	if(csz_==size_)
	{
		Enlarge();
	}
	memmove(digits_+1, digits_, csz_);
	digits_[0]=0;
	csz_++;
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
BigInt::BigInt(): size_(1), csz_(1), sign_(0)
{
	digits_=(char *)malloc(1);
	digits_[0]=0;
}
BigInt::BigInt(int a)
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
	size_=1;
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
	if(digits_!=nullptr)
	{
		free(digits_);
	}
	sign_=a.sign_;
	size_=a.size_;
	csz_=a.csz_;
	digits_=(char *)malloc(size_);
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
	return out;
}
BigInt operator+(const BigInt &a, const BigInt &b)
{
	BigInt ret(a);
	int64_t sz;
	int64_t i;
	char d=0, t;
	sz=(a.csz_>b.csz_) ? b.csz_ : a.csz_; //minimum
	if(a==0)
	{
		return b;
	}
	if(b==0)
	{
		return a;
	}
	if(a.sign_==b.sign_)
	{
		if(a.csz_<b.csz_)
		{
			return b+a;
		}
		for(i=0; i<sz; i++)
		{
			t=ret.digits_[i]+b.digits_[i]+d;
			if(t>9)
			{
				d=1;
				ret.digits_[i]=t-10;
			}
			else
			{
				d=0;
				ret.digits_[i]=t;
			}
		}
		while(d==1)
		{//beyond the minimum
			if(i<ret.csz_)
			{
				t=ret.digits_[i]+d;
				if(t>9)
				{
					d=1;
					ret.digits_[i]=t-10;
				}
				else
				{
					d=0;
					ret.digits_[i]=t;
				}
			}
			else
			{
				if(ret.csz_==ret.size_)
				{
					ret.Enlarge();
				}
				ret.digits_[i]=1;
				d=0;
				ret.csz_++;
			}
			i++;
		}
	}
	else
	{
		//redirect to operator-
		if(b<0)
		{
			return a-b;
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
	if(a==0)
	{
		return -b;
	}
	if(b==0)
	{
		return a;
	}
	if(b<0)
	{
		return a+b;
	}
	if(a<0)
	{
		return (-a)+b;
	}
	if(a>=b)
	{
		BigInt ret(a);
		int d=0, t;
		int64_t i;
		for(i=0; i<b.csz_; i++)
		{
			t=ret.digits_[i]-b.digits_[i]-d;
			if(t<0)
			{
				ret.digits_[i]=t+10;
				d=1;
			}
			else
			{
				ret.digits_[i]=t;
				d=0;
			}
		}
		while(d>0)
		{
			t=ret.digits_[i]-d;
			if(t<0)
			{
				ret.digits_[i]=t+10;
				d=1;
			}
			else
			{
				ret.digits_[i]=t;
				d=0;
			}
			i++;
		}
		ret.KillZeroes();
		return ret;
	}
	else
	{
		return -(b-a);
	}
}
BigInt operator*(const BigInt &a, const BigInt &b)
{
	if(a==0 || b==0)
	{
		return 0;
	}
	if(a.csz_<b.csz_)
	{
		return b*a;
	}
	int t, d=0;
	int64_t i, j;
	BigInt ret(0);
	for(i=0; i<b.csz_; i++)
	{
		d=0;
		BigInt tmp(a);
		for(j=0; j<a.csz_; j++)
		{
			t=b.digits_[i]*a.digits_[j]+d;
			d=t/10;
			tmp.digits_[j]=t%10;
		}
		if(d>0)
		{
			if(tmp.csz_==tmp.size_)
			{
				tmp.Enlarge();
			}
			tmp.csz_++;
			tmp.digits_[j]=d;
			d=0;
		}
		for(j=0; j<i; j++)
		{
			tmp.Multen();
		}
		ret=ret+tmp;
	}
	ret.sign_=a.sign_*b.sign_;
	return ret;
}
BigInt operator/(const BigInt &a, const BigInt &b)
{
	if(b==0)
	{
		throw 0; //std::divbyzero
	}
	if(a==0)
	{
		return 0;
	}
	BigInt ret(0);
	BigInt ra=(a>0) ? a : -a;
	BigInt rb=(b>0) ? b : -b;
	while(ra>=rb)
	{
		ret=ret+1;
		ra=ra-rb;
	}
	if(ret>0)
	{
		ret.sign_=(a.sign_*b.sign_);
	}
	else
	{
		ret.sign_=0;
	}
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
