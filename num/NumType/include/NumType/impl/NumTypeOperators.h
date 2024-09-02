#pragma once
#include "Real_NumType.h"
#include "Complex_NumType.h"


namespace alg
{
    namespace num
    {
        namespace impl
        {
            template<typename ScalarType> 
            constexpr Real_NumType<ScalarType> operator+(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            constexpr Real_NumType<ScalarType> operator-(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            constexpr Real_NumType<ScalarType> operator*(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            constexpr Real_NumType<ScalarType> operator/(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator+(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator-(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator*(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator/(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator+(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator-(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator*(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator/(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator+(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator-(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator*(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            constexpr Complex_NumType<ScalarType> operator/(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
        } // namespace impl        
    } // namespace num
} // namespace alg



using namespace alg::num::impl;


template<typename ScalarType> 
constexpr Real_NumType<ScalarType> alg::num::impl::operator+(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() + right_op.getReal());
}
template<typename ScalarType> 
constexpr Real_NumType<ScalarType> alg::num::impl::operator-(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() - right_op.getReal());
}
template<typename ScalarType> 
constexpr Real_NumType<ScalarType> alg::num::impl::operator*(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() * right_op.getReal());
}
template<typename ScalarType> 
constexpr Real_NumType<ScalarType> alg::num::impl::operator/(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() / right_op.getReal());
}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator+(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() + right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator-(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() - right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator*(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() * right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator/(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() / right_op.getComplex());
}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator+(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() + Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator-(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() - Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator*(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() * Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator/(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() / Complex_NumType(right_op).getComplex());
}

template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator+(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() + right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator-(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() - right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator*(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() * right_op.getComplex());
}
template<typename ScalarType>
constexpr Complex_NumType<ScalarType> alg::num::impl::operator/(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() / right_op.getComplex());
}