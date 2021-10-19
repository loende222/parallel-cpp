## Thread safe vector

Wrap over `std::vector`, but the only change possible in this data structure is adding a new element to the end.

Since the elements never change, many threads can read such a vector at once, however, when `PushBack` is executed, a reallocation may occur, which is why, at the time of adding an element, it is necessary to make sure that no reads occur.


---
 [`std::shared_mutex`](https://en.cppreference.com/w/cpp/thread/shared_mutex) and [`std::shared_lock`](https://en.cppreference.com/w/cpp/thread/shared_lock) are used in the implementation.
