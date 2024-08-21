#pragma once
#include <memory>
#include <string>
#include "ALGEBRA.h"
#include "Real_NumType.h"
#include "Complex_NumType.h"
#include "NumTypeOperators.h"
#include "Real.h"
#include "Complex.h"

namespace alg
{
    namespace num
    {
        template<typename ScalarType>
        class INumType
        {
        public:
            virtual ~INumType() = default;

            virtual std::string getString() const = 0;
            virtual ALGEBRA getAlgebraType() const = 0;
            virtual INumType<ScalarType>* getCopy() const = 0;
        };  



        template<typename ScalarType>
        class NumType
        {
        public:
            NumType(const Real<ScalarType>& real_num);
            NumType(Real<ScalarType>&& real_num);
            NumType(const Complex<ScalarType>& complex_num);
            NumType(Complex<ScalarType>&& complex_num);

            NumType(const NumType<ScalarType>& num);
            NumType(NumType<ScalarType>&& num) = default;
            ~NumType() = default;

            std::string getString() const;
            ALGEBRA getAlgebraType() const;

            Real<ScalarType> getReal() const;
            Complex<ScalarType> getComplex() const;

            NumType<ScalarType>& operator=(const Real<ScalarType>& real_num);
            NumType<ScalarType>& operator=(const Complex<ScalarType>& complex_num);

            NumType<ScalarType>& operator=(const NumType& num);
            NumType<ScalarType>& operator=(NumType&& num) = default;

            NumType<ScalarType>& operator+=(const NumType& right_op);
            NumType<ScalarType>& operator-=(const NumType& right_op);
            NumType<ScalarType>& operator*=(const NumType& right_op);
            NumType<ScalarType>& operator/=(const NumType& right_op);

            NumType<ScalarType> operator+(const NumType& right_op) const;
            NumType<ScalarType> operator-(const NumType& right_op) const;
            NumType<ScalarType> operator*(const NumType& right_op) const;
            NumType<ScalarType> operator/(const NumType& right_op) const;

        private:
            NumType(const Real_NumType<ScalarType>& real_num);
            NumType(Real_NumType<ScalarType>&& real_num);
            NumType(const Complex_NumType<ScalarType>& complex_num);
            NumType(Complex_NumType<ScalarType>&& complex_num);

            std::unique_ptr<INumType<ScalarType>> value;
        };        
    } // namespace num
} // namespace alg



using namespace alg::num;


template<typename ScalarType>
NumType<ScalarType>::NumType(const Real<ScalarType>& real_num) :
    value(new Real_NumType<ScalarType>(real_num))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(Real<ScalarType>&& real_num) :
    value(new Real_NumType<ScalarType>(std::move(real_num)))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(const Complex<ScalarType>& complex_num) :
    value(new Complex_NumType<ScalarType>(complex_num))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(Complex<ScalarType>&& complex_num) :
    value(new Complex_NumType<ScalarType>(std::move(complex_num)))
{}

template<typename ScalarType>
NumType<ScalarType>::NumType(const NumType<ScalarType>& num) :
    value(num.value->getCopy())
{}

template<typename ScalarType>
std::string NumType<ScalarType>::getString() const
{
    return value->getString();
}
template<typename ScalarType>
ALGEBRA NumType<ScalarType>::getAlgebraType() const
{
    return value->getAlgebraType();
}

template<typename ScalarType>
Real<ScalarType> NumType<ScalarType>::getReal() const
{
    return dynamic_cast<const Real_NumType<ScalarType>*>(value.get())->getReal();
}
template<typename ScalarType>
Complex<ScalarType> NumType<ScalarType>::getComplex() const
{
    return dynamic_cast<const Complex_NumType<ScalarType>*>(value.get())->getComplex();
}

template<typename ScalarType>
NumType<ScalarType>& NumType<ScalarType>::operator=(const Real<ScalarType>& real_num)
{
    value.reset(new Real<ScalarType>(real_num));
    return *this;
}
template<typename ScalarType>
NumType<ScalarType>& NumType<ScalarType>::operator=(const Complex<ScalarType>& complex_num)
{
    value.reset(new Complex<ScalarType>(complex_num));
    return *this;    
}

template<typename ScalarType>
NumType<ScalarType>& NumType<ScalarType>::operator=(const NumType& num)
{
    value.reset(new NumType<ScalarType>(num));
    return *this;
}

template<typename ScalarType>
NumType<ScalarType>& NumType<ScalarType>::operator+=(const NumType& right_op)
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op += *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                {
                    this->value.reset(new Complex_NumType(*l_op + *r_op));
                    return *this;
                }
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op += *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
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
NumType<ScalarType>& NumType<ScalarType>::operator-=(const NumType& right_op)
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op -= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                {
                    this->value.reset(new Complex_NumType(*l_op - *r_op));
                    return *this;
                }
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op -= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
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
NumType<ScalarType>& NumType<ScalarType>::operator*=(const NumType& right_op)
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op *= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                {
                    this->value.reset(new Complex_NumType(*l_op * *r_op));
                    return *this;
                }
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op *= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
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
NumType<ScalarType>& NumType<ScalarType>::operator/=(const NumType& right_op)
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op /= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                {
                    this->value.reset(new Complex_NumType(*l_op / *r_op));
                    return *this;
                }
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                {
                    *l_op /= *r_op;
                    return *this;
                }
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
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
NumType<ScalarType> NumType<ScalarType>::operator+(const NumType& right_op) const
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op + *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator+ error");
}
template<typename ScalarType>
NumType<ScalarType> NumType<ScalarType>::operator-(const NumType& right_op) const
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op - *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator- error");
}
template<typename ScalarType>
NumType<ScalarType> NumType<ScalarType>::operator*(const NumType& right_op) const
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op * *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator* error");
}
template<typename ScalarType>
NumType<ScalarType> NumType<ScalarType>::operator/(const NumType& right_op) const
{
    switch (this->getAlgebraType())
    {
    case ALGEBRA::REAL:
        if (auto l_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            }
        }
        break;
    
    case ALGEBRA::COMPLEX:
        if (auto l_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(this->value.get()))
        {
            switch (right_op.getAlgebraType())
            {
            case ALGEBRA::REAL:
                if (auto r_op = dynamic_cast<const impl::Real_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;
            case ALGEBRA::COMPLEX:
                if (auto r_op = dynamic_cast<const impl::Complex_NumType<ScalarType>*>(right_op.value.get()))
                    return NumType<ScalarType>(*l_op / *r_op);
                break;         
            }
        }
        break;
    }

    throw std::runtime_error("NumType<ScalarType>::operator/ error");
}


template<typename ScalarType>
NumType<ScalarType>::NumType(const Real_NumType<ScalarType>& real_num) :
    value(new Real_NumType(real_num))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(Real_NumType<ScalarType>&& real_num) :
    value(new Real_NumType(std::move(real_num)))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(const Complex_NumType<ScalarType>& complex_num) :
    value(new Complex_NumType(complex_num))
{}
template<typename ScalarType>
NumType<ScalarType>::NumType(Complex_NumType<ScalarType>&& complex_num) :
    value(new Complex_NumType(std::move(complex_num)))
{}