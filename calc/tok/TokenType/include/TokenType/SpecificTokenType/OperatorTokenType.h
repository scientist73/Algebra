#pragma once
#include "ITokenType.h"

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class OperatorTokenType : public ITokenType
            {
            public:
                enum class OPERATOR
                {
                    PLUS,
                    MINUS,
                    MULT,
                    DIV,
                };

                constexpr explicit OperatorTokenType(OPERATOR operator_t) noexcept;

                constexpr OPERATOR getOperatorTokenType() const noexcept;
                
            private:
                OPERATOR operator_t;
            };

            constexpr bool operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op);
        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr OperatorTokenType::OperatorTokenType(OPERATOR operator_t) noexcept :
    operator_t(operator_t)
{}

constexpr OperatorTokenType::OPERATOR OperatorTokenType::getOperatorTokenType() const noexcept
{
    return operator_t;
}


// non-member func
constexpr bool alg::calc::tok::operator==(const OperatorTokenType& l_op, const OperatorTokenType& r_op)
{
    return l_op.getOperatorTokenType() == r_op.getOperatorTokenType();
}