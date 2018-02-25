#include<string>

namespace error_codes
{
    constexpr int mem_err = -112;
}

class my_exception 
{
    int code;
    const std::string report;
public:
    my_exception(int _code, const std::string &_report): code(_code), report(_report)
    {
    }
    int get_code()
    {
        return code;
    }
    const std::string &get_report() 
    {
        return report;
    }
};
