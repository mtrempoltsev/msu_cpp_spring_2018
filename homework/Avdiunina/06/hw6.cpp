#include <algorithm>
#include <stdexcept>
#include <iostream>
#include <iterator>
#include <vector>
#include <sstream>
#include <string>

class division_by_zero: public std::exception {};
class wrong_operation: public std::exception {};

template <typename T>

class Calculator
{

private:
    std::vector<std::string> results;
    int number = 0;
    std::string plus = "+";
    std::string minus = "-";
    std::string multiplier = "*";
    std::string divider = "/";

    T get_value()
    {
        T value = get_result();
        while(number < results.size())
        {
            if (results[number] == plus || results[number] == minus) {
                number++;
                if (results[number - 1] == plus)
                    value = value + get_result();
                else
                    value = value - get_result();
            }
        }
        if(number < results.size())
            throw wrong_operation();
        return value;
    }


    T get_result()
    {
        T value = get_next();
        while(number < results.size())
        {
            if (results[number] == multiplier || results[number] == divider) {
                number++;
                if (results[number - 1] == multiplier)
                    value = value * get_next();
                else {
                    T next = get_next();
                    if (next == T(0))
                        throw division_by_zero();
                    value = value / next;
                }
            }
        }
        return value;
    }

    T get_next()
    {
        std::string* it = results.data() + number;
        auto next = std::stoi(*it);
        number ++;
        return next;

    }

public:

    T str_to_arr(const std::string &str)
    {
        std::istringstream iss(str);
        std::vector<std::string> results((std::istream_iterator<std::string>(iss)),
                                         std::istream_iterator<std::string>());

        number = 0;
        return get_value();
    }


};

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
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    catch(const wrong_operation& error)
    {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    catch(...)
    {
        std::cerr << "Error!" << std::endl;
        return 1;
    }
    return 0;
}
