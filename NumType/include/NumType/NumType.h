#pragma once

#include <memory>
#include <string>
#include "alg.h"


namespace alg
{
    namespace num
    {
        class INumType;
        class NumType;

        
        class INumType
        {
        public:
            virtual ~INumType() = default;

            virtual std::string getString() const = 0;
            virtual ALGEBRA getAlgebraType() const = 0;
            virtual INumType* getCopy() const = 0;
        };  

        class NumType
        {
        public:
            NumType(const NumType& num);
            ~NumType() = default;

            static NumType constuctReal(const std::string& num);

            std::string getString() const;
            ALGEBRA getAlgebraType() const;

            NumType operator+(const NumType& right_op) const;
            NumType operator-(const NumType& right_op) const;
            NumType operator*(const NumType& right_op) const;
            NumType operator/(const NumType& right_op) const;

        private:
            NumType(INumType* num);

            std::unique_ptr<INumType> num;
        };        
    } // namespace num
} // namespace alg
