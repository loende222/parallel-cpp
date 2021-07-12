#pragma once

#include <atomic>
#include <condition_variable>
#include <exception>
#include <mutex>
#include <optional>


template <typename T>
class UnbufferedChannel{
public:
    UnbufferedChannel() {
        open_ = true;
        writing_ = false;
    }

    void Send(const T& value) {
        std::unique_lock s_lock(send_mtx_);
        std::unique_lock c_lock(block_mtx_);
        if (!open_) {
            throw std::runtime_error("Channel is closed");
        }
        writing_ = true;
        val_ = &value;
        recv_cv_.notify_one();
        while(open_ && writing_) {
            send_cv_.wait(c_lock);
        }
        if (writing_) {
            throw std::runtime_error("Channel is closed");
        }
    }

    std::optional<T> Recv() {
        std::unique_lock r_lock(recv_mtx_);
        std::unique_lock c_lock(block_mtx_);
        while(open_ && !writing_) {
            recv_cv_.wait(c_lock);
        }
        if (!open_) {
            return std::nullopt;
        }
        writing_ = false;
        std::optional<T> res(*val_);
        send_cv_.notify_one();
        return res;
    }

    void Close() {
        std::unique_lock c_lock(block_mtx_);
        open_ = false;
        send_cv_.notify_all();
        recv_cv_.notify_all();
    }

private:
    const T* val_;
    bool open_;
    bool writing_;
    std::mutex block_mtx_;
    std::mutex send_mtx_;
    std::mutex recv_mtx_;
    std::condition_variable send_cv_;
    std::condition_variable recv_cv_;
};

