#include <fp/data/nothing.h>
#include <fp/mixins/value.h>
#include <fp/operators/eq.h>
#include <fp/prelude/pure.h>
#include <fp/traits/eq.h>
#include <fp/traits/value.h>
#include <gtest/gtest.h>

using namespace fp::data::nothing;

using namespace fp::prelude;
using namespace fp::operators::eq;

template <template <typename> typename Data, typename A>
using WithValue = fp::mixins::storage::WithValue<Data, A>;

template <typename A>
struct TestStruct : WithValue<TestStruct, A> {
    using Base = WithValue<TestStruct, A>;
    using Base::Base;
};

TEST(Mixin_WithValue, backend_choice) {
    constexpr int arr[] = {1, 2, 3};
    const TestStruct da1 = pure<TestStruct>(arr);
    EXPECT_TRUE(da1.is_box());
    EXPECT_FALSE(da1.is_stack());
    EXPECT_EQ(da1.value().at(2), 3);

    TestStruct const da2 = pure<TestStruct>(42);
    EXPECT_FALSE(da2.is_box());
    EXPECT_TRUE(da2.is_stack());
    EXPECT_EQ(da2.value(), 42);
}

TEST(Mixin_WithValue, empty) {
    TestStruct const da = pure<TestStruct>(nothing);
    EXPECT_TRUE(da.is_box());
    EXPECT_EQ(da.value(), nothing);
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

TEST(Mixin_WithValue, static_apply_direct) {
    auto val = TestStruct<int>::apply(123);
    static_assert(std::is_same_v<decltype(val), TestStruct<int>>);
    EXPECT_EQ(val.value(), 123);
}

TEST(Mixin_WithValue, traits) {
    static_assert(fp::traits::value::HasApply<TestStruct<int>>);
    static_assert(fp::traits::value::HasValue<TestStruct<int>>);
}

TEST(Mixin_WithValue, value_type_alias) {
    static_assert(std::is_same_v<typename TestStruct<int>::value_type, int>);
    static_assert(
      std::is_same_v<
        typename TestStruct<std::vector<int>>::value_type, std::vector<int>>
    );
}
