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

            class ITokenType
            {
            public:
                virtual ~ITokenType() = default;
                virtual constexpr TOKEN getTokenType() const = 0;
            };
        } // namespace tok
    } // namespace calc
} // namespace alg
