
#include <fp/mixins/eq.h>
#include <fp/mixins/value.h>
#include <fp/operators/eq.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

template <typename A>
struct DataClass;

template <typename A>
struct DataClass
    : fp::mixins::value::WithValue<DataClass, A>
    , fp::mixins::eq::WithEq<DataClass<A>> {};

TEST(Mixin_WithEq, is_Eq) {  //
    auto a = DataClass<int>{._value = 10};
    auto b = DataClass<int>{._value = 10};
    ASSERT_TRUE(a.equals(b));
}

TEST(Mixin_WithValue, is_Eq_complex) {
    static_assert(fp::traits::eq::Eq<TestStruct<std::vector<int>>>);
    TestStruct const da1 = pure<TestStruct>(std::vector{1, 2, 3});
    TestStruct const da2 = pure<TestStruct>(std::vector{1, 2, 3});
    TestStruct const da3 = pure<TestStruct>(std::vector{3, 2, 1});
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}

TEST(Mixin_WithValue, is_Eq_fundamental) {
    static_assert(fp::traits::eq::Eq<TestStruct<int>>);
    TestStruct const da1 = pure<TestStruct>(42);
    TestStruct const da2 = pure<TestStruct>(42);
    TestStruct const da3 = pure<TestStruct>(24);
    EXPECT_TRUE(da1 == da2);
    EXPECT_TRUE(da1 != da3);
}
