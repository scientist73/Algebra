#pragma once


namespace alg
{
    namespace num
    {
        template<typename ScalarType>
        class Real
        {
        public:
            constexpr Real(const ScalarType& value = ScalarType()) : value(value) {}

            constexpr ScalarType real() const;
            constexpr void real(const ScalarType& value);

            constexpr operator bool() const;

            constexpr Real<ScalarType>& operator=(const ScalarType& value);

            constexpr Real<ScalarType>& operator+=(const Real<ScalarType>& right_op);
            constexpr Real<ScalarType>& operator-=(const Real<ScalarType>& right_op);
            constexpr Real<ScalarType>& operator*=(const Real<ScalarType>& right_op);
            constexpr Real<ScalarType>& operator/=(const Real<ScalarType>& right_op);
        private:
            ScalarType value;
        };

        template<typename ScalarType>
        constexpr Real<ScalarType> operator+(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr Real<ScalarType> operator-(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr Real<ScalarType> operator*(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr Real<ScalarType> operator/(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);

        template<typename ScalarType>
        constexpr bool operator>=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr bool operator<=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr bool operator>(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr bool operator<(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr bool operator==(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        constexpr bool operator!=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        

    } // namespace num
} // namespace alg



using namespace alg::num;

// class Real
template<typename ScalarType>
constexpr ScalarType Real<ScalarType>::real() const
{
    return this->value;
}
template<typename ScalarType>
constexpr void Real<ScalarType>::real(const ScalarType& value)
{
    this->value = value;
}

template<typename ScalarType>
constexpr Real<ScalarType>::operator bool() const
{
    return bool(this->value);
}

template<typename ScalarType>
constexpr Real<ScalarType>& Real<ScalarType>::operator=(const ScalarType& value)
{
    this->value = value;
    return *this;
}

template<typename ScalarType>
constexpr Real<ScalarType>& Real<ScalarType>::operator+=(const Real<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real<ScalarType>& Real<ScalarType>::operator-=(const Real<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real<ScalarType>& Real<ScalarType>::operator*=(const Real<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
constexpr Real<ScalarType>& Real<ScalarType>::operator/=(const Real<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}

// Non-member operators
template<typename ScalarType>
constexpr Real<ScalarType> alg::num::operator+(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() + right_op.real());
}
template<typename ScalarType>
constexpr Real<ScalarType> alg::num::operator-(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() - right_op.real());
}
template<typename ScalarType>
constexpr Real<ScalarType> alg::num::operator*(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() * right_op.real());
}
template<typename ScalarType>
constexpr Real<ScalarType> alg::num::operator/(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() / right_op.real());
}

template<typename ScalarType>
constexpr bool alg::num::operator>=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() >= right_op.real();
}
template<typename ScalarType>
constexpr bool alg::num::operator<=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() <= right_op.real();
}
template<typename ScalarType>
constexpr bool alg::num::operator>(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() > right_op.real();
}
template<typename ScalarType>
constexpr bool alg::num::operator<(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() < right_op.real();
}
template<typename ScalarType>
constexpr bool alg::num::operator==(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() == right_op.real();
}
template<typename ScalarType>
constexpr bool alg::num::operator!=(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return left_op.real() != right_op.real();
}