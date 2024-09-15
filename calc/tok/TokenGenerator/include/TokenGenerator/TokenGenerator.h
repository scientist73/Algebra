#pragma once
#include "TokenType.h"
#include <string_view>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class TokenGenerator
            {
            public:
                static TokenType constructOperator(OperatorTokenType::OPERATOR op_t);
                static TokenType constructParen(ParenTokenType::PAREN paren_t);
                static TokenType constructNumToken(NumTokenType::NUM num_t, std::string_view scalar);
                static TokenType constructIdentifier(std::string_view id);
                static TokenType constructTermination(TerminationTokenType::TERMINATION term_t);

            private:
                TokenGenerator() = default;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
