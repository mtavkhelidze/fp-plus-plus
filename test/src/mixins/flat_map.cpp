#include <fp/mixins/flat_map.h>
#include <fp/mixins/value.h>
#include <fp/prelude/identity.h>
#include <fp/prelude/lift.h>
#include <fp/prelude/pure.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace fp::mixins::value;
using namespace fp::mixins::flat_map;
using namespace fp::prelude;
using namespace fp::tools::map;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithFlatMap<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Mixin_WithFlatMap, simple_map) {
    auto val = pure<TestStruct>(10);
    auto mapped = val.flatMap([](int x) { return pure<TestStruct>(x * 2); });
    static_assert(std::is_same_v<decltype(mapped), TestStruct<int>>);
    EXPECT_EQ(mapped.value(), 20);
}

TEST(Mixin_WithFlatMap, map_identity) {
    auto val = pure<TestStruct>(std::string("hello"));
    auto mapped =
      val.flatMap([](const std::string& s) { return pure<TestStruct>(s); });
    EXPECT_EQ(mapped.value(), "hello");
}

TEST(Mixin_WithFlatMap, map_complex_type) {
    auto val = pure<TestStruct>(std::vector<int>{1, 2, 3});
    auto mapped = val.flatMap([](const std::vector<int>& v) {
        std::vector<int> copy = v;
        copy.push_back(4);
        return pure<TestStruct>(copy);
    });
    static_assert(
      std::is_same_v<decltype(mapped), TestStruct<std::vector<int>>>
    );
    EXPECT_EQ(mapped.value().size(), 4);
    EXPECT_EQ(mapped.value().back(), 4);
}

// TEST(Mixin_WithFlatMap, static_assert_traits) {
//     static_assert(
//       HasMap<TestStruct<int>, decltype([](int x) { return x + 1; })>
//     );
// }

TEST(Mixin_WithFlatMap, value_type_alias) {
    static_assert(std::is_same_v<typename TestStruct<int>::value_type, int>);
    static_assert(
      std::is_same_v<
        typename TestStruct<std::vector<int>>::value_type, std::vector<int>>
    );
}

struct Doubler {
    TestStruct<int> operator()(int x) const { return pure<TestStruct>(x * 2); }
};

static TestStruct<int> triple(int x) { return pure<TestStruct>(x * 3); }

TEST(Mixin_WithFlatMap, map_with_callable_struct) {
    auto val = pure<TestStruct>(5);
    auto mapped = val.flatMap(Doubler{});
    EXPECT_EQ(mapped.value(), 10);
}

TEST(Mixin_WithFlatMap, map_with_function_pointer) {
    auto val = pure<TestStruct>(7);
    auto mapped = val.flatMap(triple);
    EXPECT_EQ(mapped.value(), 21);
}

TEST(Mixin_WithFlatMap, map_law_identity) {
    auto val = pure<TestStruct>(42);
    auto mapped = val.flatMap(lift<TestStruct>(identity));
    EXPECT_EQ(mapped.value(), val.value());
}
