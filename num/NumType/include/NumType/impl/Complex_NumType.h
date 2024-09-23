#pragma once
#include <type_traits>
#include "INumType.h"
#include "Complex.h"
#include "Real_NumType.h"

namespace alg
{        
    namespace num
    {
        namespace impl
        {
            template<typename ScalarType>
            class Complex_NumType : public INumType<ScalarType>
            {                    
            public:
                constexpr Complex_NumType(const Complex<ScalarType>& value);
                constexpr Complex_NumType(Complex<ScalarType>&& value);
                constexpr Complex_NumType(const Real_NumType<ScalarType>& num);
                constexpr Complex_NumType(Real_NumType<ScalarType>&& num);

                constexpr const Complex<ScalarType>& getComplex() const;

                constexpr Complex_NumType<ScalarType>& operator+=(const Real_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator-=(const Real_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator*=(const Real_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator/=(const Real_NumType<ScalarType>& right_op);

                constexpr Complex_NumType<ScalarType>& operator+=(const Complex_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator-=(const Complex_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator*=(const Complex_NumType<ScalarType>& right_op);
                constexpr Complex_NumType<ScalarType>& operator/=(const Complex_NumType<ScalarType>& right_op);

            private:

                Complex<ScalarType> value;
            };
        } // namespace impl        
    } // namespace num
} // namespace alg



using namespace alg::num::impl;


template<typename ScalarType>
constexpr Complex_NumType<ScalarType>::Complex_NumType(const Complex<ScalarType>& value) :
    value(value)
{}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>::Complex_NumType(Complex<ScalarType>&& value) :
    value(std::move(value))
{}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType>::Complex_NumType(const Real_NumType<ScalarType>& num) :
    value(num.getReal().real(), 0)
{}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>::Complex_NumType(Real_NumType<ScalarType>&& num) :
    value(std::move(num.getReal().real()), 0)
{}


template<typename ScalarType>
constexpr const Complex<ScalarType>& Complex_NumType<ScalarType>::getComplex() const
{
    return value;
}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator+=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() + right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator-=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() - right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator*=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() * right_op.getReal().real());
    this->value.imag(this->value.imag() * right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator/=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() / right_op.getReal().real());
    this->value.imag(this->value.imag() / right_op.getReal().real());
    return *this;
}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator+=(const Complex_NumType<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator-=(const Complex_NumType<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator*=(const Complex_NumType<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator/=(const Complex_NumType<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}