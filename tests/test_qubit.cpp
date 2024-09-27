#include <gtest/gtest.h>
#include "qubit.h"

TEST(QubitTest, TestInitialState)
{
    Qubit qubit;
    EXPECT_EQ(qubit.measure(), 0);
}

TEST(QubitTest, TestCustomState)
{
    Qubit qubit({0, 0}, {1, 0});
    EXPECT_EQ(qubit.measure(), 1);
}
