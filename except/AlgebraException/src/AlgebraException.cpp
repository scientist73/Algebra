#include "AlgebraException.h"

using namespace alg::except;

alg_exception::alg_exception(std::string_view error_msg) noexcept:
    error_msg(error_msg)
{}

std::string_view alg_exception::what() const noexcept
{
    return error_msg;
}