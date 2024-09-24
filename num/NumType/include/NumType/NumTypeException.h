#pragma once
#include "AlgebraException.h"
#include "INumType.h"
#include <string_view>

namespace alg
{
    namespace num
    {
        namespace except
        {
            class num_has_no_value : public alg::except::alg_exception {};

            class num_value_has_different_type : public alg::except::alg_exception
            {
            public:
                explicit num_value_has_different_type(NUM num_t) noexcept : alg_exception() {}

                NUM getNumType() const noexcept { return num_t; }
            private:
                NUM num_t;
            };
        } // namespace except
    }
} // namespace alg
