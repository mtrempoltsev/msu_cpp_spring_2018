#include <string>
#include <iostream>
namespace signs
{
	const int PLUS=1;
	const int MINUS=2;
	const int MUL=3;
	const int DIV=4;
	const int UMIN=5;
}
/*Exceptions begin*/
class CalcException
{
	private:
	const std::string cause_;
	public:
	CalcException();
	CalcException(const char *cause);
	~CalcException();
	void Handle();
};
CalcException::CalcException(): cause_("nothing")
{
}
CalcException::CalcException(const char *cause): cause_(cause)
{
}
CalcException::~CalcException()
{
}
void CalcException::Handle()
{
	std::cout << "error" << std::endl;
}

/*Exceptions end*/
template <class T>
class CalcExpr
{
	private:
	const std::string expr_;
	T Multiply(); //counts value of expressions w/o +/-
	T Evaluate(); //makes number out of string
	public:
	CalcExpr();
	CalcExpr(const std::string source); //constructs from string
	T CountValue(); //counts value of any expression 
};
int GetABreak(const std::string str, int *val);
int GetMBreak(const std::string str, int *val);
bool IsInteger(char a);
std::string KillSpaces(std::string a);
template <class T>
CalcExpr<T>::CalcExpr(const std::string source): expr_(source)
{
}
bool IsInteger(char a)
{
	if(a<='9' && a>='0')
	{
		return true;
	}
	return false;
}
template <>
int CalcExpr<int>::Evaluate()
{
	if(expr_.size()<1)
	{
		throw CalcException("Some term is of zero length");
	}
	if(!(expr_[0]=='-') && !(IsInteger(expr_[0])))
	{
		throw CalcException("Some term is not a number!");
	}
	for(int i=1; i<expr_.size(); i++)
	{
		if(!(IsInteger(expr_[i])))
		{
			throw CalcException("Some term is not a number!");
		}
	}
	return std::stoi(expr_);
}
template <class T>
T CalcExpr<T>::Multiply()
{
	T ret, tret;
	int b, bval; 
	b=GetMBreak(expr_, &bval);
	if(b==-1)
	{
		try
		{
			ret=Evaluate(); //unary minus or plain number or parsing error
		}
		catch(std::invalid_argument)
		{
			throw CalcException("Can't convert some term");
		}
		catch(std::out_of_range)
		{
			throw CalcException("Some of numbers is too big");
		}
	}
	else
	{
		if(bval==signs::MUL)
		{
			ret=CalcExpr(std::string(expr_, 0, b)).CountValue()*CalcExpr(std::string(expr_, b+1, std::string::npos)).CountValue();
		}
		if(bval==signs::DIV)
		{
			tret=CalcExpr(std::string(expr_, b+1, std::string::npos)).CountValue();
			if(tret==0)
			{
				throw CalcException("Division by zero!");
			}
			ret=CalcExpr(std::string(expr_, 0, b)).CountValue()/tret;
		}
	}
	return ret;
}
template <class T>
T CalcExpr<T>::CountValue()
{
	/*split string into smaller parts*/
	T ret;
	int b, bval; 
	b=GetABreak(expr_, &bval);
	if(b==-1)
	{
		ret=Multiply();
	}
	else
	{
		if(bval==signs::PLUS)
		{
			ret=CalcExpr(std::string(expr_, 0, b)).CountValue()+CalcExpr(std::string(expr_, b+1, std::string::npos)).CountValue();
		}
		if(bval==signs::MINUS)
		{
			ret=CalcExpr(std::string(expr_, 0, b)).CountValue()-CalcExpr(std::string(expr_, b+1, std::string::npos)).CountValue();
		}
	} 
	return ret;
}
int GetABreak(const std::string str, int *val)
{//finds first break (+/-) 
	int i=str.size()-1;
	int b=0;
	while(i>b)
	{
		if(str[i]=='+')
		{
			*val=signs::PLUS;
			return i;
		}
		if(str[i]=='-')
		{
			if(i>0 && !(str[i-1]=='+' || str[i-1]=='-' || str[i-1]=='*' || str[i-1]=='/'))
			{
				*val=signs::MINUS;
				return i;
			}
		}
		i--;
	}
	return -1;	
}
int GetMBreak(const std::string str, int *val)
{//finds first break (* or /) 
	int i=str.size()-1;
	int b=0;
	while(i>b)
	{
		if(str[i]=='*')
		{
			*val=signs::MUL;
			return i;
		}
		if(str[i]=='/')
		{
			*val=signs::DIV;
			return i;
		}
		i--;
	}
	return -1;
}
std::string KillSpaces(std::string a)
{
	std::string ret;
	for(int i=0; i<a.size(); i++)
	{
		if(a[i]!=' ')
		{
			ret+=a[i];
		}
	}
	return ret;
}
int main(int argc, char **argv)
{
	int res=0;
	if(argc!=2)
	{
		std::cout << "error";
		return 1;
	}
	std::string a(argv[1]);
	//here we kill spaces
	std::string c=KillSpaces(a);
	CalcExpr<int> b(c);
	try
	{
		res=b.CountValue();
	}
	catch(...)
	{
		std::cout << "error";
		return 1;
	}
	std::cout << res << std::endl;
	return 0;
}
