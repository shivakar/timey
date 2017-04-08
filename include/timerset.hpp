/// @file timerset.hpp
///
/// TimerSet class
///
#pragma once

#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <map>

#include "utils.hpp"
#include "timer.hpp"

namespace timey {
/// TimerSet class is a container for Timer objects.
///
/// Example:
/// @code
///     TimerSet ts;
///     ts.Add("timer1");
///     ts.Add("timer2");
///
///     for(size_t i = 0; i < n; i++) {
///         ts.Start("timer1");
///         compute_intensive_function_1();
///         ts.Stop("timer1");
///     }
///     ts.Start("timer2");
///     compute_intensive_function_2();
///     ts.Stop("timer2");
///
///     // Write the timing report to stdout
///     std::cout << ts << std::endl;
/// @endcode
class TimerSet {
   public:
    TimerSet();
    ~TimerSet();

    // API
    size_t Count(void) const;
    bool Running(void) const;
    void Add(const std::string& timer_name);
    void Add(const Timer& timer);
    void Delete(const std::string& timer_name);
    void Start(const std::string& timer_name);
    void Stop(const std::string& timer_name);
    void Restart(const std::string& timer_name);
    void Reset(const std::string& timer_name);
    Timer& Get(const std::string& timer_name);

    // Friend functions
    friend std::ostream& operator<<(std::ostream& out, const TimerSet& t);

   private:
    bool Contains_(const std::string& timer_name) const;
    std::map<std::string, Timer> timers_;
};

TimerSet::TimerSet() {}

TimerSet::~TimerSet() {}

/// Contains_ returns true if a timer with the provided name exists in the
/// TimerSet, false otherwise.
/// Contains_ is a private function and should not be used by end users.
///
/// @param timer_name Name of the Timer
///
/// @retval TRUE if a timer with name 'timer_name' exists in the TimerSet
/// @retval FALSE otherwise
inline bool TimerSet::Contains_(const std::string& timer_name) const {
    if (timers_.find(timer_name) == timers_.end()) {
        return false;
    }
    return true;
}

/// Count returns the count of timers in the TimerSet
///
/// @retval Number of timers in the TimerSet
inline size_t TimerSet::Count(void) const { return timers_.size(); }

/// Running returns true if any of the timers in the TimerSet are currently
/// running, false otherwise.
///
/// @retval TRUE if any of the timers in the TimerSet are running
/// @retval FALSE otherwise
inline bool TimerSet::Running(void) const {
    for (auto t : timers_) {
        if (t.second.Running()) {
            return true;
        }
    }
    return false;
}

/// Add (const std::string& timer_name) adds a new timer to the TimerSet
/// with name 'timer_name'.
/// Add creates a new Timer object with the given name and then adds it to
/// self.
///
/// @throw std::runtime_error if a timer with the provided name already exists
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Add(const std::string& timer_name) {
    if (Contains_(timer_name)) {
        throw std::runtime_error("Duplicate Timer '" + timer_name + "'");
    }
    Timer t(timer_name);
    timers_.insert({timer_name, t});
}

/// Add (const Timer& t) adds an existing timer to the TimerSet.
///
/// @throw std::runtime_error if a timer with the provided name already exists
/// in the TimerSet
///
/// @param [in] Timer
void TimerSet::Add(const Timer& t) {
    if (Contains_(t.Name())) {
        throw std::runtime_error("Duplicate Timer '" + t.Name() + "'");
    }
    timers_.insert({t.Name(), t});
}

/// Delete deletes a timer in the TimerSet by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Delete(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    timers_.erase(timer_name);
}

/// Start starts a timer in the TimerSet by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Start(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    timers_[timer_name].Start();
}

/// Stop stops a timer in the TimerSet by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Stop(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    timers_[timer_name].Stop();
}

/// Restart restarts a timer in the TimerSet by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Restart(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    timers_[timer_name].Restart();
}

/// Reset resets a timer in the TimerSet to its initial state by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
void TimerSet::Reset(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    timers_[timer_name].Reset();
}

/// Get returns a timer in the TimerSet by name.
///
/// @throw std::runtime_error if a timer with the provided name does not exist
/// in the TimerSet
///
/// @param [in] timer_name Name of the timer
///
/// @retval Timer object with the given timer_name
Timer& TimerSet::Get(const std::string& timer_name) {
    if (!Contains_(timer_name)) {
        throw std::runtime_error("Invalid Timer '" + timer_name + "'");
    }
    return timers_.find(timer_name)->second;
}

/// Operator overloading to write a TimerSet object to std::ostream
///
/// @param out Output Stream
/// @param ts TimerSet object
/// @retVal Updated output stream
std::ostream& operator<<(std::ostream& out, const TimerSet& ts) {
    using std::setw;
    using std::endl;
    using std::left;
    out << left;

    // Report header is defined in Timer.hpp
    out << internal::ReportHeader() << endl;
    out << std::string(80, '-') << endl;
    for (auto& t : ts.timers_) {
        out << t.second.Report() << endl;
    }
    out << std::string(80, '-') << endl;

    return out;
}
}
