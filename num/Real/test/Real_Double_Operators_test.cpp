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
    void InitOperands(double l_op, double r_op) { this->l_op = Real<double>(l_op); this->r_op = Real<double>(r_op); }
protected:
    Real<double> l_op, r_op;
};

//*************************************************************SUM*************************************************************//

class sum_of_two_real_numbers : public RealTests {};

TEST_P(sum_of_two_real_numbers, Default)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}
INSTANTIATE_TEST_SUITE_P(Default, sum_of_two_real_numbers, ::testing::Values(
    Operation{1,1,2}, 
    Operation{3,4,7}, 
    Operation{34.2,56.1,90.3}
));

//*************************************************************SUB*************************************************************//

class sub_of_two_real_numbers : public RealTests {};

TEST_P(sub_of_two_real_numbers, Default)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}
INSTANTIATE_TEST_SUITE_P(Default, sub_of_two_real_numbers, ::testing::Values(
    Operation{1,1,0}, 
    Operation{3,4,-1}, 
    Operation{34.2,56.1,-21.9}
));

//*************************************************************MUL*************************************************************//

class mul_of_two_real_numbers : public RealTests {};

TEST_P(mul_of_two_real_numbers, Default)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, mul_of_two_real_numbers, ::testing::Values(Operation{1,1,1}, Operation{3,4,12}, Operation{34.2,56.1,1918.62}));

//*************************************************************DIV*************************************************************//

class div_of_two_real_numbers : public RealTests {};

TEST_P(div_of_two_real_numbers, Default)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    Real<double> res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.real(), GetParam().res);
}

INSTANTIATE_TEST_SUITE_P(Default, div_of_two_real_numbers, ::testing::Values(Operation{1,1,1}, Operation{3,4,0.75}, Operation{34,16,2.125}));