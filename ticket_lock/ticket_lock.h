#pragma once

#include <cstddef>
#include <thread>
#include <atomic>


class TicketLock {
public:
    TicketLock() {
    }

    void Lock() {
        size_t my_ticket = next_ticket_.fetch_add(1);
        while (now_serving_ != my_ticket) {
            std::this_thread::yield();
        }
    }

    void Unlock() {
        now_serving_.fetch_add(1);
    }

private:
    std::atomic<size_t> now_serving_{0};
    std::atomic<size_t> next_ticket_{0};
};
