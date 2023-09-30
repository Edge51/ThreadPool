//
// Created by Edge51 on 7/23/23.
//

#include  <gtest/gtest.h>

#include "ThreadPoolTest.h"
#include "../include/ThreadPool.h"


TEST(ThreadPoolTest, Initialize)
{
    ThreadPool threadPool(10);
    EXPECT_EQ(threadPool.Size(), 10);
}