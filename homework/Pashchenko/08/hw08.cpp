#include <iostream>
#include <fstream>
#include <algorithm>
#include <stdexcept>
#include <map>
#include <vector>

class can_not_open_file: public std::exception {};

void word_counter(const std::string& name)
{
    std::ifstream fin(name);
    if (!fin)
    {
        throw can_not_open_file();
    }

    std::string word;
    std::map<std::string, int> dict;

    while (fin >> word)
        dict[word]++;

    std::vector<std::pair<std::string, int>> vec(dict.begin(), dict.end());
    std::sort(vec.begin(), vec.end(), [](const auto& i, const auto& j) {return (i.second > j.second);});

    for (auto it = vec.begin(); it - vec.begin() < 10; it++)
        std::cout << it->second << " " << it->first << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    try
    {
        word_counter(argv[1]);
    }
    catch(...)
    {
        std::cerr << "error" << std::endl;
        return 1;
    }

    return 0;
}
