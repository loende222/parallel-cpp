#pragma once

#include <optional>
#include <cstdint>
#include <atomic>
#include <vector>
#include <thread>

template <class T>
class MPMCQueue {
public:
    struct Node {
        T value;
        std::atomic<uint64_t> gen;
    };

    explicit MPMCQueue(uint64_t max_size) : mpmcq_(max_size){
        for (uint64_t i = 0; i != max_size; ++i) {
            mpmcq_[i].gen.store(i);
        }
        size_ = max_size;
        head_ = 0;
        tail_ = 0;
    }

    bool Push(const T& value) {
        for (;;) {
            auto cur_head = head_.load();
            auto idx = cur_head & (size_ - 1);

            if (cur_head == tail_.load() + size_) {
                return false;
            }

            if (mpmcq_[idx].gen != cur_head) {
                std::this_thread::yield();
                continue;
            }

            if (head_.compare_exchange_weak(cur_head,  cur_head + 1)) {
                mpmcq_[idx].value = value;
                ++mpmcq_[idx].gen;
                return true;
            }
        }
    }

    std::optional<T> Pop() {
        for (;;) {
            auto cur_tail = tail_.load();
            auto idx = cur_tail & (size_ - 1);

            if (cur_tail == head_.load()) {
                return std::nullopt;
            }

            if (mpmcq_[idx].gen.load() != cur_tail + 1) {
                std::this_thread::yield();
                continue;
            }

            if (tail_.compare_exchange_weak(cur_tail, cur_tail + 1)) {
                auto res = mpmcq_[idx].value;
                mpmcq_[idx].gen += size_ - 1;
                return res;
            }
        }
    }

public:
    std::vector<Node> mpmcq_;
    size_t size_;
    std::atomic<size_t> head_;
    std::atomic<size_t> tail_;
};