#include "Complex_NumType.h"

using namespace alg::num::impl::alg_t;


Complex_NumType::Complex_NumType(const std::string& real, const std::string& imag) :
    value(real, imag)
{}
Complex_NumType::Complex_NumType(const Complex_NumType& complex_num) :
    value(complex_num.value)
{}
Complex_NumType::Complex_NumType(std::complex<ScalarType> complex_num) :
    value(complex_num)
{}

std::string Complex_NumType::getString() const
{
    return value.real().getString() + " + " + value.imag().getString() + "i";
}
alg::ALGEBRA Complex_NumType::getAlgebraType() const
{
    return ALGEBRA::COMPLEX;
}
INumType* Complex_NumType::getCopy() const
{
    return new Complex_NumType(*this);
}