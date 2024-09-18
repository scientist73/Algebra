#include <stdexcept>


namespace alg
{
    namespace util
    {
        namespace except
        {
            class AlgebraException : public std::exception
            {};
            class alg_exception : public std::exception
            {};
        } // namespace except
    } // namespace util
} // namespace alg
