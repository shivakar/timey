## Todos for Timey

`Timer` functionality:

* [ x ] Write a fixed format report to an `ostream`.

`TimerSet` functionality:

* `Vector` to hold multiple timers by name.
* Add and delete timers by name.
* Start, stop and restart a given timer by name.
* Start, stop and restart all timers.
* Write a fixed format report of all the timers.


## Undecided functionality from proposal

`Timer` functionality:

* When was the timer last started?
* When was the timer last stopped?
* How many times (count) was the timer started (and stopped)?
* What are the min, max, mean and std. dev. times for the timer?
* What are the indices of the min and max indices?
* Keep track of min, max and their indices only if requested.
* If needed, store the actual elapsed time of each iteration.
    * For performance, have the ability to preallocate enough memory to store
      the times
* Write a fixed format detailed report to an `ostream`.

`TimerSet` functionality:

* Write a fixed format detailed report to an `ostream`.
