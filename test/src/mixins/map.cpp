#include <fp/mixins/map.h>
#include <fp/mixins/value.h>
#include <fp/prelude/identity.h>
#include <fp/prelude/pure.h>
#include <fp/tools/map.h>
#include <fp/tools/value.h>
#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace fp::mixins::map;
using namespace fp::mixins::value;
using namespace fp::prelude;
using namespace fp::tools::map;
using namespace fp::tools::value;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithMap<TestStruct<A>> {
    using Base = WithValue<TestStruct<A>>;
    using Base::Base;
};

TEST(Mixin_WithMap, simple_map) {
    auto val = pure<TestStruct>(10);
    auto mapped = val.map([](int x) { return x * 2; });
    static_assert(std::is_same_v<decltype(mapped), TestStruct<int>>);
    EXPECT_EQ(mapped.value(), 20);
}

TEST(Mixin_WithMap, map_identity) {
    auto val = pure<TestStruct>(std::string("hello"));
    auto mapped = val.map([](const std::string& s) { return s; });
    EXPECT_EQ(mapped.value(), "hello");
}

TEST(Mixin_WithMap, map_complex_type) {
    auto val = pure<TestStruct>(std::vector<int>{1, 2, 3});
    auto mapped = val.map([](const std::vector<int>& v) {
        std::vector<int> copy = v;
        copy.push_back(4);
        return copy;
    });
    static_assert(
      std::is_same_v<decltype(mapped), TestStruct<std::vector<int>>>
    );
    EXPECT_EQ(mapped.value().size(), 4);
    EXPECT_EQ(mapped.value().back(), 4);
}

TEST(Mixin_WithMap, static_assert_traits) {
    static_assert(
      HasMap<TestStruct<int>, decltype([](int x) { return x + 1; })>
    );
}

TEST(Mixin_WithMap, value_type_alias) {
    static_assert(std::is_same_v<typename TestStruct<int>::value_type, int>);
    static_assert(
      std::is_same_v<
        typename TestStruct<std::vector<int>>::value_type, std::vector<int>>
    );
}

struct Doubler {
    int operator()(int x) const { return x * 2; }
};

static int triple(int x) { return x * 3; }

TEST(Mixin_WithMap, map_with_callable_struct) {
    auto val = pure<TestStruct>(5);
    auto mapped = val.map(Doubler{});
    EXPECT_EQ(mapped.value(), 10);
}

TEST(Mixin_WithMap, map_with_function_pointer) {
    auto val = pure<TestStruct>(7);
    auto mapped = val.map(triple);
    EXPECT_EQ(mapped.value(), 21);
}

TEST(Mixin_WithMap, map_law_identity) {
    auto val = pure<TestStruct>(42);
    auto mapped = val.map(identity);
    EXPECT_EQ(mapped.value(), val.value());
}
