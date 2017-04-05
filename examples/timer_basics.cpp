/// @file timer_basics.cpp
///
/// Example demonstrating the basic usage of the Timer class.
///
#include <chrono>
#include <iostream>
#include <iostream>
#include <thread>

#include "timey.hpp"

int main(void) {
    // Simplest usage
    timey::Timer my_timer;

    my_timer.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    my_timer.Stop();

    std::cout << "Total Elapsed: " << my_timer.Elapsed().count() << "ms"
              << std::endl;
    std::cout << my_timer << std::endl;

    // A named timer
    // The name of the timer will be used when printing the timer
    timey::Timer named_timer("Timer1");
    named_timer.Start();
    std::this_thread::sleep_for(30 * timey::Millisecond);
    named_timer.Stop();
    std::cout << "Total Elapsed: " << named_timer.Elapsed().count() << "ms"
              << std::endl;
    std::cout << named_timer << std::endl;

    return 0;
}
