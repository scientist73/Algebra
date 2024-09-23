#pragma once
#include "ITokenType.h"
#include <string_view>

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class NumTokenType : public ITokenType
            {
            public:
                enum class NUM
                {
                    REAL,
                    IMAG,
                };

                constexpr explicit NumTokenType(NUM num_t, std::string_view scalar);

                constexpr NUM getNumTokenType() const;
                constexpr std::string_view getScalar() const;

            private:
                NUM num_t;
                std::string_view scalar;
            };

            constexpr bool operator==(const NumTokenType& l_op, const NumTokenType& r_op);
        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr NumTokenType::NumTokenType(NUM num_t, std::string_view scalar) :
    num_t(num_t), scalar(scalar)
{}

constexpr NumTokenType::NUM NumTokenType::getNumTokenType() const
{
    return num_t;
}
constexpr std::string_view NumTokenType::getScalar() const
{
    return scalar;
}


// non-member func
constexpr bool alg::calc::tok::operator==(const NumTokenType& l_op, const NumTokenType& r_op)
{
    return l_op.getNumTokenType() == r_op.getNumTokenType() && l_op.getScalar() == r_op.getScalar();
}