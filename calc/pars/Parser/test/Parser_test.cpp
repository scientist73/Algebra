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



class ParserTests
{
public:
    void InitParser() { parser.reset(new Parser<double>()); }
    void AssertNum(const NumType<double>& l_op, const NumType<double>& r_op)
    {
        if (l_op.getAlgebraType() == r_op.getAlgebraType())
        {
            switch (l_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                ASSERT_DOUBLE_EQ(l_op.getReal().real(), r_op.getReal().real());
                break;
            case ALGEBRA::COMPLEX:
                ASSERT_DOUBLE_EQ(l_op.getComplex().real(), r_op.getComplex().real());
                ASSERT_DOUBLE_EQ(l_op.getComplex().imag(), r_op.getComplex().imag());
                break;
            }
        }
        else
            FAIL();
    }

protected:
    std::unique_ptr<Parser<double>> parser;
};


struct Expression
{
    std::vector<TokenType> tokens;
    NumType<double> res;
};

class parse_expression : public ParserTests, public ::testing::TestWithParam<Expression> {};
TEST_P(parse_expression,Default)
{
    InitParser();

    for (auto token : GetParam().tokens)
        parser->pushToken(token);
    auto res = parser->parse();

    AssertNum(res, GetParam().res);
}
INSTANTIATE_TEST_SUITE_P(Default, parse_expression, ::testing::Values(
    Expression{std::vector({REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(5))},
    Expression{std::vector({PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("5"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(5))},
    Expression{std::vector({REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(10))},
    Expression{std::vector({PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(10))},
    Expression{std::vector({REAL_TOKEN("5"), PLUS_TOKEN, REAL_TOKEN("5"), MULT_TOKEN, REAL_TOKEN("5"), END_OF_INPUT_TOKEN}), NumType<double>(Real<double>(30))}
));