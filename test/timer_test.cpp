#include <thread>
#include "gtest/gtest.h"

#include "timey.hpp"

TEST(TimeyTimerTest, Constructor) {
    timey::Timer t;
    EXPECT_EQ(t.running(), false);
    EXPECT_EQ(t.Elapsed().count(), 0);
    EXPECT_EQ(t.count(), 0);
}

TEST(TimeyTimerTest, StartStopElapsedReset) {
    timey::Timer t;

    t.Start();
    std::this_thread::sleep_for(10 * timey::Millisecond);
    EXPECT_EQ(t.running(), true);
    t.Stop();

    EXPECT_EQ(t.running(), false);
    EXPECT_GT(t.Elapsed(), 10 * timey::Millisecond);
    EXPECT_NEAR(t.Elapsed().count(), 10e6, 1e6);
    EXPECT_EQ(t.count(), 1);

    t.Reset();
    EXPECT_EQ(t.running(), false);
    EXPECT_EQ(t.Elapsed().count(), 0);
    EXPECT_EQ(t.count(), 0);
}

TEST(TimeyTimerTest, Restart) {
    timey::Timer t;
    for (int i = 0; i < 10; i++) {
        t.Start();
        std::this_thread::sleep_for(timey::Millisecond);
        t.Stop();
    }
    EXPECT_EQ(t.count(), 10);
    EXPECT_NEAR(t.Elapsed().count(), 1e6, 2e5);

    t.Reset();
    t.Start();
    for (int i = 0; i < 10; i++) {
        t.Restart();
        std::this_thread::sleep_for(timey::Millisecond);
    }
    t.Stop();
    EXPECT_EQ(t.count(), 11);
    EXPECT_NEAR(t.Elapsed().count(), 1e6, 2e5);
}

TEST(TimeyTimerTest, StartStopRestartExceptions) {
    timey::Timer t;
    t.Start();
    EXPECT_THROW(t.Start(), std::runtime_error);
    t.Stop();
    EXPECT_THROW(t.Stop(), std::runtime_error);
    EXPECT_THROW(t.Restart(), std::runtime_error);
}
