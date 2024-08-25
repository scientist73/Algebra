%{
#include <stdexcept>
#include "Flex_Lexer.h"
#include "TokenRegexGenerator.h"
#include "TokenGenerator.h"


using alg::calc::lex::flex::Flex_Lexer;
using alg::calc::tok::TokenType;
using alg::calc::tok::TokenRegexGenerator;
using alg::calc::tok::TokenGenerator;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::TerminationTokenType;
%}

%option noyywrap
%option batch
%option debug

blank [ \t\r]
new_line \n

%{
#define yyterminate() \
input_t = INPUT::END_OF_INPUT;\
return TokenGenerator::constructTerminationToken(TerminationTokenType());

#define YY_USER_INIT \
if (input_t == Flex_Lexer::INPUT::NONE || input_t == Flex_Lexer::INPUT::END_OF_INPUT)\
    throw std::runtime_error("some error");
%}


%%
{blank}+
{new_line}+


TokenRegexGenerator::getOperatorRegex(OPERATOR::MINUS) return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::MINUS));
TokenRegexGenerator::getOperatorRegex(OPERATOR::PLUS) return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS));
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