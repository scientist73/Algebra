#include "gtest/gtest.h"
#include "Calculator.h"
#include <string>
#include <memory>

using alg::calc::Calculator;


void AssertNum(const NumType<double>& l_op, const NumType<double>& r_op)
{
    if (l_op.getNumType() == r_op.getNumType())
    {
        switch (l_op.getNumType())
        {
        case NUM::REAL:
            ASSERT_DOUBLE_EQ(get_num<Real<double>>(l_op).real(), get_num<Real<double>>(r_op).real());
            break;
        case NUM::COMPLEX:
            ASSERT_DOUBLE_EQ(get_num<Complex<double>>(l_op).real(), get_num<Complex<double>>(r_op).real());
            ASSERT_DOUBLE_EQ(get_num<Complex<double>>(l_op).imag(), get_num<Complex<double>>(r_op).imag());
            break;
        }
    }
    else
        FAIL();
}

class CalculatorTests
{
public:
    void InitCalculator() { calc.reset(new Calculator<double>()); }
protected:
    std::unique_ptr<Calculator<double>> calc;
};


struct Expression
{
    std::string expr;
    NumType<double> res;
};
class calculate_correct_expression : public CalculatorTests, public ::testing::TestWithParam<Expression> {};
TEST_P(calculate_correct_expression, Default)
{
    InitCalculator();

    calc->setupInputString(GetParam().expr);
    NumType<double> res = calc->calculate();

    AssertNum(res, GetParam().res);
}
INSTANTIATE_TEST_SUITE_P(simple_real_num_expr, calculate_correct_expression, ::testing::Values(
    Expression{"4", NumType<double>(Real<double>(4))},
    Expression{"2+5", NumType<double>(Real<double>(7))},
    Expression{"2-5", NumType<double>(Real<double>(-3))},
    Expression{"2.4*5", NumType<double>(Real<double>(12))},
    Expression{"5.5/0.5", NumType<double>(Real<double>(11))}
));
INSTANTIATE_TEST_SUITE_P(simple_complex_num_expr, calculate_correct_expression, ::testing::Values(
    Expression{"2+4i", NumType<double>(Complex<double>(2, 4))},
    Expression{"2+4i + 3+5i", NumType<double>(Complex<double>(5, 9))},
    Expression{"6-4i - 3+7i", NumType<double>(Complex<double>(3, 3))},
    Expression{"(4+6i)*(1-2i)", NumType<double>(Complex<double>(16, -2))},
    Expression{"(4+6i)/(1-2i)", NumType<double>(Complex<double>(-1.6, 2.8))}
));
INSTANTIATE_TEST_SUITE_P(complicated_expr, calculate_correct_expression, ::testing::Values(
    Expression{"2.2 * (4.5 + i)", NumType<double>(Complex<double>(9.9, 2.2))},
    Expression{"(4.5/2 + 5.6 * 2) / 4 - (5.6 + 5.2i) * (4.5 + i)", NumType<double>(Complex<double>(-16.6375, -29))}
));
INSTANTIATE_TEST_SUITE_P(spaces_between_numbers_is_not_important, calculate_correct_expression, ::testing::Values(
    Expression{"2   +    4i", NumType<double>(Complex<double>(2, 4))},
    Expression{"(  3+6) * 2", NumType<double>(Real<double>(18))}
));


struct InvalidExpression
{
    std::string expr;
};
class calculate_invalid_expression : public CalculatorTests, public ::testing::TestWithParam<InvalidExpression> {};
TEST_P(calculate_invalid_expression, Default)
{
    InitCalculator();

    calc->setupInputString(GetParam().expr);

    ASSERT_THROW(calc->calculate(), std::runtime_error);
}
INSTANTIATE_TEST_SUITE_P(Default, calculate_invalid_expression, ::testing::Values(
    InvalidExpression{"5 i"},
    InvalidExpression{"(4 + 5"},
    InvalidExpression{"4.2 * "},
    InvalidExpression{" / "}
));