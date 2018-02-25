#include<string>

const int MEMORY_ERROR = -112;

class my_exception 
{
    int code;
    std::string report;
public:
    my_exception(int _code, const std::string &_report): code(_code), report(_report)
    {
    }
    int get_code()
    {
        return code;
    }
};
