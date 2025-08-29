// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers

#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp::core;
using namespace fp::core::mixins;
using namespace fp::prelude;
using namespace fp::traits;

template <typename A>
struct TestStruct : WithValue<TestStruct<A>> {
  private:
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;

  public:
    auto map(auto& f) -> TestStruct {
        return fp::core::Functor<TestStruct>::map<A>(f)(*this);
    }
};

TEST(Types_Functor_Laws, identity) {
    auto x = pure<TestStruct>(42);

    auto mapped = Functor<TestStruct>::map<int>([](auto&& x) { return x; })(x);

    EXPECT_EQ(mapped.value(), x.value());
}

TEST(Types_Functor_Laws, composition) {
    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };

    auto x = pure<TestStruct>(10);

    auto lhs = Functor<TestStruct>::map<int>(compose(f, g))(x);
    auto rhs =
      Functor<TestStruct>::map<int>(f)(Functor<TestStruct>::map<int>(g)(x));

    EXPECT_EQ(lhs.value(), rhs.value());
}

TEST(Types_Functor, has_and_is_traits) {
    static_assert(HasFunctor<TestStruct>);
    static_assert(IsFunctor<TestStruct>);
}
