#pragma once

#include <cstddef>
#include <thread>
#include <vector>
#include <numeric>
#include <atomic>

template <typename RandomAccessIterator, class T, class Func>
T parallel_reduce(RandomAccessIterator begin, RandomAccessIterator end,
                  const T& initial_value, Func func, size_t n_threads) {
    std::vector<std::thread> threads;
    std::atomic<T> result(initial_value);

    for (size_t i = 0; i != n_threads; ++i) {
        RandomAccessIterator from = begin + (end - begin) * i / n_threads;
        RandomAccessIterator to = begin + (end - begin) * (i + 1) / n_threads;
        threads.emplace_back([from, to, &result, &func] {
            T local_result = *from;
            local_result = std::reduce(from + 1, to, local_result, func);
            result.store(func(result.load(), local_result));
        });
    }

    for (auto& t : threads) {
        t.join();
    }
    return result.load();
}
