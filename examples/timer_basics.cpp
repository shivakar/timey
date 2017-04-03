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
    timey::Timer my_timer;

    my_timer.Start();
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    my_timer.Stop();

    std::cout << "Total Elapsed: " << my_timer.Elapsed().count() << std::endl;

    return 0;
}
