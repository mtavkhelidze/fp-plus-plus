#include <fp/fp.h>
#include <gtest/gtest.h>

#include <concepts>

using namespace fp;
using namespace fp::kernel::mixins;

template <typename A>
struct TestStruct
    : WithValue<TestStruct<A>>
    , WithFunctor<TestStruct<A>> {
    //
};
// as returns a callable
TEST(Kernel_Ops_As, returns_callable) {
    auto fa = pure<TestStruct>(42);
    auto arrow = as(fa);
    ASSERT_EQ(arrow(10).value(), 10);
}

// preserves structure, replaces value
TEST(Kernel_Ops_As, preserves_structure_replaces_value) {
    auto fa = pure<TestStruct>(42);
    auto result = as(fa)(String("hello"));
    static_assert(std::same_as<decltype(result), TestStruct<String>>);
    ASSERT_EQ(result.value(), "hello");
}
