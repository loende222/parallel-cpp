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
        std::shared_lock lock(mtx1_);
        return vector_[index];
    }

    size_t Size() const {
        std::shared_lock lock(mtx1_);
        return vector_.size();
    }

    void PushBack(const T& value) {
        if (vector_.size() == vector_.capacity()) {
            std::unique_lock lock1(mtx1_);
            std::unique_lock lock2(mtx2_);
            vector_.push_back(value);
        } else {
            std::shared_lock lock1(mtx1_);
            std::unique_lock lock2(mtx2_);
            vector_.push_back(value);
        }
    }

private:
    std::vector<T> vector_;
    mutable std::shared_mutex mtx1_;
    std::mutex mtx2_;
};

