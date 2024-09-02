#include "Real_Double.h"
#include "gtest/gtest.h"

using alg::num::Real;


struct Operation
{
    double l_op;
    double r_op;
    double res;
};

class RealTests : public ::testing::TestWithParam<Operation> 
{
public:
    void InitOperands(double r_op, double l_op) { this->r_op = Real<double>(r_op); this->l_op = Real<double>(l_op); }
protected:
    Real<double> r_op, l_op;
};

//*************************************************************SUM*************************************************************//

class RealSumTests : public RealTests {};

TEST_P(RealSumTests, sum_of_two_real_numbers)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = r_op + l_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, RealSumTests, ::testing::Values(Operation{1,1,2}, Operation{3,4,7}, Operation{34.2,56.1,90.3}));

//*************************************************************SUB*************************************************************//

class RealSubTests : public RealTests {};

TEST_P(RealSubTests, sub_of_two_real_numbers)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = r_op - l_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, RealSubTests, ::testing::Values(Operation{1,1,0}, Operation{3,4,-1}, Operation{34.2,56.1,-21.9}));

//*************************************************************MUL*************************************************************//

class RealMulTests : public RealTests {};

TEST_P(RealMulTests, mul_of_two_real_numbers)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = r_op * l_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, RealMulTests, ::testing::Values(Operation{1,1,1}, Operation{3,4,12}, Operation{34.2,56.1,1918.62}));

//*************************************************************DIV*************************************************************//

class RealDivTests : public RealTests {};

TEST_P(RealDivTests, div_of_two_real_numbers)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = r_op / l_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, RealDivTests, ::testing::Values(Operation{1,1,1}, Operation{3,4,0.75}, Operation{34,16,2.125}));



TEST(sd,ds)
{
    constexpr Real<double> var1 = 5.6;

    constexpr Real<double> var2(var1);
    constexpr Real<double> var3(Real<double>(5.3));
}