#include <iostream>
#include <cctype>
#include <sstream>
#include <string>
#include <memory>
typedef std::shared_ptr<std::basic_istream<char>> point;
template <class T>
class calculator
{
    T number_value;
    //T result;

    char get_token(point input, char& curr_token)
    {

        char ch;
        do {    // Пропустить все пробельные символы кроме '\n'.
            if (!input->get(ch))
            {
                return curr_token = 'E'; // Завершить работу калькулятора.
            }
        } while (ch != '\n' && isspace(ch));

        switch (ch)
        {
            case 0: // При вводе символа конца файла, завершить работу калькулятора.
                return curr_token = 'E';
            case '*':
                return curr_token = '*';
            case '/':
                return curr_token = '/';
            case '+':
                return curr_token = '+';
            case '-':
                return curr_token = '-';
            case '(':
                return curr_token = '(';
            case ')':
                return curr_token = ')';
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case '.':
                input->putback(ch); // Положить назад в поток...
                *input >> number_value; // И считать всю лексему.
                return curr_token = 'N';
            default:
                throw "Bad Token";
        }

    }

    // prim() - обрабатывает первичные выражения.
    T prim(point input, bool get, char& curr_token)
    {
        if (get)
        {
            get_token(input, curr_token);
        }

        switch (curr_token)
        {
            case 'N':
            {
                T v = number_value;
                get_token(input, curr_token);
                return v;
            }
            case '-':
                return -prim(input, true, curr_token);
            case '(':
            {
                T e = expr(input, true, curr_token);
                if (curr_token != ')')
                {
                    throw "')' expected";
                }
                get_token(input, curr_token);
                return e;
            }
            default:
                throw "primary expected";
        }
    }

// term() - умножение и деление.
    T term(point input, bool get, char& curr_token )
    {
        T result = prim(input, get, curr_token);

        for ( ; ; )
        {
            switch (curr_token)
            {
                case '*':
                    result *= prim(input, true, curr_token);
                    break;
                case '/':
                    if (T d = prim(input, true, curr_token))
                    {
                        result /= d;
                        break;
                    }
                    throw "Divide by 0";
                default:
                    return result;
            }
        }
    }

// expr() - сложение и вычитание.
    T expr(point input, bool get, char& curr_token)
    {
        T result = term(input, get, curr_token);

        for ( ; ; )
        {
            switch (curr_token)
            {
                case '+':
                    result += term(input, true, curr_token);
                    break;
                case '-':
                    result -= term(input, true, curr_token);
                    break;
                default:
                    return result;
            }
        }
    }

    void calculus(point input)
    {
        char curr_token;
        try {

            while (*input) {
                get_token(input, curr_token);
                if (curr_token == 'E') {
                    break;
                }

                // Снимает ответственность expr() за обработку пустых выражений.
                if (curr_token == 'L') {
                    continue;
                }

                // expr() -> term() -> prim() -> expr() ...
                std::cout << expr(input, false, curr_token) << std::endl;
            }
        }
        catch (const char* arr)
        {
            error(arr);
            throw;
        }
    }

    void error(const std::string& error_message)
    {
        std::cerr << "error" << std::endl;
    }
public:
    calculator(point input)
    {
        calculus(input);
    }
};

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout << "error" << std::endl;
        return 1;
    }
    auto input = std::shared_ptr<std::istream>(new std::istringstream(argv[1]));
    try {
        calculator<int> a(input);
    }
    catch(...)
    {
        return 1;
    }
    return 0;
}