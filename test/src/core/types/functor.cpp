// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

#include <fp/core/all.h>
#include <fp/mixins/all.h>
#include <fp/prelude/all.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::mixins;
using namespace fp::prelude;

template <typename A>
struct FunctorInstance : WithValue<FunctorInstance<A>> {
  private:
    using Base = WithValue<FunctorInstance<A>>;
    using Base::Base;
};

TEST(Functor_Laws, identity) {
    auto x = pure<FunctorInstance>(42);

    auto mapped =
      Functor<FunctorInstance>::map<int>([](auto&& x) { return x; })(x);

    EXPECT_EQ(mapped.value(), x.value());
}

TEST(Functor_Laws, composition) {
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };

    auto x = pure<FunctorInstance>(10);

    auto lhs = Functor<FunctorInstance>::map<int>(compose(f, g))(x);
    auto rhs = Functor<FunctorInstance>::map<
      int>(Functor<FunctorInstance>::map<int>(g)(x))(f);

    EXPECT_EQ(lhs.value(), rhs.value());
}
