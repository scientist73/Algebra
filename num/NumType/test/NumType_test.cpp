#include "NumType.h"
#include "Real.h"
#include "Complex.h"
#include "gtest/gtest.h"

using alg::num::NumType;

TEST(NumType, RealReal_OperatorA_test)
{
    Real<double> x1(256);
    Real<double> x2(32);

    NumType<double> var1 = x1;
    NumType<double> var2 = x2;

    EXPECT_DOUBLE_EQ((var1+var2).getReal().real(), (x1 + x2).real());
    EXPECT_DOUBLE_EQ((var1-var2).getReal().real(), (x1 - x2).real());
    EXPECT_DOUBLE_EQ((var1*var2).getReal().real(), (x1 * x2).real());
    EXPECT_DOUBLE_EQ((var1/var2).getReal().real(), (x1 / x2).real());
}

TEST(NumType, RealComplex_OperatorA_test)
{
    Real<double> x1_real(256); Complex<double> x1(256);
    Complex<double> x2(32, 2);

    NumType<double> var1 = x1_real;
    NumType<double> var2 = x2;

    EXPECT_DOUBLE_EQ((var1+var2).getComplex().real(), (x1 + x2).real());
    EXPECT_DOUBLE_EQ((var1+var2).getComplex().imag(), (x1 + x2).imag());
    EXPECT_DOUBLE_EQ((var1-var2).getComplex().real(), (x1 - x2).real());
    EXPECT_DOUBLE_EQ((var1-var2).getComplex().imag(), (x1 - x2).imag());    
    EXPECT_DOUBLE_EQ((var1*var2).getComplex().real(), (x1 * x2).real());
    EXPECT_DOUBLE_EQ((var1*var2).getComplex().imag(), (x1 * x2).imag());
    EXPECT_DOUBLE_EQ((var1/var2).getComplex().real(), (x1 / x2).real());
    EXPECT_DOUBLE_EQ((var1/var2).getComplex().imag(), (x1 / x2).imag());
}

TEST(NumType, ComplexComplex_OperatorA_test)
{
    Complex<double> x1(256, 50);
    Complex<double> x2(32, 25);

    NumType<double> var1 = x1;
    NumType<double> var2 = x2;

    EXPECT_DOUBLE_EQ((var1+var2).getComplex().real(), (x1 + x2).real());
    EXPECT_DOUBLE_EQ((var1+var2).getComplex().imag(), (x1 + x2).imag());
    EXPECT_DOUBLE_EQ((var1-var2).getComplex().real(), (x1 - x2).real());
    EXPECT_DOUBLE_EQ((var1-var2).getComplex().imag(), (x1 - x2).imag());    
    EXPECT_DOUBLE_EQ((var1*var2).getComplex().real(), (x1 * x2).real());
    EXPECT_DOUBLE_EQ((var1*var2).getComplex().imag(), (x1 * x2).imag());
    EXPECT_DOUBLE_EQ((var1/var2).getComplex().real(), (x1 / x2).real());
    EXPECT_DOUBLE_EQ((var1/var2).getComplex().imag(), (x1 / x2).imag());
}