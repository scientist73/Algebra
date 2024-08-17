#include "NumType.h"
#include "gtest/gtest.h"
#include <cstdlib>

using alg::num::NumType;

TEST(Real_NumType, SumTest)
{
    NumType var1 = NumType::constructReal("4.5");
    NumType var2 = NumType::constructReal("4.5");

    NumType sum = var1 + var2;

    EXPECT_EQ(strtold(sum.getString().c_str(), 0), strtold("9.0", 0));
}