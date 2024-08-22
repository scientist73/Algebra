#pragma once
#include "TokenType.h"

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class TokenRegexGenerator
            {
            public:
                static std::string getOperatorRegex(OperatorTokenType::OPERATOR op_t);
                static std::string getNumTokenRegex(NumTokenType::NUM num_t);
                static std::string getIdentifierRegex(IdentifierTokenType::IDENTIFIER id_t = IdentifierTokenType::IDENTIFIER::UNKNOWN);

            private:
                TokenRegexGenerator() = default;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
