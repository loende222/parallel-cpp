## Hello, World!

Printing `"Hello, World! From thread <thread_id>\n"` from multiple threads.

---

Since `ostream` is not thread-safe, access to it must be restricted via [`mutex`](https://en.cppreference.com/w/cpp/thread/mutex).
To get the id of the current thread, we call the [`get_id`](https://en.cppreference.com/w/cpp/thread/get_id) from the standard library.
