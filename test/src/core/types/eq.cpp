// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

#include <fp/core/all.h>
#include <fp/internal/mixins/eq.h>
#include <fp/operators/all.h>
#include <fp/prelude/all.h>
#include <fp/traits/all.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::internal::mixins;
using namespace fp::prelude;
using namespace fp::operators;
using namespace fp::traits;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
  private:
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;

  public:
    auto equals(const TestStruct<A>& other) const -> bool {
        return fp::core::Eq<TestStruct>::equals(*this, other);
    }
};

TEST(Types_Eq, typeclass_equals) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    auto c = pure<TestStruct>(43);
    ASSERT_TRUE(Eq<TestStruct>::equals(a, b));
    ASSERT_FALSE(Eq<TestStruct>::equals(a, c));
}

TEST(Types_Eq, operator_equals) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(42);
    ASSERT_TRUE(a == b);
}

TEST(Types_Eq, operator_not_equals) {
    auto a = pure<TestStruct>(42);
    auto b = pure<TestStruct>(43);
    ASSERT_TRUE(a != b);
}

TEST(Types_Eq, has_and_is_traits) {
    static_assert(HasEq<TestStruct>);
    static_assert(IsEq<TestStruct>);
}
