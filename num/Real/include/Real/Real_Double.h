#pragma once
#include <Real_Template.h>
#include <stdexcept>

namespace alg
{
    namespace num
    {
        template<>
        class Real<double>
        {
        public:
            constexpr Real(double value = double()) noexcept : value(value) {}

            constexpr double real() const noexcept;
            constexpr void real(double value) noexcept;

            constexpr operator bool() const noexcept;
            constexpr operator double() const noexcept;

            constexpr Real<double>& operator=(double value) noexcept;

            constexpr Real<double>& operator+=(const Real<double>& right_op) noexcept;
            constexpr Real<double>& operator-=(const Real<double>& right_op) noexcept;
            constexpr Real<double>& operator*=(const Real<double>& right_op) noexcept;
            constexpr Real<double>& operator/=(const Real<double>& right_op) noexcept;
        private:
            double value;
        };
    } // namespace num
} // namespace alg


using namespace alg::num;

constexpr double Real<double>::real() const noexcept
{
    return value;
}
constexpr void Real<double>::real(double value) noexcept
{
    this->value = value;
}

constexpr Real<double>::operator bool() const noexcept
{
    return bool(this->value);
}
constexpr Real<double>::operator double() const noexcept
{
    return this->value;
}

constexpr Real<double>& Real<double>::operator=(double value) noexcept
{
    this->value = value;
    return *this;
}

constexpr Real<double>& Real<double>::operator+=(const Real<double>& right_op) noexcept
{
    this->value += right_op.value;
    return *this;
}
constexpr Real<double>& Real<double>::operator-=(const Real<double>& right_op) noexcept
{
    this->value -= right_op.value;
    return *this;
}
constexpr Real<double>& Real<double>::operator*=(const Real<double>& right_op) noexcept
{
    this->value *= right_op.value;
    return *this;
}
constexpr Real<double>& Real<double>::operator/=(const Real<double>& right_op) noexcept
{
    this->value /= right_op.value;
    return *this;
}