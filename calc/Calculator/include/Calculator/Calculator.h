#pragma once
#include "Lexer.h"
#include "Parser.h"
#include "NumType.h"



namespace alg
{
    namespace calc
    {
        template<typename ScalarType>
        class Calculator
        {
        public:
            Calculator();

            void setupInputString(const std::string& str_input);
            void closeInput();

            NumType<ScalarType> calculate();

        private:
            lex::Lexer lexer;
            pars::Parser<ScalarType> parser;
        };
        
    } // namespace calc
} // namespace alg


#include "TokenType.h"

using namespace alg::calc;

template<typename ScalarType>
Calculator<ScalarType>::Calculator() :
    parser(), lexer()
{}

template<typename ScalarType>
void Calculator<ScalarType>::setupInputString(const std::string& str_input)
{
    return lexer.setupInputString(str_input);
}
template<typename ScalarType>
void Calculator<ScalarType>::closeInput()
{
    return lexer.closeInput();
}

template<typename ScalarType>
NumType<ScalarType> Calculator<ScalarType>::calculate()
{
    TokenType token;
    
    do
    {
        token = lexer.getNextToken();
        parser.pushToken(token);

    } while (token != TokenType(TerminationTokenType(TerminationTokenType::TERMINATION::END_OF_INPUT)));
    
    return parser.parse();
}