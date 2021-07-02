#pragma once

#include <ostream>
#include <string_view>
#include<thread>
#include<mutex>
#include <vector>


class HelloWorld {
private:
    std::vector<std::thread> Threads;
    size_t kThreads;
    std::mutex mtx;

public:
    static constexpr std::string_view kHelloPrefix = "Hello, World! From thread ";

    HelloWorld(size_t n_threads) : kThreads(n_threads) {
    }

    void SayHello(std::ostream& os) {
        for (size_t i = 0; i != kThreads; ++i) {
            Threads.emplace_back([&] {
                mtx.lock();
                os << kHelloPrefix << std::this_thread::get_id() << "\n";
                mtx.unlock();
            });
        }
        for (size_t i = 0; i != kThreads; ++i) {
            Threads[i].join();
        }
    }
};

