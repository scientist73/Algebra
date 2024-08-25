#pragma once
#include "TokenType.h"




using alg::calc::tok::TokenType;



namespace alg
{
    namespace calc
    {
        namespace lex
        {
            class ILexer
            {
            public:
                enum class INPUT
                {
                    STRING,
                    FILE,
                    CIN,
                    NONE,
                    END_OF_INPUT,
                };

                virtual ~ILexer() = default;

                virtual void setupInputString(const std::string& str_input) = 0;
                virtual void closeInput() = 0;

                virtual INPUT getInputType() const = 0;
                virtual TokenType getNextToken() = 0;
            };
        } // namespace lex
    } // namespace calc
} // namespace alg
