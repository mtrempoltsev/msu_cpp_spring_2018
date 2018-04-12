#include <iostream>
#include <string>
#include <stdexcept>

template<typename type>
class Calculator
{
    type ans_ = 0;

    std::string::const_iterator find_unarn_minus(std::string::const_iterator start, std::string::const_iterator last)
    {
        for(auto i = start; i!= last; ++i){
            if(*i == '-')
                return i;
        }
        return last;
    }

    type to_num(std::string::const_iterator start, std::string::const_iterator last)
    {
        type ans = 0;
        if(start == last)
            throw std::invalid_argument("Empty value");
        for(auto i = start; i!= last; ++i){
            if(*i == ' ')
                continue;
            else if(!(*i >= '0' && *i <= '9'))
                throw std::invalid_argument("Unknown symbol");
            else
                ans = ans * 10 + *i - 0x30;
        }
        return ans;
    }

    std::string::const_iterator find_last_minus_plus(std::string::const_iterator start, std::string::const_iterator last)
    {
        bool was_prev_op = true;
        auto ans = last;
        for(auto i = start; i != last; ++i){
            if(*i == '+' || (*i == '-' && !was_prev_op))
                ans = i;
            if(*i == '-' || *i == '+' || *i == '*' || *i == '/')
                was_prev_op = true;
            if(*i >= '0' && *i <= '9')
                was_prev_op = false;
        }
        return ans;
    }

    std::string::const_iterator find_last_mul_div(std::string::const_iterator start, std::string::const_iterator last)
    {
        bool was_prev_op = true;
        auto ans = last;
        for(auto i = start; i != last; ++i){
            if(*i == '/' || *i == '*')
                ans = i;
        }
        return ans;
    }

    type mul_div(std::string::const_iterator start, std::string::const_iterator last)
    {
        auto i = find_last_mul_div(start, last);
        if(i != last){
            if(*i == '*'){
                return mul_div(start, i) * to_num(i + 1, last);
            }
            else if(*i == '/'){
                auto num = to_num(i + 1, last);
                if(num == 0)
                    throw std::invalid_argument("Division by zero");
                return mul_div(start, i) / num;
            }
        }

        i = find_unarn_minus(start, last);
        if(i != last)
            return -to_num(i + 1, last);
        return to_num(start, last);
    }

    type parser(std::string::const_iterator start, std::string::const_iterator last)
    {
        auto i = find_last_minus_plus(start, last);
        if(i != last){
            if(*i == '+'){
                return parser(start, i) + mul_div(i + 1, last);
            }
            else if(*i == '-'){
                return parser(start, i) - mul_div(i + 1, last);
            }
        }
        return mul_div(start, last);
    }

public:
    Calculator(): ans_(0){}

    type calculate(const char* str)
    {
        std::string expr(str);
        ans_ = parser(expr.begin(), expr.end());
        return ans_;
    }
};

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "error\n";
        return 1;
    }

    try
    {
        Calculator<int> c;
        std::cout << c.calculate(argv[1]) << std::endl;
    }
    catch(std::invalid_argument&)
    {
        std::cerr << "error\n";
        return 1;
    }
    return 0;
}
