//
// Created by Edge51 on 7/23/23.
//

#include  <gtest/gtest.h>

#include "ThreadPoolTest.h"
#include "../include/ThreadPool.h"


TEST(ThreadPoolTest, ThreadPoolTest)
{
    EXPECT_STRNE("hello", "world");
    EXPECT_EQ(7 * 6, 42);
}

TEST(ThreadPoolTest, SayHello)
{
    ThreadPool threadPool(1);
    EXPECT_STREQ("hello", threadPool.SayHello().c_str());
}