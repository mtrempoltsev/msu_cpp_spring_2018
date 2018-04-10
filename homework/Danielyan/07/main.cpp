#include <iostream>
#include <vector>
#include <string>
#include <sstream>

void CheckNumberCorrectness(const std::string& s) {
    bool double_dot = false;
    bool first_symbol = true;
    for (auto &&x : s) {
        if (first_symbol && x == '-') {
            first_symbol = false;
            continue;
        }
        if (!(('0' <= x && x <= '9') || (x == '.' && !double_dot)))
            throw std::invalid_argument("");
        else if (x == '.')
            double_dot = true;
    }
}

template <class T>
auto Parse(const std::string& s) {
    CheckNumberCorrectness(s);
    std::stringstream ss;
    ss << s;
    T result;
    ss >> result;
    return result;
}

std::string ClearSpaces(std::string s) {
    size_t  p = 0;
    for (size_t i = 0; i < s.size(); ++i)
        if (s[i] != ' ')
            s[p++] = s[i];
    s.resize(p);
    s.shrink_to_fit();
    return s;
}

auto Split(const std::string& s, const std::string& delimiters) {
    std::vector<std::string> result;
    result.emplace_back();
    for (size_t i = 0; i < s.size(); ++i) {
        if (delimiters.find(s[i]) < delimiters.size()) {
            if (result.back() != "")
                result.emplace_back();
            result.back() = s[i];
            result.emplace_back();
        } else {
            result.back().push_back(s[i]);
        }
    }
    if (result.back() == "")
        result.pop_back();
    return result;
}

template <class T>
class Calculator {
public:
    T evaluate(const std::string& expression) {
        splitted_ = Split(ClearSpaces(expression), "+-*/");
        CheckOperationCorrectness();
        return evaluate(0, splitted_.size());
    }

private:
    T evaluate(size_t from, size_t to) const {
        if (to - from == 1)
            return Parse<T>(splitted_[from]);
        for (size_t i = to; i-- > from; ) {
            if (splitted_[i] == "+") {
                return evaluate(from, i) + evaluate(i + 1, to);
            }
            if (splitted_[i] == "-") {
                return evaluate(from, i) - evaluate(i + 1, to);
            }
        }
        for (size_t i = to; i-- > from; ) {
            if (splitted_[i] == "*") {
                return evaluate(from, i) * evaluate(i + 1, to);
            }
            if (splitted_[i] == "/") {
                auto a = evaluate(from, i), b = evaluate(i + 1, to);
                if (b == 0)
                    throw std::invalid_argument("");
                return a / b;
            }
        }
        throw std::runtime_error("something bad happened!");
    }

    void CheckOperationCorrectness() {
        bool prev_is_unary_minus = false;
        bool prev_is_operation = false;
        size_t p = 0;
        for (size_t i = 0; i < splitted_.size(); ++i) {
            if (splitted_[i].size() == 1 && IsOperation(splitted_[i][0])) {
                if (prev_is_operation) {
                    if (splitted_[i][0] == '-') {
                        prev_is_unary_minus = !prev_is_unary_minus;
                    } else {
                        throw std::invalid_argument("");
                    }
                } else {
                    if (splitted_[i][0] == '-' && p == 0) {
                        prev_is_unary_minus = !prev_is_unary_minus;
                    } else {
                        splitted_[p++] = splitted_[i];
                        prev_is_operation = true;
                    }
                }
            } else {
                if (prev_is_operation) {
                    if (prev_is_unary_minus)
                        splitted_[i] = "-" + splitted_[i];
                    splitted_[p++] = splitted_[i];
                } else {
                    if (p != 0) {
                        throw std::invalid_argument("");
                    } else {
                        if (prev_is_unary_minus)
                            splitted_[i] = "-" + splitted_[i];
                        splitted_[p++] = splitted_[i];
                    }
                }
                prev_is_unary_minus = false;
                prev_is_operation = false;
            }
        }
        if (prev_is_operation || prev_is_unary_minus)
            throw std::invalid_argument("");

        splitted_.resize(p);
        splitted_.shrink_to_fit();
    }

    bool IsOperation(char c) const {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    std::vector<std::string> splitted_;
};


int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "error";
        return 1;
    }

    Calculator<int> calculator;
    try {
        std::cout << calculator.evaluate(argv[1]);
    } catch (const std::invalid_argument&) {
        std::cout << "error";
        return 1;
    }
    return 0;
}

