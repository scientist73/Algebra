#pragma once
#include <string>


namespace alg
{
    namespace num
    {
        enum class NUM
        {
            REAL,
            COMPLEX,
        };

        template<typename ScalarType>
        class INumType {};
    } // namespace num
} // namespace alg
