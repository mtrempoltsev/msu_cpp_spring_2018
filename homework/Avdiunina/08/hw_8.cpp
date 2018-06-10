
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <stdexcept>

class can_not_open_file: public std::exception {};
class invalid_arguments_number: public std::exception {};

void count(const std::string& file)
{
    std::fstream in;
    in.open(file, std::fstream::in);
    if (!in)
        throw can_not_open_file();

    std::string word;
    std::map<std::string, int> dict;

    while(in >> word)
        dict[word]++;

    in.close();

    std::vector<std::pair<std::string, int>> vec(dict.begin(), dict.end());
    std::sort(vec.begin(), vec.end(), [](const auto& i, const auto& j) {return (i.second > j.second);});

    for (auto it = vec.begin(); it < 10 + vec.begin(); it++)
        std::cout << it->second << " " << it->first << std::endl;
}

int main(int argc, char **argv)
{
    try
    {
        if(argc != 2)
            throw invalid_arguments_number();

        count(argv[1]);
    }
    catch(const invalid_arguments_number& error)
    {
        return 1;
    }
    catch(...)
    {
        std::cerr << "Error!" << std::endl;
        return 1;
    }

    return 0;
}
