#include <iostream>
#include <fstream>
#include <map>

int main(int argc,char **argv)
{
    if(argc != 2)
        return 1;

    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cout << "can't open file"<<std::endl ;
        return 1;
    }

    std::map<std::string, int> dict;
    std::string s;
    while (file.good())
    {
        file >> s;
        auto it = dict.find(s);
        if(it == dict.end() && s != "")
            dict[s] = 1;
        else
            it -> second++;
        s="";
    }

    //std::string s;
    int buff = 0;
    for(int i = 0; i < 10 && i < dict.size(); i++)
    {
        for (auto it = dict.begin(); it != dict.end(); it++)
        {
            if (it->second > buff)
            {
                s = it->first;
                buff = it ->second;
            }
        }
        std::cout<<dict[s]<<" "<<s<<std::endl;
        dict[s] = 0;
        buff=0;
    }

    return 0;
}