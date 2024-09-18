#include "gtest/gtest.h"
#include "Parser.h"
#include <vector>

using alg::calc::pars::Parser;

using alg::calc::tok::NumTokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::TerminationTokenType;
using alg::calc::tok::IdentifierTokenType;


#define PLUS_TOKEN TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS))
#define MINUS_TOKEN TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::MINUS))
#define DIV_TOKEN TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::DIV))
#define MULT_TOKEN TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::MULT))

#define PAREN_ROUND_OPEN_TOKEN TokenType(ParenTokenType(ParenTokenType::PAREN::ROUND_OPEN))
#define PAREN_ROUND_CLOSE_TOKEN TokenType(ParenTokenType(ParenTokenType::PAREN::ROUND_CLOSE))

#define REAL_TOKEN(real_str) TokenType(NumTokenType(NumTokenType::NUM::REAL, real_str))
#define IMAG_TOKEN(imag_str) TokenType(NumTokenType(NumTokenType::NUM::IMAG, imag_str))

#define IDENTIFIER_TOKEN(id_str) TokenType(IdentifierTokenType(id_str))

#define END_OF_INPUT_TOKEN TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT))


void AssertNum(const NumType<double>& l_op, const NumType<double>& r_op)
{
    if (l_op.getNumType() == r_op.getNumType())
    {
        switch (l_op.getNumType())
        {
        case NUM::REAL:
            ASSERT_DOUBLE_EQ(l_op.getReal().real(), r_op.getReal().real());
            break;
        case NUM::COMPLEX:
            ASSERT_DOUBLE_EQ(l_op.getComplex().real(), r_op.getComplex().real());
            ASSERT_DOUBLE_EQ(l_op.getComplex().imag(), r_op.getComplex().imag());
            break;
        }
    }
    else
        FAIL();
}

class ParserTests
{
public:
    void InitParser() { parser.reset(new Parser<double>()); }


protected:
    std::unique_ptr<Parser<double>> parser;
};


struct Expression
{
    std::vector<TokenType> tokens;
    NumType<double> res;
};

class parse_correct_expression : public ParserTests, public ::testing::TestWithParam<Expression> {};
TEST_P(parse_correct_expression, Default)
{
    InitParser();

    for (auto token : GetParam().tokens)
        parser->pushToken(token);
    auto res = parser->parse();

    AssertNum(res, GetParam().res);
}
INSTANTIATE_TEST_SUITE_P(simple_real_num_expression, parse_correct_expression, ::testing::Values(
    Expression{std::vector({REAL_TOKEN("5.1"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(5.1))},
    Expression{std::vector({REAL_TOKEN("3.4"), PLUS_TOKEN, REAL_TOKEN("2.6"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(6))},
    Expression{std::vector({REAL_TOKEN("3.4"), MINUS_TOKEN, REAL_TOKEN("2.4"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(1))},
    Expression{std::vector({REAL_TOKEN("3"), MULT_TOKEN, REAL_TOKEN("2"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(6))},
    Expression{std::vector({REAL_TOKEN("3"), DIV_TOKEN, REAL_TOKEN("2"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(1.5))},
    Expression{std::vector({PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("7.8"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(7.8))}
));
INSTANTIATE_TEST_SUITE_P(simple_complex_num_expression, parse_correct_expression, ::testing::Values(
    Expression{std::vector({IMAG_TOKEN("5.1"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(0, 5.1))},
    Expression{std::vector({IMAG_TOKEN("3.4"), PLUS_TOKEN, IMAG_TOKEN("2.6"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(0, 6))},
    Expression{std::vector({IMAG_TOKEN("3.4"), MINUS_TOKEN, IMAG_TOKEN("2.4"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(0, 1))},
    Expression{std::vector({IMAG_TOKEN("3"), MULT_TOKEN, IMAG_TOKEN("2"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(-6, 0))},
    Expression{std::vector({IMAG_TOKEN("3"), DIV_TOKEN, IMAG_TOKEN("2"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(1.5, 0))},
    Expression{std::vector({PAREN_ROUND_OPEN_TOKEN, IMAG_TOKEN("7.8"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(0, 7.8))}
));
INSTANTIATE_TEST_SUITE_P(complicated_expression, parse_correct_expression, ::testing::Values(
    Expression{std::vector({REAL_TOKEN("2"), PLUS_TOKEN, IMAG_TOKEN("5.6"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(2, 5.6))},
    Expression{std::vector({REAL_TOKEN("5"), PLUS_TOKEN, IMAG_TOKEN("5"), MULT_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Complex<double>(5, 25))},
    Expression{std::vector({REAL_TOKEN("5"), MINUS_TOKEN, REAL_TOKEN("5"), MULT_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(-20))},
    Expression{std::vector({PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), PAREN_ROUND_CLOSE_TOKEN, MULT_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(50))},
    Expression{std::vector({REAL_TOKEN("10"), DIV_TOKEN, REAL_TOKEN("5"), MULT_TOKEN, REAL_TOKEN("3"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(6))},
    Expression{std::vector({REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), MULT_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(30))}
));


struct TwoExpressions
{
    std::vector<TokenType> tokens;
    NumType<double> res1;
    NumType<double> res2;
};
class parse_two_correct_expression : public ParserTests, public ::testing::TestWithParam<TwoExpressions> {};
TEST_P(parse_two_correct_expression, Default)
{
    InitParser();

    for (auto token : GetParam().tokens)
        parser->pushToken(token);
    auto res1 = parser->parse();
    auto res2 = parser->parse();

    AssertNum(res1, GetParam().res1);
    AssertNum(res2, GetParam().res2);
}
INSTANTIATE_TEST_SUITE_P(Default, parse_two_correct_expression, ::testing::Values(
    TwoExpressions{std::vector({REAL_TOKEN("5.1"), END_OF_INPUT_TOKEN, REAL_TOKEN("3"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(5.1)), NumType<double>(Real<double>(3))},
    TwoExpressions{std::vector({REAL_TOKEN("5"), END_OF_INPUT_TOKEN, REAL_TOKEN("3"), PLUS_TOKEN, IMAG_TOKEN("2.1"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(5)), NumType<double>(Complex<double>(3, 2.1))}
));


struct InvalidExpression
{
    std::vector<TokenType> tokens;
};
class parse_invalid_expression : public ParserTests, public ::testing::TestWithParam<InvalidExpression> {};
TEST_P(parse_invalid_expression, Default)
{
    InitParser();

    for (auto token : GetParam().tokens)
        parser->pushToken(token);
    ASSERT_THROW(parser->parse(), std::runtime_error);
}
INSTANTIATE_TEST_SUITE_P(Default, parse_invalid_expression, ::testing::Values(
    InvalidExpression{std::vector({END_OF_INPUT_TOKEN})},
    InvalidExpression{std::vector({PLUS_TOKEN, END_OF_INPUT_TOKEN})},
    InvalidExpression{std::vector({PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("5.6"), END_OF_INPUT_TOKEN})}
));
