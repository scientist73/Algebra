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

            ScalarType real() const;
            void real(const ScalarType& value);

            Real<ScalarType>& operator+=(const Real<ScalarType>& right_op);
            Real<ScalarType>& operator-=(const Real<ScalarType>& right_op);
            Real<ScalarType>& operator*=(const Real<ScalarType>& right_op);
            Real<ScalarType>& operator/=(const Real<ScalarType>& right_op);
        private:
            ScalarType value;
        };

        template<typename ScalarType>
        Real<ScalarType> operator+(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        Real<ScalarType> operator-(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        Real<ScalarType> operator*(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);
        template<typename ScalarType>
        Real<ScalarType> operator/(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op);

    } // namespace num
} // namespace alg



using namespace alg::num;

// class Real
template<typename ScalarType>
ScalarType Real<ScalarType>::real() const
{
    return value;
}
template<typename ScalarType>
void Real<ScalarType>::real(const ScalarType& value)
{
    this->value = value;
}

template<typename ScalarType>
Real<ScalarType>& Real<ScalarType>::operator+=(const Real<ScalarType>& right_op)
{
    this->value += right_op.value;
    return *this;
}
template<typename ScalarType>
Real<ScalarType>& Real<ScalarType>::operator-=(const Real<ScalarType>& right_op)
{
    this->value -= right_op.value;
    return *this;
}
template<typename ScalarType>
Real<ScalarType>& Real<ScalarType>::operator*=(const Real<ScalarType>& right_op)
{
    this->value *= right_op.value;
    return *this;
}
template<typename ScalarType>
Real<ScalarType>& Real<ScalarType>::operator/=(const Real<ScalarType>& right_op)
{
    this->value /= right_op.value;
    return *this;
}

// Non-member operators
template<typename ScalarType>
Real<ScalarType> alg::num::operator+(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() + right_op.real());
}
template<typename ScalarType>
Real<ScalarType> alg::num::operator-(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() - right_op.real());
}
template<typename ScalarType>
Real<ScalarType> alg::num::operator*(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() * right_op.real());
}
template<typename ScalarType>
Real<ScalarType> alg::num::operator/(const Real<ScalarType>& left_op, const Real<ScalarType>& right_op)
{
    return Real<ScalarType>(left_op.real() / right_op.real());
}
