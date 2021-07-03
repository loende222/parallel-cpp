#pragma once

#include <mutex>


class Fork {
 public:
  Fork(size_t id) : id_(id) {
  }

  size_t Id() const {
    return id_;
  }

  void Get() {
    mutex_.lock();
  }

  bool TryGet() {
    return mutex_.try_lock();
  }

  void Put() {
    mutex_.unlock();
  }

 private:
  size_t id_;
  std::mutex mutex_;
};

class Philosopher {
public:
    Philosopher(size_t id, Fork* left_fork, Fork* right_fork) {
        id_ = id;
        left_ = left_fork;
        right_ = right_fork;
    }

    size_t Id() const {
        return id_;
    }

    void Eat() {
        if (left_->Id() < right_->Id()) {
            while (true) {
                if (left_->TryGet()) {
                    if (right_->TryGet()) {
                        break;
                    } else {

                        left_->Put();
                    }
                }
            }
        } else {
            while (true) {
                if (right_->TryGet()) {
                    if (left_->TryGet()) {
                        break;
                    } else {
                        right_->Put();
                    }
                }
            }
        }
    }

    void Think() {
        left_->Put();
        right_->Put();
    }

private:
    size_t id_;
    Fork* left_;
    Fork* right_;
};


