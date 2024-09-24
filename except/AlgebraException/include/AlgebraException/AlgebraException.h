#pragma once
#include <stdexcept>
#include <string_view>

namespace alg
{
    namespace except
    {
        class alg_exception
        {
        public:
            explicit alg_exception(std::string_view error_msg) noexcept;
            virtual ~alg_exception() noexcept = default;
            virtual std::string_view what() const noexcept;

        protected:
            std::string_view error_msg;
        };



        class unknown_exception : public alg_exception
        {
        public:
            explicit unknown_exception(std::string_view error_msg) noexcept : alg_exception(error_msg) {}
        };
        
    } // namespace except
} // namespace alg