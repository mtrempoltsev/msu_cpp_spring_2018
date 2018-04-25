#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <vector>

int main(int argc, char ** argv) {

    if(argc < 2) {
        std::cerr << "You need to pass filename as a parameter" << std::endl;
        return 1;
    }
    if(argc > 2) {
        std::cerr << "Too many arguments passed. Interpreting the first argument "\
                     "as filename and ignoring the rest" << std::endl;
    }

    std::ifstream file(argv[1]);

    if(!file) {
        std::cerr << "Couldn't find file " << argv[1] <<
                  " exiting now" << std::endl;
        return 1;
    }

    std::unordered_map<std::string, size_t> freq_dict;

    while(true) {
        std::string word;
        file >> word;
        if(file.good()) {
            if (freq_dict.find(word) != freq_dict.end()) {
                ++freq_dict[word];
            } else {
                freq_dict[word] = 1;
            }
        } else {
            break;
        }
    }
    
    std::vector<std::pair<std::string, size_t>> rev_dict;
    std::copy(freq_dict.begin(), freq_dict.end(), std::back_inserter(rev_dict));

    auto it = rev_dict.begin();
    std::advance(it, std::min(10l, std::distance(it, rev_dict.end())));

    std::partial_sort(rev_dict.begin(), it, rev_dict.end(),
                      [](const std::pair<std::string, size_t> & a,
                         const std::pair<std::string, size_t> & b)
                      {
                          return a.second > b.second;
                      });

    for(auto i = rev_dict.begin(); i != it; ++i) {
        std::cout << i->second << " " << i->first << std::endl;
    }

    return 0;
}