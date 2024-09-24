#pragma once
#include "AlgebraException.h"
#include "ITokenType.h"

namespace alg
{
    namespace calc
    {
        namespace tok
        {
            namespace except
            {
                
                class token_value_has_different_type : public alg::except::alg_exception
                {
                public:
                    explicit token_value_has_different_type(TOKEN token_t) noexcept : alg_exception() {}

                    TOKEN getTokenType() const noexcept { return token_t; }
                private:
                    TOKEN token_t;
                };
            } // namespace except
        } // namespace tok
    } // namespace calc
} // namespace alg
