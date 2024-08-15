#include "StdScalarType.h"

#include<stdexcept>

using namespace alg::impl::scalar;


StdScalarType::StdScalarType(long double value) :
    value(value)
{}
StdScalarType::StdScalarType(const std::string& scalar) :
    value(0)
{
    char* end;
    value = strtold(scalar.c_str(), &end);
    if(*end)
        throw std::runtime_error("");
}
StdScalarType::StdScalarType(const StdScalarType& scalar) :
    value(scalar.value)
{}

inline std::string StdScalarType::getString() const
{
    return std::to_string(value);
}
inline long double StdScalarType::getLongDouble() const
{
    return value;
}

StdScalarType::operator bool() const
{
    return bool(value);
}

StdScalarType& StdScalarType::operator+=(const StdScalarType& right_op)
{
    this->value += right_op.value;
    return *this;
}
StdScalarType& StdScalarType::operator-=(const StdScalarType& right_op)
{
    this->value -= right_op.value;
    return *this;
}

StdScalarType StdScalarType::operator+(const StdScalarType& right_op) const
{
    return StdScalarType(this->value + right_op.value);
}
StdScalarType StdScalarType::operator-(const StdScalarType& right_op) const
{
    return StdScalarType(this->value - right_op.value);
}
StdScalarType StdScalarType::operator*(const StdScalarType& right_op) const
{
    return StdScalarType(this->value * right_op.value);
}
StdScalarType StdScalarType::operator/(const StdScalarType& right_op) const
{
    if (!right_op)
        throw std::runtime_error("");
    return StdScalarType(this->value / right_op.value);
}