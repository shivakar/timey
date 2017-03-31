#pragma once

#include <chrono>

namespace timey {
class Timer {
   public:
    Timer();
    ~Timer();

    void Reset();
    void Start();
    void Stop();
    void Restart();
    std::chrono::duration<double> Elapsed();

   private:
    bool running;
    size_t count;
    std::chrono::duration<double> totalTime;

    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
};

Timer::Timer() : running(false), count(0), totalTime(0){}

Timer::~Timer() {
    if (running) {
        std::cerr << "Destroying a running timer" << std::endl;
    }
}

inline void Timer::Reset() {
    running = false;
    count = 0;
    totalTime = std::chrono::duration<double>::zero();
}

inline void Timer::Start() {
    if (running) {
        throw std::runtime_error("Start called on a running timer");
    }
    startTime = std::chrono::high_resolution_clock::now();
    running = true;
}

inline void Timer::Stop() {
    if (!running) {
        throw std::runtime_error("Stop called on a stopped timer");
    }
    stopTime = std::chrono::high_resolution_clock::now();
    count++;
    totalTime = stopTime - startTime;
    running = false;
}

inline std::chrono::duration<double> Timer::Elapsed() {
    return totalTime;
}
}
