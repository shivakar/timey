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

namespace internal {
std::string DoubleToFixedString(double d) {
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
