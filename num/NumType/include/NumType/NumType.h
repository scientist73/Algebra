#pragma once
#include <variant>
#include <optional>
#include <string>
#include "Real.h"
#include "Complex.h"
#include "INumType.h"
#include "Real_NumType.h"
#include "Complex_NumType.h"


namespace alg
{
    namespace num
    {
        template<typename ScalarType>
        class NumType
        {
        public:
            constexpr NumType();

            constexpr NumType(const Real<ScalarType>& real_num);
            constexpr NumType(Real<ScalarType>&& real_num);
            constexpr NumType(const Complex<ScalarType>& complex_num);
            constexpr NumType(Complex<ScalarType>&& complex_num);

            std::string getString() const;
            constexpr NUM getNumType() const;

            constexpr Real<ScalarType> getReal() const;
            constexpr Complex<ScalarType> getComplex() const;

            constexpr NumType<ScalarType>& operator=(const Real<ScalarType>& real_num);
            constexpr NumType<ScalarType>& operator=(Real<ScalarType>&& real_num);
            constexpr NumType<ScalarType>& operator=(const Complex<ScalarType>& complex_num);
            constexpr NumType<ScalarType>& operator=(Complex<ScalarType>&& complex_num);

            constexpr NumType<ScalarType>& operator+=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator-=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator*=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator/=(const NumType& right_op);

            constexpr NumType<ScalarType> operator+(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator-(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator*(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator/(const NumType& right_op) const;

        private:
            constexpr NumType(const Real_NumType<ScalarType>& real_num);
            constexpr NumType(Real_NumType<ScalarType>&& real_num);
            constexpr NumType(const Complex_NumType<ScalarType>& complex_num);
            constexpr NumType(Complex_NumType<ScalarType>&& complex_num);

            constexpr bool is_valid() const;

            std::optional<std::variant<Real_NumType<ScalarType>, Complex_NumType<ScalarType>>> value;
        };

        template<typename ScalarType>
        constexpr bool operator==(const NumType<ScalarType>& left_op, const NumType<ScalarType>& right_op);
    } // namespace num
} // namespace alg



#include "NumTypeOperators.h"
#include <iostream>


using namespace alg::num;

template<typename ScalarType>
constexpr NumType<ScalarType>::NumType() :
    value()
{}

template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(const Real<ScalarType>& real_num) :
    NumType(Real_NumType<double>(real_num))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(Real<ScalarType>&& real_num) :
    NumType(Real_NumType<double>(std::move(real_num)))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(const Complex<ScalarType>& complex_num) :
    NumType(Complex_NumType<double>(complex_num))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(Complex<ScalarType>&& complex_num) :
    NumType(Complex_NumType<double>(std::move(complex_num)))
{}


template<typename ScalarType>
std::string NumType<ScalarType>::getString() const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::getString() error: NumType doesn't contain a value");
    return value->getString();
}
template<typename ScalarType>
constexpr NUM NumType<ScalarType>::getNumType() const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::getNumType() error: NumType doesn't contain a value");

    switch(this->value.value().index())
    {
    case 0:
        return NUM::REAL;
    case 1:
        return NUM::COMPLEX;
    default:
        throw std::runtime_error("");
    }
}

template<typename ScalarType>
constexpr Real<ScalarType> NumType<ScalarType>::getReal() const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::getReal() error: NumType doesn't contain a value");
    return std::get<Real_NumType<ScalarType>>(value.value()).getReal();
}
template<typename ScalarType>
constexpr Complex<ScalarType> NumType<ScalarType>::getComplex() const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::getComplex() error: NumType doesn't contain a value");
    return std::get<Complex_NumType<ScalarType>>(value.value()).getComplex();

/*
    if (auto complex_num = dynamic_cast<const Complex_NumType<ScalarType>*>(value.get()))
        return complex_num->getComplex();
    else
        throw std::runtime_error("NumType<ScalarType>::getComplex error: NumType is not a Complex type");
*/
}

template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator=(const Real<ScalarType>& real_num)
{
    value.reset(new Real<ScalarType>(real_num));
    return *this;
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator=(Real<ScalarType>&& real_num)
{
    value = Real_NumType<ScalarType>(std::move(real_num));
    return *this;
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator=(const Complex<ScalarType>& complex_num)
{
    value = Complex_NumType<ScalarType>(complex_num);
    return *this;
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator=(Complex<ScalarType>&& complex_num)
{
    value = Complex_NumType<ScalarType>(std::move(complex_num));
    return *this;
}

template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator+=(const NumType& right_op)
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator+= error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op += *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    this->value = Complex_NumType(*l_op + *r_op);
                    return *this;
                }
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op += *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op += *r_op;
                    return *this;                    
                }
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator+= error");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator-=(const NumType& right_op)
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator-= error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op -= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    this->value = Complex_NumType(*l_op - *r_op);
                    return *this;
                }
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op -= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op -= *r_op;
                    return *this;                    
                }
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator-= error");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator*=(const NumType& right_op)
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator*= error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op *= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    this->value = Complex_NumType(*l_op * *r_op);
                    return *this;
                }
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op *= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op *= *r_op;
                    return *this;                    
                }
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator*= error");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator/=(const NumType& right_op)
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator/= error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op /= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    this->value = Complex_NumType(*l_op / *r_op);
                    return *this;
                }
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op /= *r_op;
                    return *this;
                }
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                {
                    *l_op /= *r_op;
                    return *this;                    
                }
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator/= error");
}

template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator+(const NumType& right_op) const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator+ error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator+ error");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator-(const NumType& right_op) const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator- error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator- error");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator*(const NumType& right_op) const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator* error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator* error");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator/(const NumType& right_op) const
{
    if (!is_valid())
        throw std::runtime_error("NumType<ScalarType>::operator/ error: NumType doesn't contain a value");

    switch (this->getNumType())
    {
    case NUM::REAL:
        if (auto l_op = std::get_if<impl::Real_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            }
        }
        break;
    
    case NUM::COMPLEX:
        if (auto l_op = std::get_if<impl::Complex_NumType<ScalarType>>(&this->value.value()))
        {
            switch (right_op.getNumType())
            {
            case NUM::REAL:
                if (auto r_op = std::get_if<impl::Real_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            case NUM::COMPLEX:
                if (auto r_op = std::get_if<impl::Complex_NumType<ScalarType>>(&right_op.value.value()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator/ error");
}


template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(const Real_NumType<ScalarType>& real_num) :
    value(Real_NumType(real_num))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(Real_NumType<ScalarType>&& real_num) :
    value(Real_NumType(std::move(real_num)))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(const Complex_NumType<ScalarType>& complex_num) :
    value(Complex_NumType(complex_num))
{}
template<typename ScalarType>
constexpr NumType<ScalarType>::NumType(Complex_NumType<ScalarType>&& complex_num) :
    value(Complex_NumType(std::move(complex_num)))
{}

template<typename ScalarType>
inline constexpr bool NumType<ScalarType>::is_valid() const
{
    return value.has_value();
}

template<typename ScalarType>
constexpr bool alg::num::operator==(const NumType<ScalarType>& left_op, const NumType<ScalarType>& right_op)
{
    if (left_op.getNumType() == right_op.getNumType())
    {
        auto alg_t = left_op.getNumType();

        switch (alg_t)
        {
        case NUM::REAL:
            return right_op.getReal() == left_op.getReal();
        case NUM::COMPLEX:
            return right_op.getComplex() == left_op.getComplex();
        }
    }
    else
        return false;
}