#pragma once

#include <atomic>
#include <thread>

class MCSLock {
public:
    struct Node {
        std::atomic<Node*> next;
        std::atomic<bool> acquired;
    };

    thread_local static Node node;

    MCSLock() {
        tail_ = nullptr;
    }

    void Lock() {
        node.next.store(nullptr);
        node.acquired.store(false);
        auto prev = tail_.exchange(&node);
        if (prev != nullptr) {
            prev->next.store(&node);
            while (!node.acquired) {
                std::this_thread::yield();
            }
        } else {
            node.acquired.store(true);
        }
    }

    void Unlock() {
        auto succ = node.next.load();
        Node* tmp = &node;
        if (succ == nullptr) {
            if (tail_.compare_exchange_weak(tmp, nullptr)) {
                return;
            }
        }

        node.next.load()->acquired = true;
    }

private:
    std::atomic<Node*> tail_;
};

