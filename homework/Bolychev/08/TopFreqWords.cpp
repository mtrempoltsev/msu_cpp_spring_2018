#include <iostream>
#include <string>
#include <fstream>
#include <map>

int main(int argc, char* argv[])
{
    try {
        if (argc != 2) {
            throw std::runtime_error("Wrong input");
        }

        std::ifstream file(argv[1]);
        if (!file) {
            throw std::runtime_error("can't open file " + std::string(argv[1]));

        }

        std::map<std::string, size_t> freq_dict;

        while (file.good()) {
            std::string s;
            file >> s;
            if (s.length() > 0) {
                freq_dict[s]++;
            }
        }

        std::multimap<size_t, std::string> reversed_freq_dict;
        for (std::pair<std::string, int> pair : freq_dict) {
            reversed_freq_dict.insert(std::make_pair(pair.second, pair.first));
        }

        auto it = reversed_freq_dict.rbegin();
        size_t cnt = 0;
        while (it != reversed_freq_dict.rend() && cnt < 10) {
            std::cout << it->first << " " << it->second << '\n';
            ++it;
            ++cnt;
        }

    } catch (std::runtime_error err) {
        std::cerr << err.what() << std::endl;
        return 1;
    } catch(...) {
        std::cerr << "Unknown error" << std::endl;
        return 1;
    }


    return 0;
}
