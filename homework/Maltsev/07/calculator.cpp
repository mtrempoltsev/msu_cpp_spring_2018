#include <iostream>
#include <string>
#include <vector>

enum type_of_lex 
{
    LEX_NULL,
    LEX_PLUS, LEX_MINUS, LEX_SLASH, LEX_TIMES, LEX_UMINUS,
    LEX_NUM
};
std::string lexem[] = {
        "LEX_NULL",
        "LEX_PLUS", "LEX_MINUS", "LEX_SLASH", "LEX_TIMES", "LEX_UMINUS",
        "LEX_NUM"
};
template  <class T>
class Lex 
{
private:

    type_of_lex t_lex_;
    T v_lex_;
public:
    explicit Lex(const type_of_lex t_lex = LEX_NULL, const int v_lex = 0):
            t_lex_(t_lex),
            v_lex_(v_lex)
    {}
    Lex(const Lex& copied)
    {
        t_lex_ = copied.t_lex_;
        v_lex_ = copied.v_lex_;
    }
    Lex(Lex&& moved) noexcept
    {
        t_lex_ = moved.t_lex_;
        v_lex_ = moved.v_lex_;
        moved.t_lex_ = LEX_NULL;
        moved.v_lex_ = 0;
    }
    Lex &operator=(const Lex &copied)
    {
        if (this == &copied) {
            return *this;
        }
        t_lex_ = copied.t_lex_;
        v_lex_ = copied.v_lex_;
        return *this;
    }

    Lex &operator=(Lex &&moved) noexcept
    {
        if (this == &moved) {
            return *this;
        }
        t_lex_ = moved.t_lex_;
        v_lex_ = moved.v_lex_;
        moved.t_lex_ = LEX_NULL;
        moved.v_lex_ = 0;
        return  *this;
    }
    type_of_lex get_type()
    {
        return t_lex_;
    }
    int get_value()
    {
        return v_lex_;
    }
    ~Lex() = default;
    friend std::ostream &operator<<(std::ostream &os, const Lex &lex) {
        if (lex.t_lex_ == LEX_NUM)
        {
            os << lex.v_lex_;
        }
        else {
            os << lexem[lex.v_lex_];
        }
        return  os;
    }
};
template <class T>
std::vector<Lex<T>> scaner(const std::string& s)
{
    if (s.empty())
        throw "String is empty";
    std::vector<Lex<T>> res;
    T digit;
    size_t j;
    char curr_char;
    std::string TD = " +-/*";
    type_of_lex dlms[] = {LEX_NULL, LEX_PLUS, LEX_MINUS, LEX_SLASH, LEX_TIMES,};
    enum state {H, NUMB};
    state  Curr_State = H;
    size_t i = 0;
    while( i < s.size())
    {
        curr_char = s[i];
        switch(Curr_State)
        {
            case H:
                if(curr_char == ' ' ||
                   curr_char == '\n' ||
                   curr_char == '\r' ||
                   curr_char == '\t')
                {
                    i++;
                }
                else if (std::isdigit(curr_char))
                {
                    digit = curr_char - '0';
                    ++i;
                    if (i == s.size())
                    {
                        res.emplace_back(Lex<T>(LEX_NUM, digit));
                    }
                    Curr_State = NUMB;
                }
                else
                {
                    j = TD.find(curr_char);
                    if (j != std::string::npos)
                    {
                        res.emplace_back(Lex<T>(dlms[j], j));
                        i++;
                    } else
                    {
                        throw s[i];
                    }
                }
                break;
            case NUMB:
                if(std::isdigit(curr_char))
                {
                    digit = digit * 10 + (curr_char - '0');
                    ++i;
                    if (i == s.size())
                    {
                        res.emplace_back(Lex<T>(LEX_NUM, digit));
                    }
                } else
                {
                    Curr_State = H;
                    res.emplace_back(Lex<T>(LEX_NUM, digit));
                }
                break;
        }
    }
    return res;
}

//std::vector<Lex> parser(const std::string& string)
//{
//    std::vector<Lex> scan_string = scaner(string);
//
//}
template <class T>
class Parser {
private:
    std::vector<Lex<T>> scan_string;
    std::vector<Lex<T>> op;
    std::vector<T> arg;
    size_t curr_lex;
    type_of_lex curr_type;
    void parsing();
    void P();
    void M();
    void F();
    void execute()
    {
        T t2 = arg.back();
        arg.pop_back();
        T t1 = arg.back();
        arg.pop_back();
        type_of_lex oper = op.back().get_type();
        op.pop_back();
        switch (oper)
        {
            case LEX_MINUS:
                arg.push_back(t1 - t2);
                break;
            case LEX_TIMES:
                arg.push_back(t1 * t2);
                break;
            case LEX_SLASH:
                if (t2 == 0)
                {
                    throw "Divide by zero";
                }
                arg.push_back(t1 / t2);

                break;
            case LEX_PLUS:
                arg.push_back(t1 + t2);
                break;
            default:
                break;
        }
    }
public:
    explicit Parser(const std::string& string):
        curr_lex(0),
        curr_type(LEX_NULL)
    {
        scan_string = scaner<T>(string);
        parsing();
    }
    Parser(const Parser&) = delete;
    Parser& operator=(const Parser&) = delete;
    Parser(Parser&&) = delete;
    Parser& operator=(Parser&&) = delete;

    T get_res()
    {
        return arg[0];
    }
    ~Parser() = default;
};
template <class T>
void Parser<T>::parsing()
{
    curr_lex = 0;
    curr_type = scan_string[curr_lex].get_type();
    P();
}
template <class T>
void Parser<T>::P()
{
    M();
    while (curr_type == LEX_PLUS ||
           curr_type == LEX_MINUS)
    {
        op.push_back(scan_string[curr_lex]);
        curr_lex++;
        curr_type = scan_string[curr_lex].get_type();
        M();
        execute();
    }
}
template <class T>
void Parser<T>::M()
{
    F();
    while (curr_type == LEX_TIMES ||
           curr_type == LEX_SLASH)
    {
        op.push_back(scan_string[curr_lex]);
        curr_lex++;
        curr_type = scan_string[curr_lex].get_type();
        F();
        execute();

    }
}
template <class T>
void Parser<T>::F()
{
    if(curr_type == LEX_NUM)
    {
        arg.push_back(scan_string[curr_lex].get_value());
        curr_lex++;
        curr_type = scan_string[curr_lex].get_type();
    } else if(curr_type == LEX_MINUS)
    {
        curr_lex++;
        curr_type = scan_string[curr_lex].get_type();
        F();
        T a = arg.back();
        arg.pop_back();
        arg.push_back(-a);
    } else
    {
        throw scan_string[curr_lex];
    }
}
template <class T>
class Calculator
{
public:
    T get_res(const std::string& string)
    {
        Parser<T> calc(string);
        return calc.get_res();
    }
};
int main(int argc, char* argv[])  {
    if (argc != 2) {
        std::cerr << "ERROR argc != 2";
        return 1;
    }

    Calculator<int> calculator;
    try {
        std::cout << calculator.get_res(argv[1]);
    }
    catch  (const char c)
    {
        std::cerr << "Unknown character: " << c << std::endl;
        return 1;
    }
    catch  (const char* string)
    {
        std::cerr << string << std::endl;
        return 1;
    }
    catch  (const Lex<int>& lex)
    {
        std::cerr << "ERROR lex: " << lex << std::endl;
        return 1;
    }
    catch (...)
    {
        std::cerr << "UNknown error";
        return 1;
    }
    return 0;
}