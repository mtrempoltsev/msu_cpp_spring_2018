#include <algorithm>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

class DictError: public std::runtime_error {

public:
    DictError(std::string err_msg) : std::runtime_error("Dict error: " + err_msg) {}
};

class Dict {

public:
    using TStringInt = std::pair<std::string, uint64_t>;

    Dict(const std::string infile) {
        std::ifstream file(infile);

        if (!file) {
            throw DictError("cannot open file \"" + infile + "\"");
        }

        std::string str;

        while (file.good()) {
            file >> str;

            map_data_[str]++;
        }

        sort();
    }

    void print() {
        for (auto it = v_data_.begin(); it != v_data_.end(); it++) {
            if (it - v_data_.begin() > 9) {
                break;
            }

            std::cout << (it->second) << " " << (it->first) << std::endl;
        }
    }

private:
    void sort() {
        v_data_ = std::vector<TStringInt>(map_data_.begin(), map_data_.end());

        auto lt = [](const TStringInt & i, const TStringInt & j) {
            return (i.second < j.second);
        };

        std::sort(v_data_.rbegin(), v_data_.rend(), lt);
    }

    std::map<std::string, uint64_t> map_data_;
    std::vector<TStringInt> v_data_;
};

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: ./a.out <infile>" << std::endl;

        return 1;
    }

    try {
        Dict dict = Dict(argv[1]);

        dict.print();
    } catch (const DictError& e) {
        std::cout << e.what() << std::endl;

        return 1;
    }

    return 0;
}
