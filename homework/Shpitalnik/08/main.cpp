#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <algorithm>
#include <vector>

using dictionary = std::map<std::string, int>;
using word = std::pair<std::string, int>;

bool cmp(const word &w1, const word &w2){
    return std::get<1>(w1) > std::get<1>(w2);
}

int main(int argc, char **argv) {
    const int top = 10;
    dictionary dict;
    std::string s;
    if(argc < 2){
        return 1;
    }
    std::ifstream file(argv[1]);
    if (!file)
    {
        std::cout << "can't open file" ;
        return 1;
    }
    while (file.good())
    {
        file >> s;
        if(dict.find(s) != dict.end())
            dict[s]++;
        else
            dict[s] = 1;
    }

    std::vector<word> vec;
    auto cur = dict.begin();
    auto end = dict.end();
    while(cur != end){
        vec.push_back(*cur);
        cur++;
    }
    std::sort(vec.begin(), vec.end(), cmp);
    for(int i =0; i<top; i++){
        std::cout << std::get<1>(vec[i]) << ' ' << std::get<0>(vec[i]) <<'\n';
    }
    return 0;

}
