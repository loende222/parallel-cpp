#pragma once

#include <optional>
#include <atomic>


template <typename T>
class MPSCQueue {
public:
    struct Node {
        Node* next;
        T value;

        Node(const T& value) : value(value) {
            next = nullptr;
        }
    };

    MPSCQueue() {
        head_ = nullptr;
    }

    ~MPSCQueue() {
        while (Pop() != std::nullopt);
    }

    void Push(const T& value) {
        Node* node = new Node(value);
        for (;;) {
            node->next = head_;
            if (head_.compare_exchange_weak(node->next, node)) {
                return;
            }
        }
    }

    std::optional<T> Pop() {
        auto cur_head = head_.load();
        if (cur_head == nullptr) {
            return std::nullopt;
        }
        for (;;) {
            if (head_.compare_exchange_weak(cur_head, cur_head->next)) {
                break;
            }
        }
        auto node = cur_head;
        auto res = node->value;
        delete node;
        return res;
    }

private:
    std::atomic<Node*> head_;
};
