#include <algorithm>
#include <stdexcept>
#include <iostream>

class division_by_zero: public std::exception {};
class wrong_operation: public std::exception {};

template <typename T>

class Calculator
{

private:
    std::string results;
    int number = 0;

    T get_next();

    T get_value()
    {
        T value = get_result();
        while(number < results.size())
            if(results[number] == '+' || results[number] == '-')
        {
                number++;
                if(results[number - 1] == '+')
                    value = value + get_result();
                else
                    value = value - get_result();
        }
        if(number < results.size())
            throw wrong_operation();
        return value;
    }

    T get_result()
    {
        T value = get_next();
        while(number < results.size() && (results[number] == '*' || results[number] == '/'))
        {
            number++;
            if(results[number - 1] == '*')
                value = value * get_next();
            else
            {
                T next = get_next();
                if(next == T(0))
                    throw division_by_zero();
                value = value / next;
            }
        }
        return value;
    }

public:
    T str_to_arr(const std::string &str)
    {
        results = str;
        results.erase(std::remove_if(results.begin(), results.end(), isspace), results.end());
        
        number = 0;
        return get_value();
    }
};

template<>
int Calculator<int>::get_next()
{
    size_t tmp = 0;
    int next = std::stoi(results.data() + number, &tmp);
    number += tmp;
    return next;
}

int main(int argc, char* argv[])
{
    try
    {
        if(argc != 2)
            throw std::invalid_argument("Wrong arguments");

        Calculator<int> calculator{};
        std::cout << calculator.str_to_arr(argv[1]) << std::endl;
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
