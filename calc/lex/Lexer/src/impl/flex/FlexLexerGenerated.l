%{
#include <stdexcept>
#include "FlexLexerGenerated.h"
#include "TokenRegexGenerator.h"
#include "TokenGenerator.h"



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


%%

{blank}+
{new_line}+


TokenRegexGenerator::getOperatorRegex(OPERATOR::MINUS) return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::MINUS));
TokenRegexGenerator::getOperatorRegex(OPERATOR::PLUS) return TokenGenerator::constructOperatorToken(OperatorTokenType(OperatorTokenType::OPERATOR::PLUS));
. { throw std::runtime_error("some error"); }
<<EOF>> return TokenGenerator::constructTerminationToken(TerminationTokenType());

%%