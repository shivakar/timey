#include <chrono>

#include "gtest/gtest.h"

#include "timey.hpp"

TEST(TimeyInternalTest, DoubleToFixedString) {
    std::vector<std::pair<double, std::string>> test_data = {
        std::make_pair(0, "0"), std::make_pair(0.0, "0"),
        std::make_pair(1.0, "1"), std::make_pair(2.01, "2.01"),
        std::make_pair(12.000004, "12.000004"),
        std::make_pair(123.000007, "123.000007"),
        std::make_pair(1e-9, "0.000000001"),
        std::make_pair(77580.000000001, "77580.000000001")
        // End of test_data
    };

    for (auto test : test_data) {
        EXPECT_EQ(timey::internal::DoubleToFixedString(test.first),
                  test.second);
    }
}

TEST(TimeyTest, HumanizeDuration) {
    std::vector<std::pair<timey::NanosecondsType, std::string>> test_data = {
        std::make_pair(0 * timey::Second, "0s"),
        std::make_pair(1 * timey::Nanosecond, "1ns"),
        std::make_pair(123 * timey::Nanosecond, "123ns"),
        std::make_pair(32 * timey::Microsecond, "32us"),
        std::make_pair(999 * timey::Microsecond, "999us"),
        std::make_pair(1000 * timey::Microsecond, "1ms"),
        std::make_pair(250 * timey::Millisecond, "250ms"),
        std::make_pair(2500 * timey::Millisecond, "2.5s"),
        std::make_pair(12 * timey::Second, "12s"),
        std::make_pair(120 * timey::Second, "2m"),
        std::make_pair(1 * timey::Minute + timey::Microsecond, "1m0.000001s"),
        std::make_pair(
            45 * timey::Minute + 12 * timey::Second + timey::Nanosecond,
            "45m12.000000001s"),
        std::make_pair(90 * timey::Minute, "1h30m"),
        std::make_pair(2 * timey::Hour, "2h"),
        std::make_pair(100 * timey::Hour + 90 * timey::Minute +
                           5 * timey::Second + 5 * timey::Millisecond +
                           1 * timey::Microsecond + 4 * timey::Nanosecond,
                       "101h30m5.005001004s"),
        std::make_pair(((1UL << 63) - 1) * timey::Nanosecond,
                       "2562047h47m16.854775807s")
        // End of test_data
    };

    for (auto test : test_data) {
        EXPECT_EQ(timey::Humanize(test.first), test.second);
    }
}
