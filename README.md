# Threads: lab templates

The render node of the department's render farm: one machine, many cores,
one frame of the animation to render as fast as possible. Each exercise is
one part of the node, written from a partially completed template: threads
rendering bands of the frame, shared statistics under a mutex, rows displayed
in order with a condition variable, a pool of workers on a queue, and the
same frame rendered by processes with shared memory, for comparison.

```
ex_threads_templates/
├── demo/      <- Part 1: the programs shown during the lecture
├── ese_1/     <- Exercise 1: one thread per band
├── ese_2/     <- Exercise 2: the progress counter (mutex)
├── ese_3/     <- Exercise 3: rows in order (condition variable)
├── ese_4/     <- Exercise 4: the worker pool (queue with conditions)
├── ese_5/     <- Exercise 5: processes and shared memory
└── report/    <- the render report (needs the 5 confirmation codes)
```

The exercises are independent: solve them in any order.

To compile (the Makefiles add -pthread):
> cd ese_1
> make

To run the executable, and time it
> time ./render 4

To remove object file(s) and executable(s)
> make clean

To file the render report
> ./report/file_report.sh

It can be filed only with the 5 confirmation codes: exercise N reveals
code N when its result is the expected one.
