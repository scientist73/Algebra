#pragma once
#include "AlgebraException.h"
#include <string_view>

namespace alg
{
    namespace except
    {
        class num_has_no_value : public alg_exception 
        {
        public:
            explicit num_has_no_value(std::string_view error_msg) : alg_exception(error_msg) {}
        };
    } // namespace except
} // namespace alg
