#include "ScalarType.h"
#include "gtest/gtest.h"

using alg::num::StdScalarType;

TEST(StdScalarType, OperatorA_test)
{
    const long double x1 = 5.6;
    const long double x2 = 8.2;

    StdScalarType var1(x1);
    StdScalarType var2(x2);

    EXPECT_DOUBLE_EQ((var1+var2).scalar(), x1 + x2);
    EXPECT_DOUBLE_EQ((var1-var2).scalar(), x1 - x2);
    EXPECT_DOUBLE_EQ((var1*var2).scalar(), x1 * x2);
    EXPECT_DOUBLE_EQ((var1/var2).scalar(), x1 / x2);
}

TEST(StdScalarType, OperatorA_EQ_test)
{
    long double x1 = 5.6;
    long double x2 = 8.2;

    StdScalarType var1(x1);
    StdScalarType var2(x2);

    var1 += var2; x1 += x2; EXPECT_DOUBLE_EQ((var1).scalar(), x1);
    var1 -= var2; x1 -= x2; EXPECT_DOUBLE_EQ((var1).scalar(), x1);
    var1 *= var2; x1 *= x2; EXPECT_DOUBLE_EQ((var1).scalar(), x1);
    var1 /= var2; x1 /= x2; EXPECT_DOUBLE_EQ((var1).scalar(), x1);
}