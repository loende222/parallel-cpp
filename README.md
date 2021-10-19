# Parallel C++

This repository contains tasks from the course that I took after my first year of undergraduate studies. 
It focuses on multithreading in C++. Here is a short description of the tasks & links to them (solution, tests, local readme with more details):

#### Creating and avoiding deadlock

- ***[deadlock](https://github.com/loende222/parallel-cpp/tree/main/deadlock)*** - achiving [deadlock](https://en.wikipedia.org/wiki/Deadlock)

- ***[philosophers](https://github.com/loende222/parallel-cpp/tree/main/philosophers)*** - solution of [dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)


#### Thread safe data structures

- ***[thread_safe_queue](https://github.com/loende222/parallel-cpp/tree/main/thread_safe_queue)*** -
a thread-safe wrap over the standard library `std::queue`

- ***[thread_safe_vector](https://github.com/loende222/parallel-cpp/tree/main/thread_safe_vector)*** -
a thread-safe wrap over `std::vector`, but the only change to this structure is adding a new element to the end


#### Locking algorithms

- ***[spin_lock](https://github.com/loende222/parallel-cpp/tree/main/spin_lock)*** -
[Spinlock](https://en.wikipedia.org/wiki/Spinlock) implementation

- ***[ticket_lock](https://github.com/loende222/parallel-cpp/tree/main/ticket_lock)*** -
[Ticket lock](https://en.wikipedia.org/wiki/Ticket_lock) implementation

- ***[mcs_lock](https://github.com/loende222/parallel-cpp/tree/main/mcs_lock)*** -
[MCS lock](https://lwn.net/Articles/590243/) (Mellor-Crummey and Scott spin lock) implemetation

- ***[rw_spin_lock](https://github.com/loende222/parallel-cpp/tree/main/rw_spin_lock)*** -
Read-Write spin lock, that allows either access for an unlimited number of readers or access for a single writer


#### Lock-free data structures

- ***[mpsc_queue](https://github.com/loende222/parallel-cpp/tree/main/mpsc_queue)*** -
lock-free stack implementation, where many threads can add items to the stack, but only one thread can pop them

- ***[mpmc_queue](https://github.com/loende222/parallel-cpp/tree/main/mpmc_queue)*** -
bounded lock-free queue, where multiple threads can either add or retrieve items to the queue


#### Other tasks


- ***[unbuffered_channel](https://github.com/loende222/parallel-cpp/tree/main/unbuffered_channel)*** -
analog of the chan from the GoLang language. Such a channel does not store elements in itself - it only helps the threads to transfer elements to each other


- ***[reduce](https://github.com/loende222/parallel-cpp/tree/main/reduce)*** -
parallel analog of [`std::reduce`](https://en.cppreference.com/w/cpp/algorithm/reduce)
