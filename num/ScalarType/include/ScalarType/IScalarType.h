#pragma once
#include <string>


namespace alg
{
    namespace num
    {
        //#define ScalarType long double
        class IScalarType
        {
        public:
            virtual std::string getString() const = 0;
        };
    } // namespace num
} // namespace alg


