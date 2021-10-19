## Thread safe queue


A wrap over `std::queue`. A thread safe queue is often needed when there are multiple threads that create objects (called producers) and multiple threads that process those objects (called consumers).

In the implementation, the `Pop` method is blocking (it waits for an object in the queue and takes it). And the `TryPop` method is non-blocking, it instantly returns the object if it was there, and otherwise returns `std::nullopt`.

---

In this implementation an [`std::condition_variable`](https://en.cppreference.com/w/cpp/thread/condition_variable) is used.
