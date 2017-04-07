/// @file utils.hpp
///
/// Utility functions for working with durations.
///
#pragma once

#include <iomanip>
#include <chrono>
#include <cstdint>
#include <sstream>

namespace timey {
typedef std::chrono::duration<int64_t, std::nano> NanosecondsType;
typedef std::chrono::duration<int64_t, std::micro> MicrosecondsType;
typedef std::chrono::duration<int64_t, std::milli> MillisecondsType;
typedef std::chrono::duration<int64_t> SecondsType;
typedef std::chrono::duration<int64_t, std::ratio<60>> MinutesType;
typedef std::chrono::duration<int64_t, std::ratio<60 * 60>> HoursType;

constexpr NanosecondsType Nanosecond(1);
constexpr MicrosecondsType Microsecond(1);
constexpr MillisecondsType Millisecond(1);
constexpr SecondsType Second(1);
constexpr MinutesType Minute(1);
constexpr HoursType Hour(1);
constexpr SecondsType ZeroSeconds(0);

/// Internal namespace for internal use only functions.
///
namespace internal {

/// DoubleToFixedString returns string representation of double 'd' without
/// trailing zeros.
///
/// Where precision of d is <= 9
///
/// @param d double
/// @return std::string
std::string DoubleToFixedString(const double& d) {
    std::ostringstream out;

    out << std::fixed << std::setprecision(9) << d;
    std::string astr = out.str();
    std::size_t idx = astr.find_last_not_of("0");
    if (astr[idx] != '.') {
        idx += 1;
    }
    astr.erase(astr.begin() + idx, astr.end());

    return astr;
}
}

/// Humanize returns a human readable string representation of a duration.
///
/// For durations less than a second, the string representation will be in
/// milli, micro or nanoseconds, which ever is the highest scale to keep the
/// value of the duration between 1 and 999.
///
/// E.g. 0.001s       = 1ms
///      0.000001s    = 1us
///      0.000000001s = 1ns
///
/// For durations greater than a second, the string representation will be in
/// hours, minutes, and/or seconds.
///
/// E.g. 3665.005s = 1h1m5.005s
///      7200s     = 1h
///
/// Maximum duration that can be formatted using the function is
/// ((1<<63)-1) nanoseconds or 2562047h47m16.854775807s
///
/// Special cases are:
///      0s        = 0s (even though 0ns would still be correct)
///
/// @param dur std::chrono::duration
/// @return std::string
template <class T1, class T2>
std::string Humanize(const std::chrono::duration<T1, T2>& dur) {
    using std::chrono::duration_cast;
    using std::chrono::duration;

    std::ostringstream out;
    int64_t i;
    auto d = duration_cast<NanosecondsType>(dur);

    if (d == ZeroSeconds) {
        out << "0s";
    } else if (d < Second) {
        if (d >= Millisecond) {
            out << (duration_cast<duration<double, std::milli>>(d)).count()
                << "ms";
        } else if (d >= Microsecond) {
            out << (duration_cast<duration<double, std::micro>>(d)).count()
                << "us";
        } else {
            out << (duration_cast<duration<double, std::nano>>(d)).count()
                << "ns";
        }
    } else {
        if (d >= Hour) {
            i = (duration_cast<HoursType>(d)).count();
            out << i << "h";
            d -= i * Hour;
        }
        if (d >= Minute) {
            i = (duration_cast<MinutesType>(d)).count();
            out << i << "m";
            d -= i * Minute;
        }
        if (d != ZeroSeconds) {
            out << internal::DoubleToFixedString(
                       (duration_cast<duration<double>>(d)).count()) << "s";
        }
    }

    return out.str();
}
}
