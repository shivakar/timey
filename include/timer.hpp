/// @file timer.hpp
///
/// Timer class
///
#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <chrono>
#include <cstdint>

#include "utils.hpp"

namespace timey {
namespace internal {
const std::string ReportHeader(void) {
    return "Timer" + std::string(10, ' ') + "Count" + std::string(10, ' ') +
           "Total" + std::string(15, ' ') + "Mean" + std::string(16, ' ');
}
}
/// Timer class is a wrapper around chrono::high_resolution_clock for timing
/// computations.
///
/// Example:
/// @code
///     Timer t;
///     for(size_t i = 0; i < n; i++) {
///         t.Start() // Start the timer;
///         compute_intensive_function();
///         t.Stop() // Stop the timer;
///     }
///     // Write the report to stdout
///     std::cout << t << std::endl;
/// @endcode
class Timer {
   public:
    Timer();
    Timer(const std::string name__);
    Timer(const Timer& t);
    ~Timer();

    // API Functions
    void Reset();
    void Start();
    void Stop();
    void Restart();
    NanosecondsType Elapsed() const;
    std::string Report() const;

    // Accessors
    /// Running returns true if the Timer is currently running, false otherwise.
    ///
    /// @retval TRUE If the timer is running
    /// @retval False Otherwise
    bool Running(void) const { return running_; }

    /// Count returns the number of times the Timer was started and stopped.
    ///
    /// @retval Number of times the Timer was started and stopped.
    size_t Count(void) const { return count_; }

    /// Name returns the name of the Timer.
    ///
    /// @retval Name of the Timer
    std::string Name(void) const { return name_; }

    // Mutators
    /// Name sets the name of the timer.
    ///
    /// @param [in] name__ Name of the Timer
    void Name(const std::string name__) { name_ = name__; }

    // Friend functions
    friend std::ostream& operator<<(std::ostream& out, const Timer& t);

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

Timer::Timer(const Timer& t)
    : running_(t.running_),
      count_(t.count_),
      totalTime_(t.totalTime_),
      name_(t.name_),
      startTime_(t.startTime_),
      stopTime_(t.stopTime_) {}

Timer::~Timer() {}

/// Reset resets the timer
///
inline void Timer::Reset() {
    running_ = false;
    count_ = 0;
    totalTime_ = std::chrono::nanoseconds(0);
}

/// Start starts an idle timer.
///
/// @throw std::runtime_error if the timer is already running.
inline void Timer::Start() {
    if (running_) {
        throw std::runtime_error("Start called on a running timer");
    }
    startTime_ = std::chrono::high_resolution_clock::now();
    running_ = true;
}

/// Stop stops a running timer.
///
/// @throw std::runtime_error if the timer is already idle.
inline void Timer::Stop() {
    if (!running_) {
        throw std::runtime_error("Stop called on an idle timer");
    }
    stopTime_ = std::chrono::high_resolution_clock::now();
    count_++;
    totalTime_ += stopTime_ - startTime_;
    running_ = false;
}

/// Restart is an alias for Stop + Start.
///
/// @throw std::runtime_error as per Stop and Stop rules.
inline void Timer::Restart() {
    Stop();
    Start();
}

/// Elapsed returns the total time the timer was running for in
/// duration of Nanoseconds.
///
/// @retval std::chrono::duration object in Nanoseconds
inline NanosecondsType Timer::Elapsed() const { return totalTime_; }

/// Report returns a std::string report of the timer without the header or
/// decorations.
///
/// @returns std::string report of the timer
inline std::string Timer::Report() const {
    using std::setw;
    using std::left;
    std::ostringstream out;

    out << setw(15) << left << name_ << setw(15) << count_ << setw(20)
        << Humanize(totalTime_) << setw(20) << Humanize(totalTime_ / count_);

    return out.str();
}

/// Operator overloading to write a Timer object to std::ostream
///
/// @param out std::outstream&
/// @param t const Timer&
/// @retval Updated std::ostream
std::ostream& operator<<(std::ostream& out, const Timer& t) {
    using std::setw;
    using std::endl;
    using std::left;
    out << internal::ReportHeader() << endl;
    out << std::string(80, '-') << endl;
    out << t.Report() << endl;
    out << std::string(80, '-') << endl;
    return out;
}
}
