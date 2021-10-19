## Multiple Producer Single Consumer Queue


Lock-free stack implementation. Multiple producer single consumer means that multiple threads can add items to the stack, but only one thread can pop them.

Each element is stored in a Node structure, pointer to the next element is also stored in Node. Thus, a singly linked list is formed. The stack itself stores a pointer to the head of the list.

---

The solution task uses CAS operations.
