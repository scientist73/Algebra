#include <gtest/gtest.h>
#include "Lexer.h"
#include "TokenType.h"
#include <memory>
#include <vector>
#include <string_view>


using alg::calc::lex::Lexer;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::TerminationTokenType;
using alg::calc::tok::IdentifierTokenType;
using alg::calc::tok::get_token;


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


std::ostream& operator<<(std::ostream& out, const TokenType& token)
{
    if (token.getTokenType() == TOKEN::IDENTIFIER)
    {
        std::cout << get_token<IdentifierTokenType>(token).getIdentifier();
    }
    
    return out;
}




class LexerTests
{
public:
    void InitLexer() { lexer.reset(new Lexer()); }
protected:
    std::unique_ptr<Lexer> lexer;
};


struct SingleToken
{
    std::string token_str;
    TokenType token;
};

class scan_single_token : public LexerTests, public ::testing::TestWithParam<SingleToken> {};
TEST_P(scan_single_token, Default)
{
    InitLexer();

    lexer->setupInputString(GetParam().token_str);
    auto token{lexer->getNextToken()};
    std::cerr << token << std::endl;
    auto x{GetParam().token};
    ASSERT_EQ(token, GetParam().token);
    
    lexer->closeInput();
}
INSTANTIATE_TEST_SUITE_P(Operators, scan_single_token, ::testing::Values(
    SingleToken{"+", TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS))},
    SingleToken{"-", TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::MINUS))},
    SingleToken{"*", TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::MULT))},
    SingleToken{"/", TokenType(OperatorTokenType(OperatorTokenType::OPERATOR::DIV))}
));
INSTANTIATE_TEST_SUITE_P(Params, scan_single_token, ::testing::Values(
    SingleToken{"(", TokenType(ParenTokenType(ParenTokenType::PAREN::ROUND_OPEN))},
    SingleToken{")", TokenType(ParenTokenType(ParenTokenType::PAREN::ROUND_CLOSE))}
));
INSTANTIATE_TEST_SUITE_P(Nums, scan_single_token, ::testing::Values(
    SingleToken{"5", REAL_TOKEN("5")},
    SingleToken{"5.78", REAL_TOKEN("5.78")},
    SingleToken{"7i", TokenType(NumTokenType(NumTokenType::NUM::IMAG, "7"))},
    SingleToken{"45.6i", TokenType(NumTokenType(NumTokenType::NUM::IMAG, "45.6"))}
));
INSTANTIATE_TEST_SUITE_P(Identifiers, scan_single_token, ::testing::Values(
    SingleToken{"_", TokenType(IdentifierTokenType("_"))},
    SingleToken{"h", TokenType(IdentifierTokenType("h"))},
    SingleToken{"_hello", TokenType(IdentifierTokenType("_hello"))},
    SingleToken{"flex", TokenType(IdentifierTokenType("flex"))},
    SingleToken{"_8ad7", TokenType(IdentifierTokenType("_8ad7"))}
));
INSTANTIATE_TEST_SUITE_P(Termination, scan_single_token, ::testing::Values(
    SingleToken{"\n", TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_LINE))},
    SingleToken{"", TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT))}
));


class scanning_without_input_is_invalid : public LexerTests, public ::testing::Test {};
TEST_F(scanning_without_input_is_invalid, Default)
{
    InitLexer();

    ASSERT_THROW(lexer->getNextToken(), std::runtime_error);
}

struct MultipleTokens
{
    std::string tokens_str;
    std::vector<TokenType> tokens;
};

class scan_multiple_tokens : public LexerTests, public ::testing::TestWithParam<MultipleTokens> {};
TEST_P(scan_multiple_tokens, Default)
{
    InitLexer();

    lexer->setupInputString(GetParam().tokens_str);
    for (auto token : GetParam().tokens)
        ASSERT_EQ(lexer->getNextToken(), token);
    lexer->closeInput();
}
INSTANTIATE_TEST_SUITE_P(Default, scan_multiple_tokens, ::testing::Values(
    MultipleTokens{"3.4 + 4.5", { REAL_TOKEN("3.4"), PLUS_TOKEN, REAL_TOKEN("4.5"), END_OF_INPUT_TOKEN }},
    MultipleTokens{"sin(180)", {IDENTIFIER_TOKEN("sin"), PAREN_ROUND_OPEN_TOKEN, REAL_TOKEN("180"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}},
    MultipleTokens{"Pi*R", {IDENTIFIER_TOKEN("Pi"), MULT_TOKEN, IDENTIFIER_TOKEN("R"), END_OF_INPUT_TOKEN}},
    MultipleTokens{"4.5i * tan(x)", {IMAG_TOKEN("4.5"), MULT_TOKEN, IDENTIFIER_TOKEN("tan"), PAREN_ROUND_OPEN_TOKEN, IDENTIFIER_TOKEN("x"), PAREN_ROUND_CLOSE_TOKEN, END_OF_INPUT_TOKEN}},
    MultipleTokens{"5.6 - i", {REAL_TOKEN("5.6"), MINUS_TOKEN, IMAG_TOKEN("1"), END_OF_INPUT_TOKEN}},
    MultipleTokens{"2Pi", {REAL_TOKEN("2"), IDENTIFIER_TOKEN("Pi"), END_OF_INPUT_TOKEN}}
));
INSTANTIATE_TEST_SUITE_P(spaces_between_tokens_is_not_important, scan_multiple_tokens, ::testing::Values(
    MultipleTokens{"  * 4.5   (  /", { MULT_TOKEN, REAL_TOKEN("4.5"), PAREN_ROUND_OPEN_TOKEN, DIV_TOKEN, END_OF_INPUT_TOKEN }}
));


class scan_invalid_tokens : public LexerTests, public ::testing::TestWithParam<std::string> {};
TEST_P(scan_invalid_tokens, Default)
{
    InitLexer();

    lexer->setupInputString(GetParam());
    ASSERT_THROW(lexer->getNextToken(), std::runtime_error);
    lexer->closeInput();
}
INSTANTIATE_TEST_SUITE_P(single_invalid_token, scan_invalid_tokens, ::testing::Values(
    "%",
    "$",
    "#"
));