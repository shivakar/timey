#include <thread>
#include "timey.hpp"
#include "gtest/gtest.h"

TEST(TimeyTimerSetTest, Constructor) {
    timey::TimerSet ts;

    EXPECT_EQ(ts.Count(), (size_t)0);
}

TEST(TimeyTimerSetTest, Add) {
    timey::TimerSet ts;
    ts.Add("timer1");
    EXPECT_EQ(ts.Count(), (size_t)1);
    ts.Add("timer2");
    ts.Add("timer3");
    EXPECT_EQ(ts.Count(), (size_t)3);
    EXPECT_THROW(ts.Add("timer1"), std::runtime_error);

    timey::Timer t1("timer1");
    timey::Timer t2("timer2");
    timey::TimerSet ts2;
    ts2.Add(t1);
    ts2.Add(t2);
    EXPECT_EQ(ts2.Count(), (size_t)2);

    timey::Timer t3("timer1");  // "timer1" name is already taken in ts2
    EXPECT_THROW(ts2.Add(t3), std::runtime_error);
    EXPECT_THROW(ts2.Add(t1), std::runtime_error);
}

TEST(TimeyTimerSetTest, Delete) {
    timey::TimerSet ts;
    ts.Add("timer1");
    ts.Add("timer2");

    ts.Delete("timer1");
    EXPECT_EQ(ts.Count(), (size_t)1);

    ts.Delete("timer2");
    EXPECT_EQ(ts.Count(), (size_t)0);

    EXPECT_THROW(ts.Delete("timer2"), std::runtime_error);
}

TEST(TimeyTimerSetTest, Get) {
    timey::TimerSet ts;
    ts.Add("timer1");

    auto& t = ts.Get("timer1");
    ts.Start("timer1");
    std::this_thread::sleep_for(timey::Millisecond);
    ts.Stop("timer1");

    EXPECT_EQ(t.Name(), "timer1");
    EXPECT_EQ(t.Count(), 1);
    EXPECT_GT(t.Elapsed().count(), 0);

    ts.Start("timer1");
    std::this_thread::sleep_for(timey::Millisecond);
    ts.Stop("timer1");

    EXPECT_EQ(t.Count(), 2);

    EXPECT_EQ(ts.Running(), false);
    t.Start();
    EXPECT_EQ(ts.Running(), true);
    t.Stop();
}

TEST(TimeyTimerSetTest, StartStopRestart) {
    timey::TimerSet ts;
    ts.Add("timer1");
    ts.Add("timer2");

    EXPECT_EQ(ts.Running(), false);

    ts.Start("timer1");
    EXPECT_EQ(ts.Running(), true);
    ts.Stop("timer1");

    ts.Start("timer2");
    EXPECT_THROW(ts.Start("timer2"), std::runtime_error);
    EXPECT_THROW(ts.Stop("timer1"), std::runtime_error);

    ts.Restart("timer2");
    ts.Stop("timer2");

    auto& t = ts.Get("timer2");
    EXPECT_EQ(t.Count(), 2);

    EXPECT_THROW(ts.Start("unknown"), std::runtime_error);
    EXPECT_THROW(ts.Stop("unknown"), std::runtime_error);
    EXPECT_THROW(ts.Restart("unknown"), std::runtime_error);
    EXPECT_THROW(ts.Get("unknown"), std::runtime_error);
}

TEST(TimeyTimerSetTest, Reset) {
    timey::TimerSet ts;
    ts.Add("timer1");
    ts.Add("timer2");

    ts.Start("timer1");
    std::this_thread::sleep_for(timey::Millisecond);
    ts.Stop("timer1");

    auto& t = ts.Get("timer1");
    EXPECT_EQ(t.Count(), 1);
    EXPECT_GT(t.Elapsed(), timey::Millisecond);

    ts.Reset("timer1");
    EXPECT_EQ(t.Count(), 0);
    EXPECT_EQ(t.Elapsed().count(), 0);

    EXPECT_THROW(ts.Reset("unknown"), std::runtime_error);
}
