#include "Real_NumType.h"

#include <stdexcept>

using namespace alg::num::impl::alg_t;
using alg::num::INumType;

Real_NumType::Real_NumType(const std::string& num) :
    a(num)
{}
Real_NumType::Real_NumType(const Real_NumType& num) :
    a(num.a)
{}
Real_NumType::Real_NumType(const ScalarType& num) :
    a(num)
{}

std::string Real_NumType::getString() const
{
    return a.getString();
}
alg::ALGEBRA Real_NumType::getAlgebraType() const
{
    return ALGEBRA::REAL;
}
INumType* Real_NumType::getCopy() const
{
    return new Real_NumType(this->a);
}
