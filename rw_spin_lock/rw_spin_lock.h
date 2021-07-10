#pragma once

#include <atomic>
#include <thread>

class RWSpinLock {
public:
    RWSpinLock() {
        counter_ = 0;
    }

    void LockRead() {
        for (;;) {
            uint16_t local = counter_.load();
            if (local & 1) {
                std::this_thread::yield();
                continue;
            }
            if (counter_.compare_exchange_weak(local, local + 2)) {
                break;
            }
        }
    }

    void UnlockRead() {
        counter_ -= 2;
    }

    void LockWrite() {
        for (;;) {
            uint16_t local = counter_.load();
            if (local & 1) {
                std::this_thread::yield();
                continue;
            }
            if (counter_.compare_exchange_weak(local, local + 1)) {
                break;
            }
        }
        while (counter_ != 1) {
            std::this_thread::yield();
        }
    }

    void UnlockWrite() {
        counter_ -= 1;
    }

private:
    std::atomic<uint16_t> counter_;
};
