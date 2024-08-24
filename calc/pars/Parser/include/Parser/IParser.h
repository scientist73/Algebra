#pragma once
#include <string>
#include "NumType.h"


namespace alg
{
    namespace calc
    {
        namespace pars
        {
            template<typename ScalarType>
            class IParser
            {
            public:
                virtual ~IParser() = default;
            
                virtual NumType<ScalarType> parseString(const std::string& str_input) = 0;
            };
        } // namespace pars
    } // namespace calc
} // namespace alg
