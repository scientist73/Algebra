#pragma once
#include <string>
#include <ALGEBRA.h>


namespace alg
{
    namespace num
    {
        template<typename ScalarType>
        class INumType
        {
        public:
            virtual ~INumType() = default;

            virtual std::string getString() const = 0;
            virtual ALGEBRA getAlgebraType() const = 0;
            virtual INumType<ScalarType>* getCopy() const = 0;
        }; 
    } // namespace num
} // namespace alg
