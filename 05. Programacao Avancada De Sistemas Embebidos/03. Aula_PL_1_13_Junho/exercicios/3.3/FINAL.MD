In Exercise 3.3, each thread receives a struct containing its input index,
output index, value to add, and delay.

The worker threads repeatedly read one shared_array cell, reset it to zero,
add a constant value, and write the result to another cell.

The main thread acts as a monitor by printing shared_array every second.

The changing output confirms that the threads are running concurrently
and modifying shared state.