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
    std::vector<T> local_results(n_threads);

    for (size_t i = 0; i != n_threads; ++i) {
        RandomAccessIterator from = begin + (end - begin) * i / n_threads;
        RandomAccessIterator to = begin + (end - begin) * (i + 1) / n_threads;
        threads.emplace_back([from, to, &func, i, initial_value, &local_results] {
            local_results[i] = std::reduce(from, to, initial_value, func);
        });
    }

    for (auto& t : threads) {
        t.join();
    }
    return std::reduce(local_results.begin(), local_results.end(), initial_value, func);
}
