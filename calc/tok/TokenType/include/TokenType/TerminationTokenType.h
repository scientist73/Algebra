#pragma once
#include "ITokenType.h"


namespace alg
{
    namespace calc
    {
        namespace tok
        {
            class TerminationTokenType : public ITokenType
            {
            public:
                enum class TERMINATION
                {
                    END_OF_INPUT,
                    END_OF_LINE
                };

                constexpr explicit TerminationTokenType(TERMINATION term_t);

                constexpr TERMINATION getTerminationTokenType() const;
            private:
                TERMINATION term_t;
            };

            constexpr bool operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op);
        } // namespace tok
    } // namespace calc
} // namespace alg


using namespace alg::calc::tok;

constexpr TerminationTokenType::TerminationTokenType(TERMINATION term_t) :
    term_t(term_t)
{}

constexpr TerminationTokenType::TERMINATION TerminationTokenType::getTerminationTokenType() const
{
    return term_t;
}


// non-member func
constexpr bool alg::calc::tok::operator==(const TerminationTokenType& l_op, const TerminationTokenType& r_op)
{
    return l_op.getTerminationTokenType() == r_op.getTerminationTokenType();
}