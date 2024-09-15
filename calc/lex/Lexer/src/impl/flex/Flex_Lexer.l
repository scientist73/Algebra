%{
#include <stdexcept>
#include <string>
#include "Flex_Lexer.h"
#include "TokenType.h"


using alg::calc::lex::impl::flex::Flex_Lexer;

using alg::calc::tok::makeIdentifierToken;
using alg::calc::tok::makeNumToken;
using NUM = alg::calc::tok::NumTokenType::NUM;
using alg::calc::tok::makeOperatorToken;
using OPERATOR = alg::calc::tok::OperatorTokenType::OPERATOR;
using alg::calc::tok::makeParenToken;
using PAREN = alg::calc::tok::ParenTokenType::PAREN;
using alg::calc::tok::makeTerminationToken;
using TERMINATION = alg::calc::tok::TerminationTokenType::TERMINATION;

using alg::calc::tok::TokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::IdentifierTokenType;
using alg::calc::tok::TerminationTokenType;
%}

%option noyywrap
%option batch
%option debug


%{
#define yyterminate() \
if (getInputType() == INPUT::END_OF_INPUT)\
    throw std::runtime_error("some error");\
else\
{\
    input_t = INPUT::END_OF_INPUT;\
    return makeTerminationToken(TERMINATION::END_OF_INPUT);\
}
%}

blank       [ \t\r]
new_line    "\n"
MINUS       "-"
PLUS        "+"
MULT        "*"
DIV         "/"
PAREN_ROUND_OPEN "("
PAREN_ROUND_CLOSE ")"
REAL        [0-9]+(\.[0-9]+)?
IMAG        "i"
ID          [_a-zA-Z][_a-zA-Z0-9]*


%%
{blank}+
{new_line} return makeTerminationToken(TERMINATION::END_OF_LINE);

{MINUS} return makeOperatorToken(OPERATOR::MINUS);
{PLUS} return makeOperatorToken(OPERATOR::PLUS);
{MULT} return makeOperatorToken(OPERATOR::MULT);
{DIV} return makeOperatorToken(OPERATOR::DIV);

{PAREN_ROUND_OPEN} return makeParenToken(PAREN::ROUND_OPEN);
{PAREN_ROUND_CLOSE} return makeParenToken(PAREN::ROUND_CLOSE);


{REAL} return makeNumToken(NUM::REAL, yytext);
{IMAG} return makeNumToken(NUM::IMAG, "1");
{REAL}{IMAG} {
    yytext[strlen(yytext)-1] = '\0';
    return makeNumToken(NUM::IMAG, yytext);
}

{ID} return makeIdentifierToken(yytext);

. { throw std::runtime_error("some error"); }
<<EOF>> yyterminate()
%%


static YY_BUFFER_STATE yy_input_buf;

Flex_Lexer::Flex_Lexer() :
	input_t(INPUT::NONE)
{
    yy_input_buf = nullptr;
}

void Flex_Lexer::setupInputString(const std::string& str_input)
{
    closeInput();
	input_t = INPUT::STRING;
	yy_input_buf = yy_scan_string(str_input.c_str());
}
void Flex_Lexer::closeInput()
{
    if (yy_input_buf != nullptr)
    {
        input_t = INPUT::NONE;
        yy_delete_buffer(yy_input_buf);
        yy_input_buf = nullptr;
    }
}

Flex_Lexer::INPUT Flex_Lexer::getInputType() const
{
	return input_t;
}

TokenType Flex_Lexer::getNextToken()
{
    if (getInputType() == INPUT::NONE)
        throw std::runtime_error("some error");

    return yylex();
}