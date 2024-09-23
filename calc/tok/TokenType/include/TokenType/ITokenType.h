#pragma once

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            enum class TOKEN
            {
                OPERATOR,
                PAREN,
                NUM,
                IDENTIFIER,
                TERMINATION,
                EMPTY,
            };

            class ITokenType {};
        } // namespace tok
    } // namespace calc
} // namespace alg
