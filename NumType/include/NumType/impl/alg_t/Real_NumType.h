#pragma once

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
                class Complex_NumType;

                class Real_NumType : public INumType
                {                    
                public:
                    Real_NumType(const std::string& num);
                    Real_NumType(const Real_NumType& num);
                    ~Real_NumType() override = default;

                    std::string getString() const override;
                    alg::ALGEBRA getAlgebraType() const override;
                    INumType* getCopy() const override;

                private:
                    Real_NumType(const ScalarType& num);
                    FRIEND_OPERATORS

                    ScalarType a;
                };
            } // namespace alg_t
        } // namespace impl        
    } // namespace num
} // namespace alg