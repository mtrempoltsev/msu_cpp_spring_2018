#include <iostream>
#include <sstream>
#include <thread>
#include <string>

std::mutex m;

int i = 0;

void f1(std::ostream * str) {
    while(true) {
        m.lock();
        if(i % 2 == 0) {
            if(i == 1000000) {
                m.unlock();
                break;
            }
            *str << "ping" << std::endl;
            ++i;
        }
        m.unlock();
    }
}

void f2(std::ostream * str) {
    while(true) {
        m.lock();
        if(i % 2 == 1) {
            *str << "pong" << std::endl;
            ++i;
            if(i == 1000000) {
                m.unlock();
                break;
            }
        }
        m.unlock();
    }
}
int main() {

    const bool check = false; // you can turn this on to make sure that the sequence is correct

    std::stringstream str;
    std::ostream  * s = check ? &str : &std::cout;

    std::thread t1(f1, s);
    std::thread t2(f2, s);

    t1.join();
    t2.join();

    if(check) {
        std::cerr << "Checking the resulting sequence..." << std::endl;
        std::string in;
        for(size_t i = 0; i < 1000000; ++i) {
            if(!str.good()) {
                std::cerr << "Error: sequence too short." << std::endl;
                return 1;
            }
            str >> in;
            if(i % 2 == 0) {
                if(in != "ping") {
                    std::cerr << "Error: unexpected token." << std::endl;
                    return 1;
                }
            } else {
                if(in != "pong") {
                    std::cerr << "Error: unexpected token." << std::endl;
                    return 1;
                }
            }
        }
        str >> in;
        if(str.good()) {
            std::cerr << "Error: sequence too long." << std::endl;
            return 1;
        }
	std::cerr << "All good. The sequence is correct." << std::endl;
    }
    return 0;
}
