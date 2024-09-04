#pragma once
#include "TokenType.h"
#include <string>

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
                static TokenType constructParam(ParamTokenType::PARAM param_t);
                static TokenType constructNumToken(NumTokenType::NUM num_t, const std::string& scalar);
                static TokenType constructIdentifier(const std::string& id);
                static TokenType constructTermination(TerminationTokenType::TERMINATION term_t);

            private:
                TokenGenerator() = default;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
