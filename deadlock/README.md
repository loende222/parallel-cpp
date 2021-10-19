## Deadlock

In this task, we need to achieve a [deadlock](https://en.wikipedia.org/wiki/Deadlock) - a problem that is not difficult to face in reality, but can rarely occur and be difficult to find.


`ThreadOne` and `ThreadTwo` methods run and complete their execution successfully if they are called sequentially. 
But a deadlock appears if they are called at about the same time.

---

The solution uses only [`sleep_for`](https://en.cppreference.com/w/cpp/thread/sleep_for) and [`mutex`](https://en.cppreference.com/w/cpp/thread/mutex).
