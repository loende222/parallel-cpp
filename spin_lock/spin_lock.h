#pragma once

#include <cstddef>
#include <thread>
#include <atomic>


class SpinLock {
public:
    SpinLock() {
        flag_ = false;
    }

    void Lock() {
        while (flag_.load() || flag_.exchange(true)) {
            std::this_thread::yield();
        }
    }

    void Unlock() {
        flag_ = false;
    }

private:
    std::atomic<bool> flag_;
};