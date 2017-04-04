/// @file timer.hpp
///
/// Timer class
///
#pragma once

#include <iostream>
#include <stdexcept>
#include <chrono>
#include <cstdint>

#include "utils.hpp"

namespace timey {
/// Timer class is a wrapper around chrono::high_resolution_clock for timing
/// computations.
///
/// Example:
///     Timer t;
///     for(size_t i = 0; i < n; i++) {
///         t.Start() // Start the timer;
///         compute_intensive_function();
///         t.Stop() // Stop the timer;
///     }
///     // Write the report to stdout
///     std::cout << t << std::endl;
///
class Timer {
   public:
    Timer();
    Timer(const std::string name__);
    ~Timer();

    // API Functions
    void Reset();
    void Start();
    void Stop();
    void Restart();
    NanosecondsType Elapsed();

    // Accessors
    bool running(void) { return running_; }
    size_t count(void) { return count_; }
    std::string name(void) { return name_; }

    // Mutators
    void name(const std::string name__) { name_ = name__; }

   private:
    bool running_;
    /// count_ is the number of times the timer was started
    ///
    size_t count_;
    /// totalTime_ is the total duration of time that the timer
    /// was running.
    NanosecondsType totalTime_;
    std::string name_;

    std::chrono::high_resolution_clock::time_point startTime_;
    std::chrono::high_resolution_clock::time_point stopTime_;
};

Timer::Timer() : running_(false), count_(0), totalTime_(0) {}

Timer::Timer(const std::string name__)
    : running_(false), count_(0), totalTime_(0), name_(name__) {}

Timer::~Timer() {}

/// Reset - resets the timer
///
inline void Timer::Reset() {
    running_ = false;
    count_ = 0;
    totalTime_ = std::chrono::nanoseconds(0);
}

/// Start - starts an idle timer.
///
/// Throws a std::runtime_error if the timer is already running.
inline void Timer::Start() {
    if (running_) {
        throw std::runtime_error("Start called on a running timer");
    }
    startTime_ = std::chrono::high_resolution_clock::now();
    running_ = true;
}

/// Stop - stops a running timer.
///
/// Throws a std::runtime_error if the timer is already idle.
inline void Timer::Stop() {
    if (!running_) {
        throw std::runtime_error("Stop called on an idle timer");
    }
    stopTime_ = std::chrono::high_resolution_clock::now();
    count_++;
    totalTime_ = stopTime_ - startTime_;
    running_ = false;
}

/// Restart is an alias for Stop + Start.
///
/// Throws std::runtime_error as per Stop and Stop rules.
inline void Timer::Restart() {
    Stop();
    Start();
}

/// Elapsed returns the total time the timer was running for in
/// duration of Nanoseconds.
inline NanosecondsType Timer::Elapsed() { return totalTime_; }                           
}
