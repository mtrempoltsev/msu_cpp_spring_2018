#include <iostream>
#include <string.h>
#include <sstream>
#include <algorithm>


int get_priority(const std::string& bin_op) {
    if (bin_op == "+") return 1;
    if (bin_op == "-") return 1;
    if (bin_op == "*") return 2;
    if (bin_op == "/") return 2;
    return 3;
}

class Parser {
public:
    Parser(const char* input) : input(input) {}
    const char* input;
    int get_min_priority(int start, int stop)
    {
        auto temp=input;

        int min_p=3;
        int nomer=start;
        int s=0;
        int i;
        int pred=0;

        for(i=start;i<=stop;i++)
        {
            if(std::isspace(temp[i])==0)
            {
                s=get_priority(parse_term(temp+i, pred));

                if(s<=min_p)
                {
                    min_p=s;
                    nomer=i;
                }
                if(s==3)
                {
                    i=i+parse_term(temp+i, pred).length()-1;
                }
                pred=s;
            }
        }
        return nomer;
    }

    std::string parse_term(const char *in, int s) {
        while (std::isspace(*in)) ++in;
        if (std::isdigit(*in)) {
            std::string number;
            while (std::isdigit(*in)) number.push_back(*in++);
            return number;
        }
        switch (*in++) {
        case('+'):
            return "+";
        case('-'):
            if(std::isdigit(*in)!=0 && s==3)
            {
                return "-";
            }
            if (std::isdigit(*in)) {
                std::string number;
                number.push_back('-');
                while (std::isdigit(*in)) number.push_back(*in++);
                return number;

            }
            return "-";
        case('*'):
            return "*";
        case('/'):
            return "/";
        }
        throw std::runtime_error("unknown character");

        return "";
    }

    std::string parse_term1(const char *in) {
        while (std::isspace(*in)) ++in;
        if (std::isdigit(*in)) {
            std::string number;
            while (std::isdigit(*in)) number.push_back(*in++);
            return number;
        }
        switch (*in++) {
        case('+'):
            return "+";
        case('-'):
            if(std::isdigit(*(in-2))!=0 && std::isdigit(*in)!=0)
            {
                return "-";
            }
            if (std::isdigit(*in)) {
                std::string number;
                number.push_back('-');
                while (std::isdigit(*in)) number.push_back(*in++);
                return number;

            }
            return "-";
        case('*'):
            return "*";
        case('/'):
            return "/";
        }
        throw std::runtime_error("unknown character");

        return "";
    }


};


template <class T>
class Calc
{
public:
    Parser p;
    Calc(const char* argv) : p(argv) {}
    T equal(int start, int stop)
    {
        int s=0;
        s=p.get_min_priority(start, stop);
        if(p.parse_term1(p.input+s)=="+")
        {
            return equal(start, s-1)+equal(s+1,stop);
        }
        if(p.parse_term1(p.input+s)=="-")
        {
            return equal(start, s-1)-equal(s+1,stop);
        }
        if(p.parse_term1(p.input+s)=="*")
        {
            return equal(start, s-1)*equal(s+1,stop);
        }
        if(p.parse_term1(p.input+s)=="/")
        {
            auto temp=equal(s+1,stop);
            if(temp==0)
            {
                throw std::runtime_error("Divizion by zero");
            }
            return equal(start, s-1)/temp;
        }
        if(std::isdigit(p.input[s]) || std::isdigit(p.input[s+1]))
        {
            int number;
            number=stoi(p.parse_term1(p.input+s));
            return number;
        }

        throw std::runtime_error("unknown character");

    }
};


int main(int argc, char *argv[])
{
    if (argc != 2) {
        std::cout << "error";
        return 1;
    }
    try{
        std::string s(argv[1]);
        s.erase( std::remove_if( s.begin(), s.end(), ::isspace ), s.end() );
        const char * c = s.c_str();
        Calc<int> calc(c);
        std::cout<<calc.equal(0, strlen(c)-1)<<std::endl;
    }
    catch (const std::runtime_error) {
        std::cout << "error";
        return 1;
    }

    return 0;
}
