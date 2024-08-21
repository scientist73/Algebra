#pragma once
#include "NumType.h"


namespace alg
{
    namespace num
    {
        namespace impl
        {
            template<typename ScalarType> class Real_NumType;
            template<typename ScalarType> class Complex_NumType;
        
            template<typename ScalarType> 
            Real_NumType<ScalarType> operator+(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            Real_NumType<ScalarType> operator-(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            Real_NumType<ScalarType> operator*(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType> 
            Real_NumType<ScalarType> operator/(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            Complex_NumType<ScalarType> operator+(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator-(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator*(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator/(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            Complex_NumType<ScalarType> operator+(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator-(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator*(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator/(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op);

            template<typename ScalarType>
            Complex_NumType<ScalarType> operator+(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator-(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator*(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
            template<typename ScalarType>
            Complex_NumType<ScalarType> operator/(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op);
        } // namespace impl        
    } // namespace num
} // namespace alg


using namespace alg::num::impl;


template<typename ScalarType> 
Real_NumType<ScalarType> alg::num::impl::operator+(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() + right_op.getReal());
}
template<typename ScalarType> 
Real_NumType<ScalarType> alg::num::impl::operator-(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() - right_op.getReal());
}
template<typename ScalarType> 
Real_NumType<ScalarType> alg::num::impl::operator*(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() * right_op.getReal());
}
template<typename ScalarType> 
Real_NumType<ScalarType> alg::num::impl::operator/(const Real_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Real_NumType(left_op.getReal() / right_op.getReal());
}

template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator+(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() + right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator-(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() - right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator*(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() * right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator/(const Real_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(Complex_NumType(left_op).getComplex() / right_op.getComplex());
}

template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator+(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() + Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator-(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() - Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator*(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() * Complex_NumType(right_op).getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator/(const Complex_NumType<ScalarType>& left_op, const Real_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() / Complex_NumType(right_op).getComplex());
}

template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator+(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() + right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator-(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() - right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator*(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() * right_op.getComplex());
}
template<typename ScalarType>
Complex_NumType<ScalarType> alg::num::impl::operator/(const Complex_NumType<ScalarType>& left_op, const Complex_NumType<ScalarType>& right_op)
{
    return Complex_NumType(left_op.getComplex() / right_op.getComplex());
}