#pragma once

#include <optional>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

template <typename T>
class ThreadSafeQueue {
public:
    ThreadSafeQueue() {
    }

    void Push(const T& value) {
        std::unique_lock lock(mtx_);
        queue_.push(value);
        cv_.notify_all();
    }

    T Pop() {
        std::unique_lock lock(mtx_);
        while (queue_.empty()) {
            cv_.wait(lock);
        }
        auto value = queue_.front();
        queue_.pop();
        return value;
    }

    std::optional<T> TryPop() {
        std::unique_lock lock(mtx_);
        if (queue_.empty()) {
            return std::nullopt;
        }
        auto value = queue_.front();
        queue_.pop();
        return value;
    }


private:
    std::mutex mtx_;
    std::condition_variable cv_;
    std::queue<T> queue_;
};

