%{
#include <stdexcept>
#include <string>
#include "Flex_Lexer.h"
#include "TokenGenerator.h"


using alg::calc::lex::flex::Flex_Lexer;
using alg::calc::tok::TokenType;
using alg::calc::tok::TokenGenerator;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParamTokenType;
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
    return TokenGenerator::constructTerminationToken(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT));\
}
%}

blank       [ \t\r]
new_line    "\n"
MINUS       "-"
PLUS        "+"
MULT        "*"
DIV         "/"
PARAM_ROUND_OPEN "("
PARAM_ROUND_CLOSE ")"
REAL        [0-9]+(\.[0-9]+)?
IMAG        "i"
ID          [_a-zA-Z][_a-zA-Z0-9]*


%%
{blank}+
{new_line} return TokenGenerator::constructTerminationToken(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_LINE));

{MINUS} return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::MINUS));
{PLUS} return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS));
{MULT} return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::MULT));
{DIV} return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::DIV));

{PARAM_ROUND_OPEN} return TokenGenerator::constructParamToken(ParamTokenType(ParamTokenType::PARAM::ROUND_OPEN));
{PARAM_ROUND_CLOSE} return TokenGenerator::constructParamToken(ParamTokenType(ParamTokenType::PARAM::ROUND_CLOSE));


{REAL} return TokenGenerator::constructNumTokenToken(NumTokenType(NumTokenType::NUM::REAL, yytext));
{IMAG} return TokenGenerator::constructNumTokenToken(NumTokenType(NumTokenType::NUM::IMAG, "1"));
{REAL}{IMAG} {
    yytext[strlen(yytext)-1] = '\0';
    return TokenGenerator::constructNumTokenToken(NumTokenType(NumTokenType::NUM::IMAG, yytext));
}

{ID} return TokenGenerator::constructIdentifierToken(IdentifierTokenType(yytext));

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