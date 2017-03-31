#include <chrono>

#include "gtest/gtest.h"

#include "timey.hpp"

TEST(HumanizeTest, default) {
    using std::cout;
    using std::endl;
    typedef std::chrono::duration<double> seconds_type;
    std::chrono::duration<double, std::nano> nanosecond(1);
    std::chrono::duration<double, std::micro> microsecond(1);
    std::chrono::duration<double, std::milli> millisecond(1);
    std::chrono::duration<double> second(1);
    std::chrono::duration<double, std::ratio<60>> minute(1);
    std::chrono::duration<double, std::ratio<60 * 60>> hour(1);

    std::vector<std::pair<seconds_type, std::string>> test_data = {
        std::make_pair(0 * second, "0s"),
        std::make_pair(1 * nanosecond, "1ns"),
        std::make_pair(123 * nanosecond, "123ns"),
        std::make_pair(32 * microsecond, "32us"),
        std::make_pair(999* microsecond, "999us")};

    for (auto test : test_data) {
        EXPECT_EQ(test.second, timey::Humanize(test.first));
    }
}
