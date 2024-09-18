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

                std::string getString() const override;
                constexpr NUM getNumType() const override;
                constexpr INumType<ScalarType>* getCopy() const override;

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
std::string Real_NumType<ScalarType>::getString() const
{
    if constexpr (std::is_same_v<ScalarType, double>)
        return std::to_string(value.real());
    else
        return value.real().getString();
}
template<typename ScalarType>
constexpr NUM Real_NumType<ScalarType>::getNumType() const
{
    return NUM::REAL;
}
template<typename ScalarType>
constexpr INumType<ScalarType>* Real_NumType<ScalarType>::getCopy() const
{
    return new Real_NumType(this->value);
}

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