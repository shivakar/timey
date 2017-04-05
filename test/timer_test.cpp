#include <iostream>
#include <iomanip>
#include <sstream>
#include <thread>
#include "gtest/gtest.h"

#include "timey.hpp"

TEST(TimeyTimerTest, Constructor) {
    timey::Timer t;
    EXPECT_EQ(t.running(), false);
    EXPECT_EQ(t.Elapsed().count(), 0);
    EXPECT_EQ(t.count(), (size_t)0);
    EXPECT_EQ(t.name(), "");

    timey::Timer tn("timer1");
    EXPECT_EQ(tn.running(), false);
    EXPECT_EQ(tn.Elapsed().count(), 0);
    EXPECT_EQ(tn.count(), (size_t)0);
    EXPECT_EQ(tn.name(), "timer1");
}

TEST(TimeyTimerTest, StartStopElapsedReset) {
    timey::Timer t;

    t.Start();
    std::this_thread::sleep_for(10 * timey::Millisecond);
    EXPECT_EQ(t.running(), true);
    t.Stop();

    EXPECT_EQ(t.running(), false);
    EXPECT_GT(t.Elapsed(), 10 * timey::Millisecond);
    EXPECT_NEAR(t.Elapsed().count(), 10e6, 5e6);
    EXPECT_EQ(t.count(), (size_t)1);

    t.Reset();
    EXPECT_EQ(t.running(), false);
    EXPECT_EQ(t.Elapsed().count(), 0);
    EXPECT_EQ(t.count(), (size_t)0);
}

TEST(TimeyTimerTest, Restart) {
    timey::Timer t;
    for (int i = 0; i < 10; i++) {
        t.Start();
        std::this_thread::sleep_for(timey::Millisecond);
        t.Stop();
    }
    EXPECT_EQ(t.count(), (size_t)10);
    EXPECT_NEAR(t.Elapsed().count(), 1e6, 5e5);

    t.Reset();
    t.Start();
    for (int i = 0; i < 10; i++) {
        t.Restart();
        std::this_thread::sleep_for(timey::Millisecond);
    }
    t.Stop();
    EXPECT_EQ(t.count(), (size_t)11);
    EXPECT_NEAR(t.Elapsed().count(), 1e6, 5e5);
}

TEST(TimeyTimerTest, StartStopRestartExceptions) {
    timey::Timer t;
    t.Start();
    EXPECT_THROW(t.Start(), std::runtime_error);
    t.Stop();
    EXPECT_THROW(t.Stop(), std::runtime_error);
    EXPECT_THROW(t.Restart(), std::runtime_error);
}

TEST(TimeyTimerTest, WriteToStream) {
    using std::setw;
    using std::left;
    using std::endl;
    timey::Timer t;
    t.name("My Timer");
    t.Start();
    std::this_thread::sleep_for(10 * timey::Millisecond);
    t.Stop();
    std::ostringstream actual;
    actual << t;

    std::ostringstream expected;
    // Adding the header
    expected << setw(15) << left << "Timer" << setw(15) << "Count" << setw(20)
             << "Total" << endl;
    // Adding decorations and timer report
    expected << std::string(80, '-') << endl;
    expected << setw(15) << t.name() << setw(15) << t.count() << setw(20)
             << timey::Humanize(t.Elapsed()) << endl;
    expected << std::string(80, '-') << endl;

    EXPECT_EQ(actual.str(), expected.str());

    // Test using t.Report member function
    expected.clear();
    expected.str("");
    expected << setw(15) << t.name() << setw(15) << t.count() << setw(20)
             << timey::Humanize(t.Elapsed());
    EXPECT_EQ(t.Report(), expected.str());
}
