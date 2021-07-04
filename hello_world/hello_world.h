#pragma once

#include <ostream>
#include <string_view>
#include<thread>
#include<mutex>
#include <vector>


class HelloWorld {
private:
    const size_t n_threads_;
    std::vector<std::thread> threads_;
    std::mutex mtx_;

public:
    static constexpr std::string_view kHelloPrefix = "Hello, World! From thread ";

    HelloWorld(size_t n_threads) : n_threads_(n_threads) {
    }

    void SayHello(std::ostream& os) {
        for (size_t i = 0; i != n_threads_; ++i) {
            threads_.emplace_back([&] {
                std::unique_lock lock(mtx_);
                os << kHelloPrefix << std::this_thread::get_id() << "\n";
            });
        }
        for (auto& t : threads_) {
            t.join();
        }
    }
};

