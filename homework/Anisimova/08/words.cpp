#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <algorithm>
#include <vector>


int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return 1;
    }
    std::string s;
    std::map<std::string, int> dict;

    std::fstream file;
    file.open(argv[1], std::fstream::in);

    if (!file)
    {
        std::cerr << "file error" << std::endl;
        return 1;
    }

    while (file >> s)
        dict[s]++;

    file.close();
    int k=0;
    std::multimap<int, std::string> sort;

    for (auto it = dict.begin(); it != dict.end(); it++)
    {
        sort.insert(std::pair<int, std::string>(it->second, it->first));
    }

    for (auto it = sort.rbegin(); it != sort.rend() && k<10; ++it, ++k)
    {
        std::cout << (*it).first << " " << (*it).second << std::endl;
    }

    return 0;
}
