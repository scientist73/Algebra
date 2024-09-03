#include <gtest/gtest.h>
#include "Lexer.h"
#include "TokenType.h"

using alg::calc::lex::Lexer;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::TerminationTokenType;




TEST(Default, ds)
{
    Lexer lexer;
    lexer.setupInputString("4+3");
    
    ASSERT_EQ(alg::calc::lex::ILexer::INPUT::STRING, lexer.getInputType());

    auto token = lexer.getNextToken();

    ASSERT_EQ(token.getNumToken().getNumTokenType(), NumTokenType::NUM::REAL);
    ASSERT_EQ(token.getNumToken().getScalar(), "4");

    token = lexer.getNextToken();

    ASSERT_EQ(token.getOperatorToken().getOperatorTokenType(), OperatorTokenType::OPERATOR::PLUS);

    token = lexer.getNextToken();

    ASSERT_EQ(token.getNumToken().getNumTokenType(), NumTokenType::NUM::REAL);
    ASSERT_EQ(token.getNumToken().getScalar(), "3");

    token = lexer.getNextToken();

    ASSERT_EQ(token.getTerminationToken().getTerminationTokenType(), TerminationTokenType::TERMINATION::END_OF_INPUT);

    ASSERT_EQ(alg::calc::lex::ILexer::INPUT::END_OF_INPUT, lexer.getInputType());


    ASSERT_THROW(lexer.getNextToken(), std::runtime_error);

    lexer.closeInput();
}

TEST(Default, scanning_without_input_is_invalid)
{
    Lexer lexer;

    ASSERT_EQ(alg::calc::lex::ILexer::INPUT::NONE, lexer.getInputType());
    ASSERT_THROW(lexer.getNextToken(), std::runtime_error);
    ASSERT_THROW(lexer.getNextToken(), std::runtime_error);
}