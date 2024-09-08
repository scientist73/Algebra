#pragma once
#include <string>
#include "NumType.h"
#include "TokenType.h"


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
            
                virtual void pushToken(tok::TokenType token) = 0;
                virtual NumType<ScalarType> parse() = 0;
            };
        } // namespace pars
    } // namespace calc
} // namespace alg
