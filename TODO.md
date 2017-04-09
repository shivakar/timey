## Todos for Timey

`Timer` functionality:

* [ x ] Write a fixed format report to an `ostream`.
* [ x ] Add mean time to Timer.
* Add Std. Dev. time to Timer.
* Update report to include [ x ] mean and std. dev.

`TimerSet` functionality:

* [ x ] `Vector` to hold multiple timers by name.
* [ x ] Add and [ x ] delete timers by name.
* [ x ] Start, [ x ] stop and [ x ] restart a given timer by name.
* [ x ] Write a fixed format report of all the timers.


## Undecided functionality from proposal

`Timer` functionality:

* When was the timer last started?
* When was the timer last stopped?
* What are the min, max, mean and std. dev. times for the timer?
* What are the indices of the min and max indices?
* Keep track of min, max and their indices only if requested.
* If needed, store the actual elapsed time of each iteration.
    * For performance, have the ability to preallocate enough memory to store
      the times
* Write a fixed format detailed report to an `ostream`.

`TimerSet` functionality:

* Start, stop and restart all timers.
* Write a fixed format detailed report to an `ostream`.
