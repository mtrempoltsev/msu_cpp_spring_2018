/*
*  Кaлькулятор. Пример из учебника "С++ Programming Language" (основа).
*  Применяется алгоритм "рекурсивный спуск" (recursive descent).
*  (Примечание: калькулятор может работать с выражениями. Например, если
*  на входе подать r = 2.5; area = pi * r * r; то на выходе будет
*  2.5; 19.635)
*/

#include <cctype>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <memory>
#include <exception>

template <typename T>
class Calc
{
private:

    using TExpr = std::unique_ptr<std::stringstream>;

    enum class Token : char
    {
        END,
        NUM,
        PLS = '+',
        MIN = '-',
        DIV = '/',
        MUL = '*'
    };

    TExpr input;
    Token current = Token::END;
    T value;

    Token get_token ()
    {
        char ch;
        do
        {
            if (!input->get (ch))
                if (input->eof ())
                    return current = Token::END;
                else
                    throw std::invalid_argument("Read T from string exception");
        } while (isspace (ch));
        switch (ch)
        {
        case 0:
            return current = Token::END;
        case (char) Token::PLS:
        case (char) Token::MIN:
        case (char) Token::MUL:
        case (char) Token::DIV:
            return current = Token (ch);
        default:
            input->putback (ch);
            *input >> value;
            return current = Token::NUM;
        }
    }

    T prim (bool get)
    {
        if (get)
            get_token ();
        switch (current)
        {
        case Token::MIN:
            return -prim (true);
        case Token::NUM:
        {
            T v = value;
            get_token ();
            return v;
        }
        default:
            throw std::invalid_argument ("Unexpected symbol");
            return T (0);
        }
    }

    T term (bool get)
    {
        T left = prim (get);
        while (true)
        {
            switch (current)
            {
            case Token::MUL:
                left *= prim (true);
                break;
            case Token::DIV:
            {
                T d = prim (true);
                if (d == T (0))
                    throw std::invalid_argument ("Division by zero");
                left /= d;
                break;
            }
            default:
                return left;
            }
        }
    }

    T expr (bool get)
    {
        T left = term (get);

        while (true)
        {
            switch (current)
            {
            case Token::PLS:
                left += term (true);
                break;
            case Token::MIN:
                left -= term (true);
                break;
            default:
                return left;
            }
        }
    }

public:

    Calc (const std::string & str) : input (std::make_unique<std::stringstream> (str)) {}

    T Eval ()
    {
        get_token ();
        if (current == Token::END)
            return T (0);
        return expr (false);
    }
};

int main (int argc, char * argv[])
{
    if (argc == 1)
    {
        std::cout << "error\n";
        return 1;
    }
    if (argc == 2)
    {
        Calc<int> calc = Calc<int> (std::string (argv[1]));
        try
        {
            std::cout << calc.Eval ();
            return 0;
        }
        catch (std::exception & e)
        {
            std::cout << "error\n";
            return 1;
        }
    }

    std::cout << "error\n";
    return 1;
}
