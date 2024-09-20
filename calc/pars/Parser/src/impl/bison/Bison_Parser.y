%require "3.4"
%language "c++"
%defines

%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
#include <string_view>
#include <queue>
#include "NumType.h"
#include "TokenType.h"


using alg::num::NumType;
using alg::calc::tok::get;
using alg::calc::tok::TOKEN;
using alg::calc::tok::TokenType;
using alg::calc::tok::OperatorTokenType;
using alg::calc::tok::ParenTokenType;
using alg::calc::tok::NumTokenType;
using alg::calc::tok::IdentifierTokenType;
using alg::calc::tok::TerminationTokenType;
}



%define parse.trace
%define api.namespace {alg::calc::pars::impl::bison}

%code provides{
namespace alg
{
    namespace calc
    {
        namespace pars
        {
            namespace impl
            {
                namespace bison
                {
                    // private func
                    // this func should be declared in .cpp file
                    // but bison doesn't provide this functionality
                    parser::symbol_type yylex ();
                    void setParseResult(const NumType<double>& parse_result);

                    // public func
                    void pushToken(alg::calc::tok::TokenType token);
                    NumType<double> getParseResult();

                } // namespace bison
            } // namespace impl
        } // namespace pars
    } // namespace calc
} // namespace alg
}



%token
  END_OF_INPUT 0
  END_OF_LINE "\n"
  MINUS "-"
  PLUS "+"
  MULT "*"
  DIV "/"
  PAREN_ROUND_OPEN "("
  PAREN_ROUND_CLOSE ")"
;
%token <std::string_view> ID "identifier"
%token <NumType<double>> NUM "number"
%type <NumType<double>> exp


%%
%left "+" "-";
%left "*" "/";


input: exp { setParseResult($1); }
  ;

exp: NUM
  | exp "+" exp { $$ = $1 + $3; }
  | exp "-" exp { $$ = $1 - $3; }
  | exp "*" exp { $$ = $1 * $3; }
  | exp "/" exp { $$ = $1 / $3; }
  | "(" exp ")" { $$ = $2; }
  ;
%%

using alg::calc::pars::impl::bison::parser;

NumType<double> parse_result;
std::queue<parser::symbol_type> parser_tokens;


void alg::calc::pars::impl::bison::setParseResult(const NumType<double>& parse_result)
{
    ::parse_result = parse_result;
}
parser::symbol_type alg::calc::pars::impl::bison::yylex ()
{
    auto token = parser_tokens.front();
    parser_tokens.pop();
    return token;
}
void alg::calc::pars::impl::bison::pushToken(TokenType token)
{
    switch (token.getTokenType())
    {
    case TOKEN::TERMINATION:
    {
        auto term_token = get<TerminationTokenType>(token);
        switch (term_token.getTerminationTokenType())
        {
        case TerminationTokenType::TERMINATION::END_OF_INPUT:
            parser_tokens.push(parser::make_END_OF_INPUT());
            break;
        case TerminationTokenType::TERMINATION::END_OF_LINE:
            parser_tokens.push(parser::make_END_OF_LINE());
            break;
        }
        break;
    }
    case TOKEN::IDENTIFIER:
    {
        auto id_token = get<IdentifierTokenType>(token);
        parser_tokens.push(parser::make_ID(id_token.getIdentifier()));
        break;
    }
    case TOKEN::NUM:
    {
        auto num_token = get<NumTokenType>(token);
        // modify code here
        switch (num_token.getNumTokenType())
        {
        case NumTokenType::NUM::REAL:
            parser_tokens.push(parser::make_NUM(NumType<double>(Real<double>(std::stod(std::string(num_token.getScalar()))))));
            break;
        case NumTokenType::NUM::IMAG:
            parser_tokens.push(parser::make_NUM(NumType<double>(Complex<double>(0, std::stod(std::string(num_token.getScalar()))))));
            break;
        }
        break;
    }
    case TOKEN::OPERATOR:
    {
        auto op_token = get<OperatorTokenType>(token);
        switch (op_token.getOperatorTokenType())
        {
        case OperatorTokenType::OPERATOR::PLUS:
            parser_tokens.push(parser::make_PLUS());
            break;
        case OperatorTokenType::OPERATOR::MINUS:
            parser_tokens.push(parser::make_MINUS());
            break;
        case OperatorTokenType::OPERATOR::MULT:
            parser_tokens.push(parser::make_MULT());
            break;
        case OperatorTokenType::OPERATOR::DIV:
            parser_tokens.push(parser::make_DIV());
            break;
        }
        break;
    }
    case TOKEN::PAREN:
    {
        auto paren_token = get<ParenTokenType>(token);
        switch (paren_token.getParenTokenType())
        {
        case ParenTokenType::PAREN::ROUND_CLOSE:
            parser_tokens.push(parser::make_PAREN_ROUND_CLOSE());
            break;
        case ParenTokenType::PAREN::ROUND_OPEN:
            parser_tokens.push(parser::make_PAREN_ROUND_OPEN());
            break;
        }
        break;
    }
    case TOKEN::EMPTY:
        throw std::runtime_error("parser received empty token");
    }
}
NumType<double> alg::calc::pars::impl::bison::getParseResult()
{
    return parse_result;
}


void parser::error(const std::string& err_mes) 
{
    throw std::runtime_error(err_mes);
}
