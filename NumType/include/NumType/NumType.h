#pragma once

#include <memory>
#include <string>
#include "alg.h"


namespace alg
{
    namespace num
    {
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
            NumType(NumType&& num);
            ~NumType() = default;

            static NumType constructReal(const std::string& num);
            static NumType constructComplex(const std::string& real, const std::string& imag);

            std::string getString() const;
            ALGEBRA getAlgebraType() const;

            NumType& operator=(const NumType& num);
            NumType& operator=(NumType&& num);

            NumType& operator+=(const NumType& right_op);
            NumType& operator-=(const NumType& right_op);
            NumType& operator*=(const NumType& right_op);
            NumType& operator/=(const NumType& right_op);

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
