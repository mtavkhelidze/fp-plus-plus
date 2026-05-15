#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

static_assert(IsApply<StructApply>, "StructApply must be an applyable object");
static_assert(
  HasPure<StructApply<int>>, "StructApply<int> must have a apply method"
);
static_assert(
  HasPure<StructApply<String>>, "StructApply<String> must have a apply method"
);

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_const_int) {
    const int x = 42;
    auto val = StructApply<int>::pure(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_non_trivial_type_const_string) {
    const auto str = String("string");
    auto val = StructApply<String>::pure(str);
    ASSERT_EQ(val.value(), "string");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_int_rvalue) {
    auto val = StructApply<int>::pure(42);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_double) {
    auto val = StructApply<double>::pure(3.14);
    ASSERT_DOUBLE_EQ(val.value(), 3.14);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, strips_const_ref_to_fundamental) {
    const int& x = 42;
    auto val = StructApply<int>::pure(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_string_literal) {
    auto val = StructApply<String>::pure("hello");
    ASSERT_EQ(val.value(), "hello");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_vector) {
    Vector<int> v = {1, 2, 3};
    auto val = StructApply<Vector<int>>::pure(v);
    ASSERT_EQ(val.value(), v);
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, copy_shares_data) {
    auto a = StructApply<String>::pure(String("shared"));
    auto b = a;
    ASSERT_EQ(a.value(), b.value());
    ASSERT_EQ(&a.value(), &b.value());  // same underlying data
}

TEST(Kernel_Mixins_WithValue, nothing_uses_box) {
    auto val = StructApply<fp::Nothing>::pure(fp::nothing);
    ASSERT_TRUE(val.is_box());
}
