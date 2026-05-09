#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;

    template <typename T>
    static auto create(T&& v) -> TestStruct<fp::cast<T>> {
        return TestStruct<fp::cast<T>>::apply(std::forward<T>(v));
    }
};

TEST(WithValue, uses_stack_for_trivial_type_const_int) {
    const int x = 42;
    auto val = TestStruct<int>::create(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(WithValue, usses_box_for_non_trivial_type_const_string) {
    const auto str = std::string("string");
    auto val = TestStruct<std::string>::create(str);
    ASSERT_EQ(val.value(), "string");
    ASSERT_TRUE(val.is_box());
}

TEST(WithValue, uses_stack_for_trivial_type_int_rvalue) {
    auto val = TestStruct<int>::create(42);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(WithValue, uses_stack_for_trivial_type_double) {
    auto val = TestStruct<double>::create(3.14);
    ASSERT_DOUBLE_EQ(val.value(), 3.14);
    ASSERT_TRUE(val.is_stack());
}

TEST(WithValue, strips_const_ref_to_fundamental) {
    const int& x = 42;
    auto val = TestStruct<int>::create(x);
    ASSERT_EQ(val.value(), 42);
    ASSERT_TRUE(val.is_stack());
}

TEST(WithValue, uses_box_for_string_literal) {
    auto val = TestStruct<std::string>::create("hello");
    ASSERT_EQ(val.value(), "hello");
    ASSERT_TRUE(val.is_box());
}

TEST(WithValue, uses_box_for_vector) {
    std::vector<int> v = {1, 2, 3};
    auto val = TestStruct<std::vector<int>>::create(v);
    ASSERT_EQ(val.value(), v);
    ASSERT_TRUE(val.is_box());
}

TEST(WithValue, copy_shares_data) {
    auto a = TestStruct<std::string>::create(std::string("shared"));
    auto b = a;
    ASSERT_EQ(a.value(), b.value());
    ASSERT_EQ(&a.value(), &b.value());  // same underlying data
}

TEST(WithValue, nothing_uses_box) {
    auto val = TestStruct<fp::Nothing>::create(fp::nothing);
    ASSERT_TRUE(val.is_box());
}
