// NOLINTBEGIN:cppcoreguidelines-avoid-magic-numbers
#include <fp/data/id.h>
#include <fp/mixins/map.h>
#include <fp/mixins/value.h>
#include <fp/prelude/fmap.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

using namespace fp::prelude;
using namespace fp::mixins::map;
using namespace fp::mixins::value;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithMap<TestStruct<A>> {
  private:
    using Base = WithValue<TestStruct>;
    using Base::Base;
};

TEST(Prelude_fmap, identity) {
    auto original = pure<TestStruct>(42);
    auto result = fmap(original, identity);
    static_assert(std::same_as<decltype(result), TestStruct<int>>);
    ASSERT_EQ(result.value(), 42);
}
