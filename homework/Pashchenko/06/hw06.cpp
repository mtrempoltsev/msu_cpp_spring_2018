#include <algorithm>
#include <stdexcept>
#include <iostream>

class division_by_zero: public std::exception {};
class wrong_operation: public std::exception {};

template <class T>
class Calculator
{

private:
    std::string str{};
    size_t index = 0;

    T get_number();

    T get_operator()
    {
        T value = get_number();
        while(index < str.size() && (str[index] == '*' || str[index] == '/'))
        {
            index++;
            if(str[index - 1] == '*')
                value = value * get_number();
            else
            {
                T number = get_number();
                if(number == T(0))
                    throw division_by_zero();
                value = value / number;
            }
        }
        return value;
    }

    T get_expression()
    {
        T value = get_operator();
        while(index < str.size() && (str[index] == '+' || str[index] == '-'))
        {
            index++;
            if(str[index - 1] == '+')
                value = value + get_operator();
            else
                value = value - get_operator();
        }
        if(index < str.size())
            throw wrong_operation();
        return value;
    }

public:
    T calc(const std::string &st)
    {
        str = st;
        str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
        index = 0;
        return get_expression();
    }
};

template<>
int Calculator<int>::get_number()
{
    size_t tmp_index = 0;
    int number = std::stoi(str.data() + index, &tmp_index);
    index += tmp_index;
    return number;
}

int main(int argc, char **argv)
{
    try
    {
        if(argc != 2)
            throw std::invalid_argument("Invalid number of arguments");

        Calculator<int> calc{};
        std::cout << calc.calc(argv[1]) << std::endl;
    }

    catch(const division_by_zero& error)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    catch(const wrong_operation& error)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    catch(...)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    return 0;
}
