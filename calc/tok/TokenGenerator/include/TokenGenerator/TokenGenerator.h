#pragma once
#include "TokenType.h"


namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class TokenGenerator
            {
            public:
                static TokenType constructOperatorToken(OperatorTokenType&& op_token);
                static TokenType constructNumTokenToken(NumTokenType&& num_token);
                static TokenType constructIdentifierToken(IdentifierTokenType&& id_token);
                static TokenType constructTerminationToken(TerminationTokenType&& term_token);

            private:
                TokenGenerator() = default;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
