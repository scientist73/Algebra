#pragma once
#include "IParser.h"


namespace alg
{
    namespace calc
    {
        namespace pars
        {
            namespace bison
            {
                template<typename ScalarType>
                class Bison_Parser : public IParser<ScalarType>
                {
                public:
                    Bison_Parser();
                    ~Bison_Parser();
                
                    NumType<ScalarType> parseString(const std::string& str_input) override;
                };
            } // namespace bison
        } // namespace pars
    } // namespace calc
} // namespace alg
