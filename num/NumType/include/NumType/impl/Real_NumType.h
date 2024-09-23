#pragma once
#include <type_traits>
#include "INumType.h"
#include "Real.h"



namespace alg
{        
    namespace num
    {
        namespace impl
        {
            template<typename ScalarType>
            class Real_NumType : public INumType<ScalarType>
            {                    
            public:
                constexpr Real_NumType(const Real<ScalarType>& value);
                constexpr Real_NumType(Real<ScalarType>&& value);

                constexpr const Real<ScalarType>& getReal() const;

                constexpr Real_NumType<ScalarType>& operator+=(const Real_NumType<ScalarType>& right_op);
                constexpr Real_NumType<ScalarType>& operator-=(const Real_NumType<ScalarType>& right_op);
                constexpr Real_NumType<ScalarType>& operator*=(const Real_NumType<ScalarType>& right_op);
                constexpr Real_NumType<ScalarType>& operator/=(const Real_NumType<ScalarType>& right_op);
            private:

                Real<ScalarType> value;
            };

        } // namespace impl        
    } // namespace num
} // namespace alg



using namespace alg::num::impl;

template<typename ScalarType>
constexpr Real_NumType<ScalarType>::Real_NumType(const Real<ScalarType>& value) :
    value(value)
{}
template<typename ScalarType>
constexpr Real_NumType<ScalarType>::Real_NumType(Real<ScalarType>&& value) :
    value(value)
{}

template<typename ScalarType>
constexpr const Real<ScalarType>& Real_NumType<ScalarType>::getReal() const
{
    return value;
}

template<typename ScalarType>
constexpr Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator+=(const Real_NumType<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator-=(const Real_NumType<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator*=(const Real_NumType<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real_NumType<ScalarType>& Real_NumType<ScalarType>::operator/=(const Real_NumType<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}