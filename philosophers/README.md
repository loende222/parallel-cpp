## [Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Formulation of the problem:

There are N philosophers sitting at a round table, each of whom has a plate of spaghetti in front of them, and between each pair of philosophers there is one fork - a total of N forks. Every philosopher can be in one of two states:
- Thinking - a philosopher does not need forks, and he simply reflects on his philosophical thoughts.
- Hungry - the philosopher is hungry. In this case, the philosopher must take both forks, which lie to his left and right, and start eating. After the philosopher decides to think again, he must put these forks back on the table.

In the `Philosopher` class, the `Eat` method must "take" adjacent forks from the table, waiting for them to be released, if they were busy. The `Think` method is to put the forks back on the table.
