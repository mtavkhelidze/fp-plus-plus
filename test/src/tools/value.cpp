#include <fp/data/nothing.h>
#include <fp/mixins/value.h>
#include <fp/prelude/pure.h>
#include <fp/tools/value.h>
#include <gtest/gtest.h>

using namespace fp::data::nothing;
using namespace fp::prelude;
using namespace fp::tools::value;

template <typename Data>
using WithValue = fp::mixins::value::WithValue<Data>;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
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

TEST(Mixin_WithValue, static_apply_direct) {
    auto val = TestStruct<int>::apply(123);
    static_assert(std::is_same_v<decltype(val), TestStruct<int>>);
    EXPECT_EQ(val.value(), 123);
}

TEST(Mixin_WithValue, traits) {
    static_assert(HasApply<TestStruct<int>>);
    static_assert(HasValue<TestStruct<int>>);
}

TEST(Mixin_WithValue, value_type_alias) {
    static_assert(std::is_same_v<typename TestStruct<int>::value_type, int>);
    static_assert(
      std::is_same_v<
        typename TestStruct<std::vector<int>>::value_type, std::vector<int>>
    );
}
