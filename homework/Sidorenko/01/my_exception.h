#include<string>
#define MEMORY_ERROR -111

class my_exception 
{
private:
    int code;
    std::string report;
public:
    my_exception(int _code, std::string _report)
    {
        code = _code;
        report = _report;
    }
    int get_code()
    {
        return code;
    }
};
