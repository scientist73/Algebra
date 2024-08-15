#pragma once

#include <initializer_list>
#include <complex>
#include "alg.h"
#include "alg_t.h"
#include "NumType.h"
#include "NumTypeOperators.h"

namespace alg
{        
    namespace num
    {
        namespace impl
        {
            namespace alg_t
            {
                class Complex_NumType : public INumType
                {                    
                public:
                    Complex_NumType(std::initializer_list<std::string> complex_num);
                    Complex_NumType(const Complex_NumType& complex_num);
                    ~Complex_NumType() override = default;

                    std::string getString() const override;
                    alg::ALGEBRA getAlgebraType() const override;
                    INumType* getCopy() const override;

                private:
                    Complex_NumType(std::complex<ScalarType> complex_num);
                    FRIEND_OPERATORS

                    std::complex<ScalarType> value;
                };
            } // namespace alg_t
        } // namespace impl        
    } // namespace num
} // namespace alg