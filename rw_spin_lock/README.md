## Read-Write spin lock

Read-Write spin lock implementation, based on only one [`atomic`](https://en.cppreference.com/w/cpp/atomic/atomic) variable. This blocking allows either access for an unlimited number of readers or access for a single writer.

Algorithm idea:
1. An atomic variable of unsigned type is created.
2. The least significant bit serves as a flag for writing.
3. The rest of the bits serve as a reader counter.
4. `LockWrite` sets the writer flag.
5. `LockRead` increases the reader counter by 1 (that is, increases the variable itself by 2).


Writing is available only if the reader counter is 0 and the thread itself has set the writer flag.
Reading is available if the writer flag is 0.

At the same time, writers have a priority. If there is a writer who is waiting for the readers to finish and a new reader arrives, then the new reader is not allowed to take a read lock and must wait for the writer(s) to complete their work.

---

The solution uses [CAS](https://en.wikipedia.org/wiki/Compare-and-swap) operations. 
