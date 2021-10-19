## Multiple Producer Multiple Consumer Bounded Queue

Lock-free queue implementation. Multiple producer multiple consumer means that multiple threads can both add and retrieve items to the queue. Bounded means the queue is limited in size. The maximum queue size is specified in the constructor.


 `Push` method returns `false`, if the queue is full, otherwise it inserts an element and returns `true`.  
 `Pop` method returns `std::nullopt`, if the queue is empty, otherwise it pops and returns the item.
 
 The algorithm is following:
 1. We create an array of the required size. For simplicity, the queue size can only be a power of two - 2, 4, 8, etc.
 2. Each element of the array consists of an object of type T and an atomic unsigned number - "generation".
 3. Initially, generation is equal to the index of the element in the array.
 4. 2 indices are stored - `head` and `head` of the queue. These indices never decrease, and to get an index in an array, we need to take the remainder of the division by `size` (in our case, we can take a bitwise AND with `size - 1`, since `size` is a power of two).
 5. When inserting an element, if there is room in the queue, we increase the `head` index by one, thereby reserving space. After copying the element, we increment the generation by one, indicating that we have written the element. Note that we can write an element only if the generation is equal to the value of `head`, which means that the element has already been fetched from there (or there was no element originally).
 6. When deleting an element, if the queue is not empty, we increase the `tail` index by one, thereby reserving the element. After copying the element, we increase the generation by `size - 1`, thereby indicating that we have taken the element and freed up space. Note that we can only pick up an item if generation is `tail + 1`, which means that the item was written there.

Constantly increasing the indexes of the beginning and end of the queue are necessary to avoid the [ABA-problem](https://en.wikipedia.org/wiki/ABA_problem).

---

The solution task uses CAS operations.
