#include<string>
#include<iostream>
#include<stdexcept>
#include <type_traits>

class CalcError : std::exception {};
template <typename T>
class Calc
{
    private:
        T AddOrSub(std::string::const_iterator start, std::string::const_iterator finish)
        {
            if(start == finish)
                return 0;
            bool flag = false;
            for (auto it = finish - 1; it != start - 1; --it)
            {
                if(*it == '+'){
                    if(flag)
                        return AddOrSub(start,it) + AddOrSub(it + 1, finish);
                    else
                        throw CalcError();
                }
                if(*it == '-'){
                    if(flag)
                        return AddOrSub(start,it) - AddOrSub(it + 1, finish);
                    else
                        throw CalcError();
                }
                if(*it == '*' || *it == '/')
                    flag = false;
                if(*it >= '0' && *it <= '9')
                    flag = true;
            }
            return MulOrDiv(start,finish);
        }

        T MulOrDiv(std::string::const_iterator start, std::string::const_iterator finish)
        {
            bool flag = false;
            for(auto it = finish - 1; it != start-1; --it)
            {
                if(*it == '*'){
                    if(flag)
                        return MulOrDiv(start,it) * MulOrDiv(it + 1, finish);
                    else
                        throw CalcError();
                }
                if(*it == '/'){
                    if(!flag)
                        throw CalcError();
                    T a = MulOrDiv(it + 1, finish);
                    if(a == 0)
                        throw CalcError();
                    return MulOrDiv(start,it) / a;
                }
                if(*it >= '0' && *it <= '9')
                    flag = true;
            }
            return print(start, finish);
        }

        T print(std::string::const_iterator start, std::string::const_iterator finish)
        {
            throw CalcError();
        }

        /*template<long long>
        long long print(std::string::const_iterator start, std::string::const_iterator finish)
        {
            return std::stoll(std::string(start, finish));
        }*/

        std::string Clearing(const std::string& str) const
        {
            std::string mid = "";
            for (auto i:str)
                if(i != ' ' && i != '\t')
                    mid += i;
            std::string out = "";
            for (int i = 0; i < mid.size(); ++i){
                if(i>0 && mid[i] == '-' && mid[i-1] == '-')
                    out+='+';
                else if(i>0 && mid[i] == '-' && mid[i-1] == '+')
                    out+='-';
                else if(!(i + 1 < mid.size() && (mid[i] == '-' && mid[i+1] == '-') || (mid[i] == '+' && mid[i+1] == '-' )))
                    out+=mid[i];
            }
            return out;
        }

        void Check(const std::string& str) const
        {
            for(auto i:str)
                if(!((i >= '0' && i <='9') || i == '+' || i == '-' || i == '*' || i =='/' || i == ' ' || i == '\t'))
                    throw CalcError();
        }
    public:
        T Calculate(const std::string& str)
        {
            Check(str);
            std::string str2 = Clearing(str);
            return AddOrSub(str2.begin(), str2.end());
        }
};

template<>
int Calc<int>::print(std::string::const_iterator start, std::string::const_iterator finish)
{
    return std::stoi(std::string(start, finish));
}

template<>
long long Calc<long long>::print(std::string::const_iterator start, std::string::const_iterator finish)
{
    return std::stoll(std::string(start, finish));
}
int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "error\n";
        return 1;
    }
    Calc<long long> c;
    try {
        std::cout << c.Calculate(argv[1]) << std::endl;
    }
    catch(CalcError& error) {
        std::cerr << "error\n";
        return 1;
    }
    return 0;
}
