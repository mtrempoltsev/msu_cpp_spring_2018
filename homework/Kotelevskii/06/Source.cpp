#include<iostream>
#include<string>
#include<algorithm>
template <class T>
class Calculator
{
	T divider(std::string s) const
	{
		for (size_t i = s.length(); i >= 1; i--)
		{

			if (s[i] == '+')
			{
				return divider(s.substr(0, i)) + mult_div(s.substr(i + 1));
			}
			else if (s[i] == '-' && (s[i - 1] != '*' || s[i - 1] != '/'))
			{
				return divider(s.substr(0, i)) - mult_div(s.substr(i + 1));
			}
		}
		return s[0] == '-' ? -1 * mult_div(s.substr(1)) : mult_div(s);
	}
	T mult_div(std::string s) const
	{
		std::string helper;
		for (size_t i = s.length(); i > 0; i--)
		{
			if (s[i] == '*')
			{
				helper = s.substr(i + 1);
				return mult_div(s.substr(0, i))*(helper[0] == '-' ? -1 * std::stoi(helper.substr(1)) : std::stoi(helper));
			}
			else if (s[i] == '/')
			{
				helper = s.substr(i + 1);
				return mult_div(s.substr(0, i))/(helper[0] == '-' ? -1 * std::stoi(helper.substr(1)) : std::stoi(helper));
			}
		}
		return s[0] == '-' ? -1 * std::stoi(s.substr(1)) : std::stoi(s);
	}
	
	std::string normalization(std::string& s) const
	{
		s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
		for (size_t i = 0; i < s.length() - 1; i++)
		{
			if (s[i] == '-'&&s[i + 1] == '-')
			{
				s[i] = ' ';
				s[i + 1] = '+';
			}
			else if (s[i] == '+'&&s[i + 1] == '-')
			{
				s[i] = ' ';
				s[i + 1] = '-';
			}
		}
		s.erase(std::remove(s.begin(), s.end(), ' '), s.end());
		return s;
	}
	void checker(std::string& s) const
	{
		if (s.find("/0") != std::string::npos)
		{
			throw std::exception{};
		}
		for (size_t i = 0; i < s.length() - 1; i++)
		{
			if (!(s[i] >= '0'&&s[i] <= '9' || s[i]==' ' || s[i] == '+' || s[i] == '-'||
				s[i]=='*'||s[i]=='/'))
			{
				throw std::exception{};
			}
		}
	}
public:
	T calculate(std::string s) const
	{
		checker(s);
		return divider(normalization(s));
	}
};

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cerr << "error\n";
		return 1;
	}
	Calculator<int> a;
	try {
		std::cout << a.calculate(argv[1]) << std::endl;
	}
	catch (...) {
		std::cerr << "error\n";
		return 1;
	}
	return 0;	
}
