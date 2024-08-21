#pragma once
#include <initializer_list>
#include <complex>
#include <utility>
#include <cmath>
#include "ALGEBRA.h"
#include "NumType.h"
#include "NumTypeOperators.h"
#include "Complex.h"
#include "Real_NumType.h"

namespace alg
{        
    namespace num
    {
        template<typename ScalarType>
        class INumType;

        namespace impl
        {
            template<typename ScalarType>
            class Complex_NumType : public INumType<ScalarType>
            {                    
            public:
                Complex_NumType(const Complex<ScalarType>& value);
                Complex_NumType(Complex<ScalarType>&& value);

                Complex_NumType(const Complex_NumType<ScalarType>& num) = default;
                Complex_NumType(Complex_NumType<ScalarType>&& num) = default;
                Complex_NumType(const Real_NumType<ScalarType>& num);
                Complex_NumType(Real_NumType<ScalarType>&& num);
                ~Complex_NumType() override = default;

                std::string getString() const override;
                ALGEBRA getAlgebraType() const override;
                INumType<ScalarType>* getCopy() const override;

                const Complex<ScalarType>& getComplex() const;

                Complex_NumType<ScalarType>& operator=(const Complex_NumType<ScalarType>& num) = delete;
                Complex_NumType<ScalarType>& operator=(Complex_NumType<ScalarType>&& num) = delete;

                Complex_NumType<ScalarType>& operator+=(const Real_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator-=(const Real_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator*=(const Real_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator/=(const Real_NumType<ScalarType>& right_op);

                Complex_NumType<ScalarType>& operator+=(const Complex_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator-=(const Complex_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator*=(const Complex_NumType<ScalarType>& right_op);
                Complex_NumType<ScalarType>& operator/=(const Complex_NumType<ScalarType>& right_op);

            private:

                Complex<ScalarType> value;
            };
        } // namespace impl        
    } // namespace num
} // namespace alg



//#include "Complex_NumType.cpp"

using namespace alg::num::impl;


template<typename ScalarType>
Complex_NumType<ScalarType>::Complex_NumType(const Complex<ScalarType>& value) :
    value(value)
{}
template<typename ScalarType>
Complex_NumType<ScalarType>::Complex_NumType(Complex<ScalarType>&& value) :
    value(std::move(value))
{}

template<typename ScalarType>
Complex_NumType<ScalarType>::Complex_NumType(const Real_NumType<ScalarType>& num) :
    value(num.getReal().real(), 0)
{}
template<typename ScalarType>
Complex_NumType<ScalarType>::Complex_NumType(Real_NumType<ScalarType>&& num) :
    value(std::move(num.getReal().real()), 0)
{}

template<typename ScalarType>
std::string Complex_NumType<ScalarType>::getString() const
{
    if constexpr (std::is_same_v<ScalarType, long double>)
    {
        if (value.imag() >= 0)
            return std::to_string(value.real()) + " + " + std::to_string(value.imag()) + "i";
        else
            return std::to_string(value.real()) + " + " + "(" + std::to_string(value.imag()) + "i" + ")";
    }
    else
    {
        if (value.imag() >= 0)
            return value.real().getString() + " + " + std::to_string(value.imag()) + "i";
        else
            return value.real().getString() + " + " + "(" + value.imag().getString() + "i" + ")";
    }
}
template<typename ScalarType>
ALGEBRA Complex_NumType<ScalarType>::getAlgebraType() const
{
    return ALGEBRA::COMPLEX;
}
template<typename ScalarType>
INumType<ScalarType>* Complex_NumType<ScalarType>::getCopy() const
{
    return new Complex_NumType<ScalarType>(this->value);
}

template<typename ScalarType>
const Complex<ScalarType>& Complex_NumType<ScalarType>::getComplex() const
{
    return value;
}

template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator+=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() + right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator-=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() - right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator*=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() * right_op.getReal().real());
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator/=(const Real_NumType<ScalarType>& right_op)
{
    this->value.real(this->value.real() / right_op.getReal().real());
    return *this;
}

template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator+=(const Complex_NumType<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator-=(const Complex_NumType<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator*=(const Complex_NumType<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
Complex_NumType<ScalarType>& Complex_NumType<ScalarType>::operator/=(const Complex_NumType<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}