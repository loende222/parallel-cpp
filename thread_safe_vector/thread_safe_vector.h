#pragma once

#include <vector>
#include <mutex>
#include <shared_mutex>
#include <thread>

template <typename T>
class ThreadSafeVector {
public:
    ThreadSafeVector() = default;

    T operator[](size_t index) const {
        std::shared_lock r_lock(read_mtx_);
        return vector_[index];
    }

    size_t Size() const {
        std::shared_lock r_lock(read_mtx_);
        return vector_.size();
    }

    void PushBack(const T& value) {
        std::unique_lock w_lock(write_mtx_);
        if (vector_.size() == vector_.capacity()) {
            std::unique_lock r_lock(read_mtx_);
            vector_.push_back(value);
        } else {
            vector_.push_back(value);
        }
    }

private:
    std::vector<T> vector_;
    mutable std::shared_mutex read_mtx_;
    std::mutex write_mtx_;
};

