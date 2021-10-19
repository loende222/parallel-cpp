## Unbuffered channel

The analogue of the [channel (chan) from the GoLang language](https://gobyexample.com/channels). Such a channel does not store elements in itself - it only encourages the threads to transfer elements to each other.

- When calling `Send` and` Recv` together, an element from one thread must go to another thread. In this case, only one copy of the element should occur.

- The `Send` method waits for either the release of` Recv` to send it an item, or a call to `Close`, which means that the channel is closed. Calling `Send` for a closed channel should throw an exception with the text ` "Channel is closed" `.

- The `Recv` method waits either for a` Send` call to take an element from it, or for a `Close` call. A call to `Recv` on a closed channel must return `std::nullopt`, in all other cases an element must be returned.

---

[`std::condition_variable`](https://en.cppreference.com/w/cpp/thread/condition_variable) is used.
