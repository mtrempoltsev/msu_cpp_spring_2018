#include <iostream>
#include <string>
#include <fstream>
#include <map>

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            std::cerr << "Wrong input" << std::endl;
        }

        std::ifstream file(argv[1]);
        if (!file) {
            std::cerr << "can't open file " << argv[1] << std::endl;
            return 1;
        }

        std::map<std::string, size_t> freq_dict;

        while (file) {
            std::string s;
            file >> s;
            freq_dict[s]++;
        }

        std::multimap<size_t, std::string> reversed_freq_dict;
        for (const auto& pair : freq_dict) {
            reversed_freq_dict.emplace(pair.second, pair.first);
        }

        auto it = reversed_freq_dict.rbegin();
        size_t cnt = 0;
        while (it != reversed_freq_dict.rend() && cnt < 10) {
            std::cout << it->first << " " << it->second << '\n';
            ++it;
            ++cnt;
        }
    } catch(...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }


    return 0;
}
