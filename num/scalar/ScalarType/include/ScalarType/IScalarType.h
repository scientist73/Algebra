#pragma once
#include <string>


namespace alg
{
    namespace num
    {
        namespace scalar
        {
            class IScalarType
            {
            public:
                virtual std::string getString() const = 0;
            };
        } // namespace scalar
    } // namespace num
} // namespace alg


