#include "NumType.h"
#include "Real_NumType.h"
#include "Complex_NumType.h"

#include <stdexcept>

using namespace alg::num;


#define OPERATOR_DEF(op) \
switch (this->num->getAlgebraType())\
{\
case ALGEBRA::REAL:\
    if (auto l_op = dynamic_cast<const impl::alg_t::Real_NumType*>(this->num.get()))\
        switch (right_op.num->getAlgebraType())\
        {\
        case ALGEBRA::REAL:\
            if (auto r_op = dynamic_cast<const impl::alg_t::Real_NumType*>(right_op.num.get()))\
                return NumType(*l_op op *r_op);\
            break;\
        case ALGEBRA::COMPLEX:\
            if (auto r_op = dynamic_cast<const impl::alg_t::Complex_NumType*>(right_op.num.get()))\
                return NumType(*l_op op *r_op);\
            break;\
        }\
    break;\
case ALGEBRA::COMPLEX:\
    if (auto l_op = dynamic_cast<const impl::alg_t::Complex_NumType*>(this->num.get()))\
        switch (right_op.num->getAlgebraType())\
        {\
        case ALGEBRA::REAL:\
            if (auto r_op = dynamic_cast<const impl::alg_t::Real_NumType*>(right_op.num.get()))\
                return NumType(*l_op op *r_op);\
            break;\
        case ALGEBRA::COMPLEX:\
            if (auto r_op = dynamic_cast<const impl::alg_t::Complex_NumType*>(right_op.num.get()))\
                return NumType(*l_op op *r_op);\
            break;\
        }\
    break;\
}\




NumType::NumType(INumType* num) : 
    num(num)
{}
NumType::NumType(const NumType& num) :
    num(num.num->getCopy())
{}

std::string NumType::getString() const
{
    return num->getString();
}

alg::ALGEBRA NumType::getAlgebraType() const
{
    return num->getAlgebraType();
}

NumType NumType::constuctReal(const std::string& num)
{
    return NumType(new impl::alg_t::Real_NumType(num));
}

NumType NumType::operator+(const NumType& right_op) const
{
    OPERATOR_DEF(+)

    throw std::runtime_error("");
}
NumType NumType::operator-(const NumType& right_op) const
{
    OPERATOR_DEF(-)

    throw std::runtime_error("");
}
NumType NumType::operator*(const NumType& right_op) const
{
    OPERATOR_DEF(*)

    throw std::runtime_error("");
}
NumType NumType::operator/(const NumType& right_op) const
{
    OPERATOR_DEF(/)

    throw std::runtime_error("");
}