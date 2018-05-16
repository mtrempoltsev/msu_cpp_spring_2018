#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <utility>
#include <vector>
#include <map>


int main(int argc, char* argv[]) 
{

    if (argc != 2) 
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    
    std::fstream finput;
    finput.open(argv[1], std::fstream::in);
    if (!finput) 
    {
        std::cerr << "error" << std::endl;
        return 1;
    }
    
    std::string word;
    std::map<std::string, int> dict_word;
    
    while(finput >> word) 
        dict_word[word]++;
    finput.close();
    
    std::vector<std::pair<std::string, int>> rating(dict_word.begin(), dict_word.end());
    std::sort(rating.begin(), rating.end(), [](const auto& i, const auto& j) {return (i.second > j.second);});
    
    for (auto it = rating.begin(); it != rating.end() && it - rating.begin() < 10; it++)
        std::cout << it->second << ' ' << it->first << std::endl;
    
    return 0;
}
