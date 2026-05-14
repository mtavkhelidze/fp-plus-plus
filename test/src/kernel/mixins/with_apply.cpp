#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithApply<TestStruct<A>> {
    template <typename T>
    static auto create(T&& v) -> TestStruct<fp::cast<T>> {
        return TestStruct<fp::cast<T>>::apply(std::forward<T>(v));
    }
};

static_assert(
  HasApply<TestStruct<int>>, "TestStruct<int> must have a apply method"
);
static_assert(
  HasApply<TestStruct<String>>, "TestStruct<String> must have a apply method"
);
static_assert(
  HasApply<TestStruct<int>>, "TestStruct<int> must have a value method"
);
static_assert(
  HasApply<TestStruct<String>>, "TestStruct<String> must have a value method"
);

TEST(Kernal_Mixins_WithValue, uses_stack_for_trivial_type_const_int) {
    const int x = 42;
    auto val = TestStruct<int>::create(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernal_Mixins_WithValue, usses_box_for_non_trivial_type_const_string) {
    const auto str = String("string");
    auto val = TestStruct<String>::create(str);
    ASSERT_EQ(val.value(), "string");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernal_Mixins_WithValue, uses_stack_for_trivial_type_int_rvalue) {
    auto val = TestStruct<int>::create(42);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernal_Mixins_WithValue, uses_stack_for_trivial_type_double) {
    auto val = TestStruct<double>::create(3.14);
    ASSERT_DOUBLE_EQ(val.value(), 3.14);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernal_Mixins_WithValue, strips_const_ref_to_fundamental) {
    const int& x = 42;
    auto val = TestStruct<int>::create(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(Kernal_Mixins_WithValue, uses_box_for_string_literal) {
    auto val = TestStruct<String>::create("hello");
    ASSERT_EQ(val.value(), "hello");
    ASSERT_TRUE(val.is_box());
}

TEST(Kernal_Mixins_WithValue, uses_box_for_vector) {
    Vector<int> v = {1, 2, 3};
    auto val = TestStruct<Vector<int>>::create(v);
    ASSERT_EQ(val.value(), v);
    ASSERT_TRUE(val.is_box());
}

TEST(Kernal_Mixins_WithValue, copy_shares_data) {
    auto a = TestStruct<String>::create(String("shared"));
    auto b = a;
    ASSERT_EQ(a.value(), b.value());
    ASSERT_EQ(&a.value(), &b.value());  // same underlying data
}

TEST(Kernal_Mixins_WithValue, nothing_uses_box) {
    auto val = TestStruct<fp::Nothing>::create(fp::nothing);
    ASSERT_TRUE(val.is_box());
}
