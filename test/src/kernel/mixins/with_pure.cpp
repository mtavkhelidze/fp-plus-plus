#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

static_assert(IsWithPure<StructWithPure>, "StructWithPure must hapre ::pure");
static_assert(
  HasPure<StructWithPure<Whatever>>, "StructWithPure<int> must have ::pure"
);
static_assert(
  HasPure<StructWithPure<String>>, "StructWithPure<String> must have a ::pure"
);

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_const_int) {
    const int x = 42;
    auto val = StructWithPure<int>::pure(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_non_trivial_type_const_string) {
    const auto str = String("string");
    auto val = StructWithPure<String>::pure(str);
    ASSERT_EQ(val.value(), "string");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_int_rvalue) {
    auto val = StructWithPure<int>::pure(42);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_stack_for_trivial_type_double) {
    auto val = StructWithPure<double>::pure(3.14);
    ASSERT_DOUBLE_EQ(val.value(), 3.14);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, strips_const_ref_to_fundamental) {
    const int& x = 42;
    auto val = StructWithPure<int>::pure(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_string_literal) {
    auto val = StructWithPure<String>::pure("hello");
    ASSERT_EQ(val.value(), "hello");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, uses_box_for_vector) {
    Vector<int> v = {1, 2, 3};
    auto val = StructWithPure<Vector<int>>::pure(v);
    ASSERT_EQ(val.value(), v);
    ASSERT_TRUE(val.is_box());
}

TEST(Kernel_Mixins_WithValue, copy_shares_data) {
    auto a = StructWithPure<String>::pure(String("shared"));
    auto b = a;
    ASSERT_EQ(a.value(), b.value());
    ASSERT_EQ(&a.value(), &b.value());  // same underlying data
}

TEST(Kernel_Mixins_WithValue, nothing_uses_box) {
    auto val = StructWithPure<fp::Nothing>::pure(fp::nothing);
    ASSERT_TRUE(val.is_box());
}
