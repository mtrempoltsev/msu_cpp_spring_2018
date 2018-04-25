#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>


class Error {
};

class ArgumentError : public Error {
private:
    std::string message_;
public:
    explicit ArgumentError(std::string &&message) {
        message_ = message;
    }

    const std::string &getMessage() const {
        return message_;
    }
};


template<class A, class B>
std::multimap<B, A> flip_map(const std::map<A, B> &src) {
    std::multimap<B, A> dst;
    std::transform(src.begin(), src.end(), std::inserter(dst, dst.begin()),
                   [](const std::pair<A, B> &p) { return std::pair<B, A>(p.second, p.first); });
    return dst;
}

template<class Map>
void print_map(Map &m) {
    for (auto i = m.rbegin(); i != m.rend(); i++) {
        std::cout << i->first << ' ' << i->second << std::endl;
    }
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 2) {
            throw ArgumentError("ERROR argc != 2");
        }
        std::ifstream file(argv[1]);
        if (!file) {
            throw ArgumentError("Can't open file");
        }
        std::map<std::string, unsigned int> dict;
        std::string tmp_string;
        while (file.good()) {
            file >> tmp_string;
            dict[tmp_string] += 1;
        }
        std::multimap<unsigned int, std::string> res = flip_map(dict);
        print_map(res);
    }
    catch (const ArgumentError &error) {
        return 1;
    }
    catch (...) {
        return 1;
    }
    return 0;
}