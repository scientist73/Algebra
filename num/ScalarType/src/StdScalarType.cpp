#include "StdScalarType.h"

using namespace alg::num;


std::string StdScalarType::getString() const
{
    return std::to_string(value);
}

long double StdScalarType::scalar() const
{
    return value;
}
void StdScalarType::scalar(long double value)
{
    this->value = value;
}

StdScalarType& StdScalarType::operator+=(const StdScalarType& left_op)
{
    value += left_op.value;
    return *this;
}
StdScalarType& StdScalarType::operator-=(const StdScalarType& left_op)
{
    value -= left_op.value;
    return *this;
}
StdScalarType& StdScalarType::operator*=(const StdScalarType& left_op)
{
    value *= left_op.value;
    return *this;
}
StdScalarType& StdScalarType::operator/=(const StdScalarType& left_op)
{
    value /= left_op.value;
    return *this;
}


StdScalarType alg::num::operator+(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return StdScalarType(right_op.scalar() + left_op.scalar());
}
StdScalarType alg::num::operator-(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return StdScalarType(right_op.scalar() - left_op.scalar());
}
StdScalarType alg::num::operator*(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return StdScalarType(right_op.scalar() * left_op.scalar());
}
StdScalarType alg::num::operator/(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return StdScalarType(right_op.scalar() / left_op.scalar());
}

bool alg::num::operator>=(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() >= left_op.scalar();
}
bool alg::num::operator<=(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() <= left_op.scalar();
}
bool alg::num::operator>(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() > left_op.scalar();
}
bool alg::num::operator<(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() < left_op.scalar();
}
bool alg::num::operator==(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() == left_op.scalar();
}
bool alg::num::operator!=(const StdScalarType& right_op, const StdScalarType& left_op)
{
    return right_op.scalar() != left_op.scalar();
}