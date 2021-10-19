## Mellor-Crummey and Scott spin lock


[MCS lock](https://lwn.net/Articles/590243/) algorithm implementation.

We set up a [`thread_local`](https://en.cppreference.com/w/cpp/language/storage_duration) variable of type Node, which stores the flag showing if the lock is occupied by this thread, and a pointer to the next Node, building a singly linked list.

---

The implementation is not using [`mutex`](https://en.cppreference.com/w/cpp/thread/mutex).
