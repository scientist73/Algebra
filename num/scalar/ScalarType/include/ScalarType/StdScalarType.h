#pragma once
#include "IScalarType.h"


namespace alg
{
    namespace num
    {
        namespace scalar
        {
            class StdScalarType : public IScalarType
            {
            public:
                constexpr StdScalarType(long double value = 0.0l) : value(value) {}

                std::string getString() const override;

                long double scalar() const;
                void scalar(long double value);

                StdScalarType& operator+=(const StdScalarType& left_op);
                StdScalarType& operator-=(const StdScalarType& left_op);
                StdScalarType& operator*=(const StdScalarType& left_op);
                StdScalarType& operator/=(const StdScalarType& left_op);
            private:
                long double value;
            };

            StdScalarType operator+(const StdScalarType& right_op, const StdScalarType& left_op);
            StdScalarType operator-(const StdScalarType& right_op, const StdScalarType& left_op);
            StdScalarType operator*(const StdScalarType& right_op, const StdScalarType& left_op);
            StdScalarType operator/(const StdScalarType& right_op, const StdScalarType& left_op);

            bool operator>=(const StdScalarType& right_op, const StdScalarType& left_op);
            bool operator<=(const StdScalarType& right_op, const StdScalarType& left_op);
            bool operator>(const StdScalarType& right_op, const StdScalarType& left_op);
            bool operator<(const StdScalarType& right_op, const StdScalarType& left_op);
            bool operator==(const StdScalarType& right_op, const StdScalarType& left_op);
            bool operator!=(const StdScalarType& right_op, const StdScalarType& left_op);
            
        } // namespace scalar
    } // namespace num
} // namespace alg