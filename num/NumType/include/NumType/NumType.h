#pragma once
#include <variant>
#include <optional>
#include <string>
#include "Real.h"
#include "Complex.h"
#include "INumType.h"
#include "Real_NumType.h"
#include "Complex_NumType.h"
#include "NumTypeException.h"
#include <cassert>

namespace alg
{
    namespace num
    {
        namespace impl
        {
            template<typename SpecificNumType, typename ScalarType>
            concept IsSpecificNumType = 
                std::is_same<SpecificNumType, Real_NumType<ScalarType>>::value || 
                std::is_same<SpecificNumType, Complex_NumType<ScalarType>>::value;
        }

        template<typename SpecificNumType, typename ScalarType>
        concept IsSpecificNumType = 
            std::is_same<SpecificNumType, Real<ScalarType>>::value || 
            std::is_same<SpecificNumType, Complex<ScalarType>>::value;

        template<typename ScalarType>
        class NumType
        {
        public:
            constexpr NumType();
            template<typename SpecificNumType> requires IsSpecificNumType<SpecificNumType, ScalarType>
            constexpr NumType(SpecificNumType&& specific_num);

            constexpr NUM getNumType() const;

            template<typename SpecificNumType, typename _ScalarType> requires IsSpecificNumType<SpecificNumType, _ScalarType>
            friend constexpr const SpecificNumType& get_num(const NumType<_ScalarType>& num);

            template<typename SpecificNumType> requires IsSpecificNumType<SpecificNumType, ScalarType>
            constexpr NumType<ScalarType>& operator=(SpecificNumType&& specific_num);

            constexpr NumType<ScalarType>& operator+=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator-=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator*=(const NumType& right_op);
            constexpr NumType<ScalarType>& operator/=(const NumType& right_op);

            constexpr NumType<ScalarType> operator+(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator-(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator*(const NumType& right_op) const;
            constexpr NumType<ScalarType> operator/(const NumType& right_op) const;

        private:
            template<typename SpecificNumType> requires impl::IsSpecificNumType<SpecificNumType, ScalarType>
            constexpr NumType(SpecificNumType&& specific_num);

            constexpr bool has_value() const noexcept;

            std::optional<std::variant<Real_NumType<ScalarType>, Complex_NumType<ScalarType>>> value;
        };

        template<typename SpecificNumType, typename ScalarType> requires IsSpecificNumType<SpecificNumType, ScalarType>
        constexpr const SpecificNumType& get_num(const NumType<ScalarType>& num);


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
template<typename SpecificNumType> requires alg::num::IsSpecificNumType<SpecificNumType, ScalarType>
constexpr NumType<ScalarType>::NumType(SpecificNumType&& specific_num) :
    value(SpecificNumType(std::forward<SpecificNumType>(specific_num)))
{}

template<typename ScalarType>
constexpr NUM NumType<ScalarType>::getNumType() const
{
    if (!has_value())
        throw except::num_has_no_value("");

    switch(this->value.value().index())
    {
    case 0:
        return NUM::REAL;
    case 1:
        return NUM::COMPLEX;
    default:
        throw except::unknown_exception("");
    }
}

template<typename SpecificNumType, typename ScalarType> requires alg::num::IsSpecificNumType<SpecificNumType, ScalarType>
constexpr const SpecificNumType& alg::num::get_num(const NumType<ScalarType>& num)
{
    if (!num.has_value())
        throw except::num_has_no_value("");

    if constexpr (std::is_same<SpecificNumType, Real<ScalarType>>::value)
        return std::get<Real_NumType<ScalarType>>(num.value.value()).getReal();
    else if constexpr (std::is_same<SpecificNumType, Complex<ScalarType>>::value)
        return std::get<Complex_NumType<ScalarType>>(num.value.value()).getComplex();
    else
        throw except::unknown_exception("");
}

template<typename ScalarType>
template<typename SpecificNumType> 
    requires alg::num::IsSpecificNumType<SpecificNumType, ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator=(SpecificNumType&& specific_num)
{
    value = SpecificNumType(std::forward<SpecificNumType>(specific_num));
    return *this;
}


template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator+=(const NumType& right_op)
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator-=(const NumType& right_op)
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator*=(const NumType& right_op)
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType>& NumType<ScalarType>::operator/=(const NumType& right_op)
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}

template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator+(const NumType& right_op) const
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator-(const NumType& right_op) const
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator*(const NumType& right_op) const
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}
template<typename ScalarType>
constexpr NumType<ScalarType> NumType<ScalarType>::operator/(const NumType& right_op) const
{
    if (!has_value())
        throw except::num_has_no_value("");

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

    throw except::unknown_exception("");
}

template<typename ScalarType>
template<typename SpecificNumType> requires impl::IsSpecificNumType<SpecificNumType, ScalarType>
constexpr NumType<ScalarType>::NumType(SpecificNumType&& specific_num) :
    value(SpecificNumType(std::forward<SpecificNumType>(specific_num)))
{}

template<typename ScalarType>
inline constexpr bool NumType<ScalarType>::has_value() const noexcept
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