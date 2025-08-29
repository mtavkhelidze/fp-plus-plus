// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

#include <fp/core/all.h>
#include <fp/internal/mixins/eq.h>
#include <fp/prelude/all.h>
#include <fp/traits/all.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::internal::mixins;
using namespace fp::prelude;
using namespace fp::traits;
using namespace fp::mixins::eq;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithEq<TestStruct, A> {
  private:
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Types_Eq, has_and_is_traits) {
    static_assert(HasEq<TestStruct>);
    static_assert(IsEq<TestStruct>);
}

TEST(Types_Eq, reflexivity) {
    auto a = pure<TestStruct>(42);
    EXPECT_TRUE(a.equals(a));
}

TEST(Types_Eq, symmetry) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    EXPECT_EQ(a.equals(b), b.equals(a));
}

TEST(Types_Eq, transitivity) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    auto c = pure<TestStruct>(42);
    if (a.equals(b) && b.equals(c)) {
        EXPECT_TRUE(a.equals(c));
    }
}
