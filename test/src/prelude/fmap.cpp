// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::core::mixins;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
  private:
    using Base = WithValue<TestStruct>;
    using Base::Base;
};

TEST(Prelude_fmap, works_with_identity) {
    auto original = pure<TestStruct>(42);
    auto result = fmap(identity)(original);
    ASSERT_EQ(original.value(), result.value());
}

TEST(Prelude_fmap, composition_law) {
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };
    auto original = pure<TestStruct>(10);

    auto lhs = fmap([&](int x) { return f(g(x)); })(original);
    auto rhs = fmap(f)(fmap(g)(original));

    ASSERT_EQ(lhs.value(), rhs.value());
}
