#pragma once
#include "ALGEBRA.h"
#include "NumType.h"
#include "NumTypeOperators.h"
#include "Real.h"
#include <type_traits>


namespace alg
{        
    namespace num
    {
        template<typename ScalarType>
        class INumType;

        namespace impl
        {
            template<typename ScalarType>
            class Complex_NumType;

            template<typename ScalarType>
            class Real_NumType : public INumType<ScalarType>
            {                    
            public:
                Real_NumType(const Real<ScalarType>& value);
                Real_NumType(Real<ScalarType>&& value);

                Real_NumType(const Real_NumType& num) = default;
                Real_NumType(Real_NumType&& num) = default;
                ~Real_NumType() override = default;

                std::string getString() const override;
                ALGEBRA getAlgebraType() const override;
                INumType<ScalarType>* getCopy() const override;

                const Real<ScalarType>& getReal() const;

                Real_NumType<ScalarType>& operator=(const Real_NumType<ScalarType>& num) = delete;
                Real_NumType<ScalarType>& operator=(Real_NumType<ScalarType>&& num) = delete;

                Real_NumType<ScalarType>& operator+=(const Real_NumType<ScalarType>& right_op);
                Real_NumType<ScalarType>& operator-=(const Real_NumType<ScalarType>& right_op);
                Real_NumType<ScalarType>& operator*=(const Real_NumType<ScalarType>& right_op);
                Real_NumType<ScalarType>& operator/=(const Real_NumType<ScalarType>& right_op);
            private:

                Real<ScalarType> value;
            };

        } // namespace impl        
    } // namespace num
} // namespace alg





//#include "Real_NumType.cpp"

using namespace alg::num::impl;

template<typename ScalarType>
Real_NumType<ScalarType>::Real_NumType(const Real<ScalarType>& value) :
    value(value)
{}
template<typename ScalarType>
Real_NumType<ScalarType>::Real_NumType(Real<ScalarType>&& value) :
    value(value)
{}

template<typename ScalarType>
std::string Real_NumType<ScalarType>::getString() const
{
    if constexpr (std::is_same_v<ScalarType, long double>)
        return std::to_string(value.real());
    else
        return value.real().getString();
}
template<typename ScalarType>
ALGEBRA Real_NumType<ScalarType>::getAlgebraType() const
{
    return ALGEBRA::REAL;
}
template<typename ScalarType>
INumType<ScalarType>* Real_NumType<ScalarType>::getCopy() const
{
    return new Real_NumType(this->value);
}

template<typename ScalarType>
const Real<ScalarType>& Real_NumType<ScalarType>::getReal() const
{
    return value;
}

template<typename ScalarType>
Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator+=(const Real_NumType<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator-=(const Real_NumType<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator*=(const Real_NumType<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator/=(const Real_NumType<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}