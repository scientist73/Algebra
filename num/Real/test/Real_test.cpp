#include "Real.h"
#include "gtest/gtest.h"

using alg::num::Real;


TEST(Real, OperatorA_test)
{
    const long double x1 = 5.6;
    const long double x2 = 8.2;

    Real<long double> var1(x1);
    Real<long double> var2(x2);

    EXPECT_DOUBLE_EQ((var1+var2).real(), x1 + x2);
    EXPECT_DOUBLE_EQ((var1-var2).real(), x1 - x2);
    EXPECT_DOUBLE_EQ((var1*var2).real(), x1 * x2);
    EXPECT_DOUBLE_EQ((var1/var2).real(), x1 / x2);
}

TEST(Real, OperatorA_EQ_test)
{
    long double x1 = 5.6;
    long double x2 = 8.2;

    Real<long double> var1(x1);
    Real<long double> var2(x2);

    var1 += var2; x1 += x2; EXPECT_DOUBLE_EQ((var1).real(), x1);
    var1 -= var2; x1 -= x2; EXPECT_DOUBLE_EQ((var1).real(), x1);
    var1 *= var2; x1 *= x2; EXPECT_DOUBLE_EQ((var1).real(), x1);
    var1 /= var2; x1 /= x2; EXPECT_DOUBLE_EQ((var1).real(), x1);
}