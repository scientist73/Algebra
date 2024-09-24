#pragma once
#include "ITokenType.h"

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class ParenTokenType : public ITokenType
            {
            public:
                enum class PAREN
                {
                    ROUND_OPEN,
                    ROUND_CLOSE,
                };

                constexpr explicit ParenTokenType(PAREN paren_t) noexcept;

                constexpr PAREN getParenTokenType() const noexcept;
            
            private:
                PAREN paren_t;
            };

            constexpr bool operator==(const ParenTokenType& l_op, const ParenTokenType& r_op);
        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr ParenTokenType::ParenTokenType(PAREN paren_t) noexcept :
    paren_t(paren_t)
{}

constexpr ParenTokenType::PAREN ParenTokenType::getParenTokenType() const noexcept
{
    return paren_t;
}


// non-member func
constexpr bool alg::calc::tok::operator==(const ParenTokenType& l_op, const ParenTokenType& r_op)
{
    return l_op.getParenTokenType() == r_op.getParenTokenType();
}