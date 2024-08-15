#pragma once

#include <string>
#include <memory>

namespace alg
{
    namespace impl
    {
        namespace scalar
        {
            class IScalarType
            {
            public:
                virtual ~IScalarType() = default;

                virtual std::string getString() const = 0;
                virtual long double getLongDouble() const = 0;

                virtual operator bool() const = 0;

                //virtual IScalarType* operator+(const IScalarType* right_op) const = 0;
                //virtual IScalarType* operator-(const IScalarType* right_op) const = 0;
                //virtual IScalarType* operator*(const IScalarType* right_op) const = 0;
                //virtual IScalarType* operator/(const IScalarType* right_op) const = 0;
            };          
        } // namespace scalar
    } // namespace implement
} // namespace alg

