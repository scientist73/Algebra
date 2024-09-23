%{
#include <stdexcept>
#include <string_view>
#include "Flex_Lexer.h"
#include "TokenType.h"


using alg::calc::lex::impl::flex::Flex_Lexer;

using alg::calc::tok::make_token;

using alg::calc::tok::TokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::IdentifierTokenType;
using alg::calc::tok::TerminationTokenType;

using NUM = alg::calc::tok::NumTokenType::NUM;
using OPERATOR = alg::calc::tok::OperatorTokenType::OPERATOR;
using PAREN = alg::calc::tok::ParenTokenType::PAREN;
using TERMINATION = alg::calc::tok::TerminationTokenType::TERMINATION;
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
    return make_token<TerminationTokenType>(TERMINATION::END_OF_INPUT);\
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
{new_line} return make_token<TerminationTokenType>(TERMINATION::END_OF_LINE);

{MINUS} return make_token<OperatorTokenType>(OPERATOR::MINUS);
{PLUS} return make_token<OperatorTokenType>(OPERATOR::PLUS);
{MULT} return make_token<OperatorTokenType>(OPERATOR::MULT);
{DIV} return make_token<OperatorTokenType>(OPERATOR::DIV);

{PAREN_ROUND_OPEN} return make_token<ParenTokenType>(PAREN::ROUND_OPEN);
{PAREN_ROUND_CLOSE} return make_token<ParenTokenType>(PAREN::ROUND_CLOSE);


{REAL} return make_token<NumTokenType>(NUM::REAL, yytext);
{IMAG} return make_token<NumTokenType>(NUM::IMAG, "1");
{REAL}{IMAG} {
    yytext[strlen(yytext)-1] = '\0';
    return make_token<NumTokenType>(NUM::IMAG, yytext);
}

{ID} return make_token<IdentifierTokenType>(yytext);

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