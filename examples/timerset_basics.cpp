/// @file timerset_basics.cpp
///
/// Example demonstrating the basic usage of the TimerSet class.
///
#include <chrono>
#include <iostream>
#include <thread>

#include "timey.hpp"

void task_1(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(200));
}
void task_2(void) {
    std::this_thread::sleep_for(std::chrono::milliseconds(150));
}

int main(void) {
    // Simplest usage
    // Create a TimerSet
    timey::TimerSet ts;

    // Add a timer to the timerset
    ts.Add("timer1");
    // Add another timer to the timerset
    ts.Add("timer2");

    // Do some task 1 and use "timer1" to keep track of the duration
    ts.Start("timer1");
    task_1();
    ts.Stop("timer1");

    // Do task 2 and use "timer2" to keep track of the duration;
    ts.Start("timer2");
    task_2();
    ts.Stop("timer2");

    // Add another timer
    ts.Add("timer3");
    for (int i = 0; i < 10; i++) {
        ts.Start("timer3");
        std::this_thread::sleep_for(timey::Millisecond);
        ts.Stop("timer3");
    }

    // Print the TimerSet report
     std::cout << ts << std::endl;
}
