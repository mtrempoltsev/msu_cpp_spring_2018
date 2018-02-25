#include <chrono>
#include <iostream>


using namespace std;

class Timer {
public:
    Timer(string name)
        : start_(std::chrono::high_resolution_clock::now()) {
        this->name = name;
    }

    ~Timer() {
        const auto finish = std::chrono::high_resolution_clock::now();
        std::cout << this->name << ": " << std::chrono::duration_cast<std::chrono::microseconds>(finish - start_).count() << " us" << std::endl;
    }

private:
    string name;
    const std::chrono::high_resolution_clock::time_point start_;
};
