#pragma once
#include <string>


namespace alg
{
    namespace num
    {
        enum class NUM
        {
            REAL,
            COMPLEX,
        };

        template<typename ScalarType>
        class INumType
        {
        public:
            virtual std::string getString() const = 0;
            virtual NUM getNumType() const = 0;
            virtual INumType<ScalarType>* getCopy() const = 0;
        };
    } // namespace num
} // namespace alg
