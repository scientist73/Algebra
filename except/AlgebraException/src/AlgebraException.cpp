#include <ranges>
#include "AlgebraException.h"
#include <array>

using namespace alg::except;

alg_exception::alg_exception() noexcept
{}
alg_exception::alg_exception(std::string_view error_msg) noexcept:
    error_msg(error_msg)
{}

const char* alg_exception::what() const noexcept
{
    return error_msg.data();
}