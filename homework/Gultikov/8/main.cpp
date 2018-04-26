#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main(int argc, char *argv[])
{
    if(argc != 2){
        std::cerr<<"Invalid argument";
        return 1;
    }

    std::ifstream file(argv[argc-1]);
    if(!file.is_open()){
        std::cerr<<"Can't open file";
        return 1;
    }

    std::map<std::string, int> dict;
    while(file.good()){
        std::string s;
        file >> s;
        dict[s]++;
    }
    file.close();

    std::multimap<int, std::string> d;
    for(auto i = dict.begin(); i != dict.end(); i++){
        d.insert(std::map <int, std::string>::value_type( i->second, i->first));
    }

    const unsigned top_n = 10;
    unsigned j = 0;
    for(auto i = d.rbegin(); i != d.rend() && j < top_n; i++){
        std::cout << i->first << ' ' << i->second << std::endl;
        j++;
    }
    return 0;
}
