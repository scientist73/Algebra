#pragma once

#include "NumType.h"

using alg::num::INumType;

#define FRIEND_OPERATORS \
friend INumType* operator+(const Real_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator-(const Real_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator*(const Real_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator/(const Real_NumType& left_op, const Real_NumType& right_op);\
\
friend INumType* operator+(const Real_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator-(const Real_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator*(const Real_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator/(const Real_NumType& left_op, const Complex_NumType& right_op);\
\
friend INumType* operator+(const Complex_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator-(const Complex_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator*(const Complex_NumType& left_op, const Real_NumType& right_op);\
friend INumType* operator/(const Complex_NumType& left_op, const Real_NumType& right_op);\
\
friend INumType* operator+(const Complex_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator-(const Complex_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator*(const Complex_NumType& left_op, const Complex_NumType& right_op);\
friend INumType* operator/(const Complex_NumType& left_op, const Complex_NumType& right_op);\

namespace alg
{
    namespace num
    {
        namespace impl
        {
            namespace alg_t
            {
                class Real_NumType;
                class Complex_NumType;
            
                INumType* operator+(const Real_NumType& left_op, const Real_NumType& right_op);
                INumType* operator-(const Real_NumType& left_op, const Real_NumType& right_op);
                INumType* operator*(const Real_NumType& left_op, const Real_NumType& right_op);
                INumType* operator/(const Real_NumType& left_op, const Real_NumType& right_op);

                INumType* operator+(const Real_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator-(const Real_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator*(const Real_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator/(const Real_NumType& left_op, const Complex_NumType& right_op);

                INumType* operator+(const Complex_NumType& left_op, const Real_NumType& right_op);
                INumType* operator-(const Complex_NumType& left_op, const Real_NumType& right_op);
                INumType* operator*(const Complex_NumType& left_op, const Real_NumType& right_op);
                INumType* operator/(const Complex_NumType& left_op, const Real_NumType& right_op);

                INumType* operator+(const Complex_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator-(const Complex_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator*(const Complex_NumType& left_op, const Complex_NumType& right_op);
                INumType* operator/(const Complex_NumType& left_op, const Complex_NumType& right_op);
                
            } // namespace alg_t
        } // namespace impl        
    } // namespace num
} // namespace alg
