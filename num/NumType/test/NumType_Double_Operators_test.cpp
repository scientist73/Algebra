#include "NumType.h"
#include "Real.h"
#include "Complex.h"
#include "gtest/gtest.h"

using alg::num::NumType;


struct RealDS
{
    double real;
};
struct ComplexDS
{
    double real;
    double imag;
};

# define makeRealNum(real_ds) NumType<double>(Real<double>(real_ds.real))
# define makeComplexNum(complex_ds) NumType<double>(Complex<double>(complex_ds.real, complex_ds.imag))



/* ===================================================Real_Real_Tests===================================================*/
struct R_R_Operation
{
    RealDS l_op;
    RealDS r_op;
    RealDS res;
};
class Num_R_R_Tests : public ::testing::TestWithParam<R_R_Operation> 
{
public:
    void InitOperands(RealDS l_op, RealDS r_op) { this->l_op = Real<double>(l_op.real); this->r_op = Real<double>(r_op.real); }
protected:
    NumType<double> l_op, r_op;
};

/* ---------------------------------------------------SUM--------------------------------------------------- */

class real_plus_real_test : public Num_R_R_Tests {};
TEST_P(real_plus_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), GetParam().res.real);
}
TEST_P(real_plus_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op += r_op;

    EXPECT_DOUBLE_EQ(l_op.getReal().real(), GetParam().res.real);
}
INSTANTIATE_TEST_SUITE_P(Default, real_plus_real_test, ::testing::Values(
    R_R_Operation{RealDS{3.5}, RealDS{5.8}, RealDS{9.3}},
    R_R_Operation{RealDS{0}, RealDS{5}, RealDS{5}}
));

TEST(real_plus_real_constexpr_test, Double)
{
    constexpr auto l_op = makeRealNum(RealDS{3.5});
    constexpr auto r_op = makeRealNum(RealDS{5.8});

    constexpr auto res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), RealDS{9.3}.real);
}

/* ---------------------------------------------------SUB--------------------------------------------------- */

class real_minus_real_test : public Num_R_R_Tests {};
TEST_P(real_minus_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), GetParam().res.real);
}
TEST_P(real_minus_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op -= r_op;

    EXPECT_DOUBLE_EQ(l_op.getReal().real(), GetParam().res.real);
}
INSTANTIATE_TEST_SUITE_P(Default, real_minus_real_test, ::testing::Values(
    R_R_Operation{RealDS{3.5}, RealDS{5.8}, RealDS{-2.3}},
    R_R_Operation{RealDS{6}, RealDS{2.4}, RealDS{3.6}}
));

TEST(real_minus_real_constexpr_test, Double)
{
    constexpr auto l_op = makeRealNum(RealDS{3.5});
    constexpr auto r_op = makeRealNum(RealDS{5.8});

    constexpr auto res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), RealDS{-2.3}.real);
}

/* ---------------------------------------------------MULT--------------------------------------------------- */

class real_mult_real_test : public Num_R_R_Tests {};
TEST_P(real_mult_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), GetParam().res.real);
}
TEST_P(real_mult_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op *= r_op;

    EXPECT_DOUBLE_EQ(l_op.getReal().real(), GetParam().res.real);
}
INSTANTIATE_TEST_SUITE_P(Default, real_mult_real_test, ::testing::Values(
    R_R_Operation{RealDS{5}, RealDS{3.2}, RealDS{16}},
    R_R_Operation{RealDS{-6}, RealDS{2.4}, RealDS{-14.4}}
));

TEST(real_mult_real_constexpr_test, Double)
{
    constexpr auto l_op = makeRealNum(RealDS{5});
    constexpr auto r_op = makeRealNum(RealDS{3.2});

    constexpr auto res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), RealDS{16}.real);
}

/* ---------------------------------------------------DIV--------------------------------------------------- */

class real_div_real_test : public Num_R_R_Tests {};
TEST_P(real_div_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), GetParam().res.real);
}
TEST_P(real_div_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op /= r_op;

    EXPECT_DOUBLE_EQ(l_op.getReal().real(), GetParam().res.real);
}
INSTANTIATE_TEST_SUITE_P(Default, real_div_real_test, ::testing::Values(
    R_R_Operation{RealDS{10}, RealDS{2}, RealDS{5}},
    R_R_Operation{RealDS{-12}, RealDS{8}, RealDS{-1.5}}
));

TEST(real_div_real_constexpr_test, Double)
{
    constexpr auto l_op = makeRealNum(RealDS{10});
    constexpr auto r_op = makeRealNum(RealDS{2});

    constexpr auto res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.getReal().real(), RealDS{5}.real);
}

/* ===================================================Real_Complex_Tests===================================================*/
struct R_C_Operation
{
    RealDS l_op;
    ComplexDS r_op;
    ComplexDS res;
};
class Num_R_C_Tests : public ::testing::TestWithParam<R_C_Operation> 
{
public:
    void InitOperands(RealDS l_op, ComplexDS r_op) { this->l_op = Real<double>(l_op.real); this->r_op = Complex<double>(r_op.real, r_op.imag); }
protected:
    NumType<double> l_op, r_op;
};

/* ---------------------------------------------------SUM--------------------------------------------------- */

class real_plus_complex_test : public Num_R_C_Tests {};
TEST_P(real_plus_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(real_plus_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op += r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, real_plus_complex_test, ::testing::Values(
    R_C_Operation{RealDS{6.7}, ComplexDS{2, 4}, ComplexDS{8.7, 4}},
    R_C_Operation{RealDS{3.2}, ComplexDS{-7, -1}, ComplexDS{-3.8, -1}}
));

TEST(DISABLED_real_plus_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeRealNum(RealDS{6.7});
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 4}));

    // fail to complile: operator+ for Complex<double> is not constexpr
    //constexpr auto res = l_op + r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{8.7, 4}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{8.7, 4}).imag);
}

/* ---------------------------------------------------SUB--------------------------------------------------- */

class real_minus_complex_test : public Num_R_C_Tests {};
TEST_P(real_minus_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(real_minus_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op -= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, real_minus_complex_test, ::testing::Values(
    R_C_Operation{RealDS{6.7}, ComplexDS{2, 4}, ComplexDS{4.7, -4}},
    R_C_Operation{RealDS{3.2}, ComplexDS{-7, -1}, ComplexDS{10.2, 1}}
));

TEST(DISABLED_real_minus_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeRealNum(RealDS{6.7});
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 4}));

    // fail to complile: operator- for Complex<double> is not constexpr
    //constexpr auto res = l_op - r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{4.7, -4}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{4.7, -4}).imag);
}

/* ---------------------------------------------------MULT--------------------------------------------------- */

class real_mult_complex_test : public Num_R_C_Tests {};
TEST_P(real_mult_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(real_mult_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op *= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, real_mult_complex_test, ::testing::Values(
    R_C_Operation{RealDS{6.7}, ComplexDS{2, 4}, ComplexDS{13.4, 26.8}},
    R_C_Operation{RealDS{3.2}, ComplexDS{-7, -1}, ComplexDS{-22.4, -3.2}}
));

TEST(DISABLED_real_mult_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeRealNum(RealDS{6.7});
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 4}));

    // fail to complile: operator* for Complex<double> is not constexpr
    //constexpr auto res = l_op * r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{13.4, 26.8}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{13.4, 26.8}).imag);
}

/* ---------------------------------------------------DIV--------------------------------------------------- */

class real_div_complex_test : public Num_R_C_Tests {};
TEST_P(real_div_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(real_div_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op /= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, real_div_complex_test, ::testing::Values(
    R_C_Operation{RealDS{3}, ComplexDS{5, 5}, ComplexDS{0.3, -0.3}},
    R_C_Operation{RealDS{2}, ComplexDS{10, 5}, ComplexDS{0.16, -0.08}}
));

TEST(DISABLED_real_div_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeRealNum(RealDS{3});
    constexpr auto r_op = makeComplexNum((ComplexDS{5, 5}));

    // fail to complile: operator/ for Complex<double> is not constexpr
    //constexpr auto res = l_op / r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{0.3, -0.3}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{0.3, -0.3}).imag);
}

/* ===================================================Complex_Real_Tests===================================================*/
struct C_R_Operation
{
    ComplexDS l_op;
    RealDS r_op;
    ComplexDS res;
};
class Num_C_R_Tests : public ::testing::TestWithParam<C_R_Operation> 
{
public:
    void InitOperands(ComplexDS l_op, RealDS r_op) { this->l_op = Complex<double>(l_op.real, l_op.imag); this->r_op = Real<double>(r_op.real); }
protected:
    NumType<double> l_op, r_op;
};

/* ---------------------------------------------------SUM--------------------------------------------------- */

class complex_plus_real_test : public Num_C_R_Tests {};
TEST_P(complex_plus_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_plus_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op += r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_plus_real_test, ::testing::Values(
    C_R_Operation{ComplexDS{3, 4}, RealDS{2}, ComplexDS{5, 4}},
    C_R_Operation{ComplexDS{3.2, -1}, RealDS{-7}, ComplexDS{-3.8, -1}}
));

TEST(DISABLED_complex_plus_real_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeRealNum(RealDS{2});

    // fail to complile: operator+ for Complex<double> is not constexpr
    //constexpr auto res = l_op + r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{5, 4}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{5, 4}).imag);
}

/* ---------------------------------------------------SUB--------------------------------------------------- */

class complex_minus_real_test : public Num_C_R_Tests {};
TEST_P(complex_minus_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_minus_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op -= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_minus_real_test, ::testing::Values(
    C_R_Operation{ComplexDS{3, 4}, RealDS{2}, ComplexDS{1, 4}},
    C_R_Operation{ComplexDS{3.2, -1}, RealDS{-7}, ComplexDS{10.2, -1}}
));

TEST(DISABLED_complex_minus_real_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeRealNum(RealDS{2});

    // fail to complile: operator- for Complex<double> is not constexpr
    //constexpr auto res = l_op - r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{1, 4}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{1, 4}).imag);
}

/* ---------------------------------------------------MULT--------------------------------------------------- */

class complex_mult_real_test : public Num_C_R_Tests {};
TEST_P(complex_mult_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_mult_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op *= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_mult_real_test, ::testing::Values(
    C_R_Operation{ComplexDS{3, 4}, RealDS{2}, ComplexDS{6, 8}},
    C_R_Operation{ComplexDS{3.2, -1}, RealDS{-7}, ComplexDS{-22.4, 7}}
));

TEST(DISABLED_complex_mult_real_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeRealNum(RealDS{2});

    // fail to complile: operator* for Complex<double> is not constexpr
    //constexpr auto res = l_op * r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{6, 8}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{6, 8}).imag);
}

/* ---------------------------------------------------DIV--------------------------------------------------- */

class complex_div_real_test : public Num_C_R_Tests {};
TEST_P(complex_div_real_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_div_real_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op /= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_div_real_test, ::testing::Values(
    C_R_Operation{ComplexDS{3, 4}, RealDS{2}, ComplexDS{1.5, 2}},
    C_R_Operation{ComplexDS{15, -2}, RealDS{-5}, ComplexDS{-3, 0.4}}
));

TEST(DISABLED_complex_div_real_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeRealNum(RealDS{2});

    // fail to complile: operator/ for Complex<double> is not constexpr
    //constexpr auto res = l_op / r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{1.5, 2}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{1.5, 2}).imag);
}

/* ===================================================Complex_Complex_Tests===================================================*/
struct C_C_Operation
{
    ComplexDS l_op;
    ComplexDS r_op;
    ComplexDS res;
};
class Num_C_C_Tests : public ::testing::TestWithParam<C_C_Operation> 
{
public:
    void InitOperands(ComplexDS l_op, ComplexDS r_op) { this->l_op = Complex<double>(l_op.real, l_op.imag); this->r_op = Complex<double>(r_op.real, r_op.imag); }
protected:
    NumType<double> l_op, r_op;
};

/* ---------------------------------------------------SUM--------------------------------------------------- */

class complex_plus_complex_test : public Num_C_C_Tests {};
TEST_P(complex_plus_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op + r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_plus_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op += r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_plus_complex_test, ::testing::Values(
    C_C_Operation{ComplexDS{3, 4}, ComplexDS{2, 2}, ComplexDS{5, 6}},
    C_C_Operation{ComplexDS{3.2, -1}, ComplexDS{-7, 3}, ComplexDS{-3.8, 2}}
));

TEST(DISABLED_complex_plus_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 2}));

    // fail to complile: operator+ for Complex<double> is not constexpr
    //constexpr auto res = l_op + r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{5, 6}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{5, 6}).imag);
}

/* ---------------------------------------------------SUB--------------------------------------------------- */

class complex_minus_complex_test : public Num_C_C_Tests {};
TEST_P(complex_minus_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op - r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_minus_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op -= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_minus_complex_test, ::testing::Values(
    C_C_Operation{ComplexDS{3, 4}, ComplexDS{2, 2}, ComplexDS{1, 2}},
    C_C_Operation{ComplexDS{3.2, -1}, ComplexDS{-7, 3}, ComplexDS{10.2, -4}}
));

TEST(DISABLED_complex_minus_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 2}));

    // fail to complile: operator- for Complex<double> is not constexpr
    //constexpr auto res = l_op - r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{1, 2}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{1, 2}).imag);
}

/* ---------------------------------------------------MULT--------------------------------------------------- */

class complex_mult_complex_test : public Num_C_C_Tests {};
TEST_P(complex_mult_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op * r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_mult_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op *= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_mult_complex_test, ::testing::Values(
    C_C_Operation{ComplexDS{3, 4}, ComplexDS{2, 2}, ComplexDS{-2, 14}},
    C_C_Operation{ComplexDS{3.2, -1}, ComplexDS{-7, 3}, ComplexDS{-19.4, 16.6}}
));

TEST(DISABLED_complex_mult_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 2}));

    // fail to complile: operator* for Complex<double> is not constexpr
    //constexpr auto res = l_op * r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{-2, 14}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{-2, 14}).imag);
}

/* ---------------------------------------------------DIV--------------------------------------------------- */

class complex_div_complex_test : public Num_C_C_Tests {};
TEST_P(complex_div_complex_test, Double)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    NumType<double> res = l_op / r_op;

    EXPECT_DOUBLE_EQ(res.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(res.getComplex().imag(), GetParam().res.imag);
}
TEST_P(complex_div_complex_test, Double_with_assignment)
{
    InitOperands(GetParam().l_op, GetParam().r_op);

    l_op /= r_op;

    EXPECT_DOUBLE_EQ(l_op.getComplex().real(), GetParam().res.real);
    EXPECT_DOUBLE_EQ(l_op.getComplex().imag(), GetParam().res.imag);
}
INSTANTIATE_TEST_SUITE_P(Default, complex_div_complex_test, ::testing::Values(
    C_C_Operation{ComplexDS{3, 4}, ComplexDS{2, 2}, ComplexDS{1.75, 0.25}},
    C_C_Operation{ComplexDS{6, 9}, ComplexDS{10, 5}, ComplexDS{0.84, 0.48}}
));

TEST(DISABLED_complex_div_complex_constexpr_test, Double)
{
    FAIL();

    constexpr auto l_op = makeComplexNum((ComplexDS{3, 4}));
    constexpr auto r_op = makeComplexNum((ComplexDS{2, 2}));

    // fail to complile: operator/ for Complex<double> is not constexpr
    //constexpr auto res = l_op / r_op;

    //EXPECT_DOUBLE_EQ(res.getComplex().real(), (ComplexDS{1.75, 0.25}).real);
    //EXPECT_DOUBLE_EQ(res.getComplex().imag(), (ComplexDS{1.75, 0.25}).imag);
}