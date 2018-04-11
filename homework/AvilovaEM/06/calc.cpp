#include <iostream>
#include <unordered_map>
#include <limits>

std::unordered_map<std::string, double> constants =
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };

using namespace std;

enum class Token // enum class cannot be cast to type int
{
    Invalid, // 0
    Minus, // 1
    Plus, // 2
    Mul, // 3
    Div, // 4
    Number, // 5
    End, // 6
    Constant, //7
    LBracket,
    RBracket
};

template <class T>
struct NumericTraits
{};

template <>
struct NumericTraits<int>
{
    constexpr static int max = std::numeric_limits<int>::max();
    constexpr static int min = std::numeric_limits<int>::min();
};

template <>
struct NumericTraits<long>
{
    constexpr static long max = std::numeric_limits<long>::max();
    constexpr static long min = std::numeric_limits<long>::min();
};

template <>
struct NumericTraits<double>
{
    constexpr static double max = std::numeric_limits<double>::max();
    constexpr static double min = std::numeric_limits<double>::min();
};

template <class T>
struct Parser
{};

template <>
struct Parser<int>
{
  static bool parse(const char *&text, int &value)
  {
    long tmp = atol(text);
    if ((tmp < NumericTraits<int>::min) || (tmp > NumericTraits<int>::max))
      return false;
      
    value = tmp;
    return true;
  }
};

template <>
struct Parser<long>
{
  static bool parse(const char *&text, long &value)
  {
    double tmp = strtold(text, NULL);
    std::cout << tmp <<std::endl;
    std::cout << NumericTraits<long>::min <<std::endl;
    if ((tmp < NumericTraits<long>::min) || (tmp > NumericTraits<long>::max))
      return false;
    
    value = tmp;
    return true;
  }
};

template <>
struct Parser<double>
{
  static bool parse(const char *&text, double &value)
  {
    long double tmp = strtold(text, NULL);
    if ((tmp < NumericTraits<double>::min)||(tmp > NumericTraits<double>::max))
      return false;
    
    value = tmp;
    return true;
  }
};

template <class T, class ParserT>
class Calculator
{
public:
    Token token; 
    const char *prev; 
    int opened_brackets = 0;
    Calculator(const char *&text)
    {
      prev = text;
      getToken(text);
    }

   int isEnd(void)
    {
       return (token == Token::End);
    }
 
    int isInvalid(void)
    {
       return (token == Token::Invalid);
    }

    int isConstant(void)
    {
        return(token == Token::Constant);
    }

    void getToken(const char *&text)
    {
        while (const auto c = *text++)
        {
            prev = text-1;
            switch (c)
            {
                case ' ': continue;
                case '-': 
                    token = Token::Minus; 
                    return;
                case '+': 
                    token = Token::Plus; 
                    return;
                case '*': 
                    token = Token::Mul; 
                    return;
                case '/': 
                    token = Token::Div; 
                    return;
                case '(': 
                    token = Token::LBracket; 
                    return;
                case ')': 
                    token = Token::RBracket; 
                    return;
            }
            
            if (((c >= '0') && (c <= '9')) || (c == '.'))
            {
                for (auto c = *text; ((c >= '0') && (c <= '9')) || (c == '.');)
                {
                    text++;
                    c = *text;
                }
           
                token = Token::Number;
                return;
            }
            else 
                throw "error";
            
            if (isalpha(c))
            {
                for (auto c = *text; isalpha(c);)
                { 
                    text++;
                    c = *text;
                }
                
                token = Token::Constant;
                return;
            }
            
            token = Token::Invalid;
            return;
        }
        token =  Token::End;
        return;
    }


    T getNumber(const char *&text)
    {
      T value;
      if (!ParserT::parse(text,value))
          throw "error";
        
      return value;
    }

    T prim(const char *&text)
    {

        getToken(text);
        switch (token)
        {
            case Token::Number:
            {
                T number = getNumber(prev);
                getToken(text);
                if (isInvalid() || isConstant()) 
                    throw "error";
                    
                return number;
            }
            case Token::Minus:
            {
                T number = prim(text);
                return -number;
            }
            case Token::Constant:
            {
                auto name = std::string(prev, text - prev);
                auto iter = constants.find(name);

                if (iter == constants.end())
                    throw "error";

                int number = constants[name];

                getToken(text);
                if (isInvalid()) 
                    throw "error";

                return number;
            }
            case Token::LBracket: 
            {
                opened_brackets++;
                int result = expr(text);
    				if (token != Token::RBracket) 
    					throw "error";
    						
                opened_brackets--;
    				getToken(text);
    				return result;
            }
            default: 
                throw "error";
        }
    }

    T term(const char *&text)
    {
        T left = prim(text); 
        while(1)
        {
            switch (token)
            {
                case Token::Mul:
                {
                    left *= prim(text);
                    break;
                }
                case Token::Div:
                {
                    T divisor = prim(text);
                    if (divisor == 0) 
                        throw "error";
                    left /= divisor;
                    break;
                }
                case Token::RBracket: 
                {
                    if (!opened_brackets)
                          throw "error";
                }
                default: return left;
            }
        }
    }

    T expr(const char *&text)
    {
        T left = term(text); 
        while(1)
        {
            switch (token)
            {
                case Token::Plus:
                {
                    left += term(text);
                    break;
                }
                case Token::Minus:
                {
                    left -= term(text);
                    break;
                }
                default: return left;
            }
        }
    }
};

int main(int argc, char *argv[])
{
    const char *text = "1 + 2";

    if (argc == 1)
    {
      std::cerr << "error";
      return 1;
    }
    
    text = argv[1];
    auto prev = text;

    Calculator<int, Parser<int> > calc  = Calculator<int, Parser<int> >(text);

    if (calc.isEnd())
    {
        std::cerr << "error";
        return 1;
    }
    if (!calc.isInvalid())
    {
        text = prev;
        calc.prev = prev;
        try
        {
            std::cout << calc.expr(text) << std::endl;
        }
        catch (const char* s)
        {
            std::cerr << "error";
            return 1;
        }
    } 
    else 
    {
        std::cerr << "error";
        return 1;
    }
    return 0;
}
