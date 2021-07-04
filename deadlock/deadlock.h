#pragma once

#include <thread>
#include <mutex>
#include <chrono>

class Deadlock {
public:
    Deadlock() {
    }

    void ThreadOne() {
        std::unique_lock lock1(mtx1_);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::unique_lock lock2(mtx2_);
    }

    void ThreadTwo() {
        std::unique_lock lock1(mtx2_);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::unique_lock lock2(mtx1_);
    }

private:
    std::mutex mtx1_;
    std::mutex mtx2_;
};
