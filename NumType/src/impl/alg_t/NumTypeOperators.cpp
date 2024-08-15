#include "NumTypeOperators.h"
#include "Real_NumType.h"
#include "Complex_NumType.h"


alg::num::INumType* alg::num::impl::alg_t::operator+(const Real_NumType& left_op, const Real_NumType& right_op)
{
    return new Real_NumType(left_op.a + right_op.a);
}
alg::num::INumType* alg::num::impl::alg_t::operator-(const Real_NumType& left_op, const Real_NumType& right_op)
{
    return new Real_NumType(left_op.a - right_op.a);
}
alg::num::INumType* alg::num::impl::alg_t::operator*(const Real_NumType& left_op, const Real_NumType& right_op)
{
    return new Real_NumType(left_op.a * right_op.a);
}
alg::num::INumType* alg::num::impl::alg_t::operator/(const Real_NumType& left_op, const Real_NumType& right_op)
{
    try { return new Real_NumType(left_op.a / right_op.a); }
    catch(...) { throw; }
}


INumType* alg::num::impl::alg_t::operator+(const Real_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(*dynamic_cast<Complex_NumType*>(Complex_NumType({left_op.getString(), "0"}) + right_op));
}
INumType* alg::num::impl::alg_t::operator-(const Real_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(*dynamic_cast<Complex_NumType*>(Complex_NumType({left_op.getString(), "0"}) - right_op));
}
INumType* alg::num::impl::alg_t::operator*(const Real_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(*dynamic_cast<Complex_NumType*>(Complex_NumType({left_op.getString(), "0"}) * right_op));
}
INumType* alg::num::impl::alg_t::operator/(const Real_NumType& left_op, const Complex_NumType& right_op)
{
    try { return new Complex_NumType(*dynamic_cast<Complex_NumType*>(Complex_NumType({left_op.getString(), "0"}) / right_op)); }
    catch(...) { throw; }
}


INumType* alg::num::impl::alg_t::operator+(const Complex_NumType& left_op, const Real_NumType& right_op)
{
    return right_op + left_op;
}
INumType* alg::num::impl::alg_t::operator-(const Complex_NumType& left_op, const Real_NumType& right_op)
{
    return right_op - left_op;
}
INumType* alg::num::impl::alg_t::operator*(const Complex_NumType& left_op, const Real_NumType& right_op)
{
    return right_op * left_op;
}
INumType* alg::num::impl::alg_t::operator/(const Complex_NumType& left_op, const Real_NumType& right_op)
{
    try { return right_op / left_op; }
    catch(...) { throw; }
}




alg::num::INumType* alg::num::impl::alg_t::operator+(const Complex_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(left_op.value + right_op.value);
}
alg::num::INumType* alg::num::impl::alg_t::operator-(const Complex_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(left_op.value - right_op.value);
}
alg::num::INumType* alg::num::impl::alg_t::operator*(const Complex_NumType& left_op, const Complex_NumType& right_op)
{
    return new Complex_NumType(left_op.value * right_op.value);
}
alg::num::INumType* alg::num::impl::alg_t::operator/(const Complex_NumType& left_op, const Complex_NumType& right_op)
{
    try { return new Complex_NumType(left_op.value / right_op.value); }
    catch(...) { throw; }
}