#include <iostream>
#include <thread>
#include <condition_variable>
#include <fstream>

std::mutex pinpongMutex;
std::condition_variable pingpongCV;
bool isPingPong = false;

void ping(int64_t toggle_number, std::ofstream& file) {

    for (int i = 0; i < toggle_number; ++i) {
        std::unique_lock<std::mutex> ping_lock(pinpongMutex);
        while (isPingPong) {
            pingpongCV.wait(ping_lock);
        }
        file << "Ping" << std::endl;
        isPingPong = true;
        pingpongCV.notify_one();
    }
}

void pong(int64_t toggle_number, std::ofstream& file) {
    for (int i = 0; i < toggle_number; ++i) {
        std::unique_lock<std::mutex> pong_lock(pinpongMutex);
        while (!isPingPong) {
            pingpongCV.wait(pong_lock);
        }
        file << "Pong" << std::endl;
        isPingPong = false;
        pingpongCV.notify_one();
    }
}

int main() {
    int64_t toggle_number = 1000000;
    std::string file_name = "pingpong.txt";
    std::ofstream out_file(file_name);
    if (!out_file)
    {
        std::cout << "can't open file" ;
        return 1;
    }
    std::thread pingThread(ping, toggle_number, std::ref(out_file));
    std::thread pongThread(pong, toggle_number, std::ref(out_file));
    pingThread.join();
    pongThread.join();
    out_file.close();

    std::ifstream in_file(file_name);
    if (!in_file)
    {
        std::cout << "can't open file" ;
        return 1;
    }
    bool ping_pong_flag = true;
    while (in_file.good())
    {
        std::string s;
        in_file >> s;

        if (ping_pong_flag)
        {
            if (s != "Ping" && !s.empty())
            {
                std::cout << "Errror sequence" << std::endl;
                return 1;
            }
            ping_pong_flag = false;
        } else
        {
            if (s != "Pong"  && !s.empty())
            {
                std::cout << "Errror sequence" << std::endl;
                return 1;
            }
            ping_pong_flag = true;
        }

    }
    return 0;
}