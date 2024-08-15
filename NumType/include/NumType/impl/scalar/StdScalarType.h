#pragma once

#include "ScalarType.h"


namespace alg
{
    namespace impl
    {
        namespace scalar
        {
            class StdScalarType : public IScalarType
            {
            public:
                StdScalarType(long double value);
                StdScalarType(const std::string& scalar);
                StdScalarType(const StdScalarType& scalar);
                ~StdScalarType() override = default;

                std::string getString() const override;
                long double getLongDouble() const override;

                operator bool() const override;

                StdScalarType& operator+=(const StdScalarType& right_op);
                StdScalarType& operator-=(const StdScalarType& right_op);

                StdScalarType operator+(const StdScalarType& right_op) const;
                StdScalarType operator-(const StdScalarType& right_op) const;
                StdScalarType operator*(const StdScalarType& right_op) const;
                StdScalarType operator/(const StdScalarType& right_op) const;

            private:
                long double value;
            };
        } // namespace scalar
    } // namespace implement
} // namespace alg