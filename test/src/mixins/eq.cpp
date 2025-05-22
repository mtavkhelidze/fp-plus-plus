
#include <fp/mixins/eq.h>
#include <fp/traits/eq.h>
#include <gtest/gtest.h>

template <typename A>
struct DataClass : fp::mixins::eq::WithEq<DataClass<A>> {
    A _value;
    auto value() const { return _value; }
};
TEST(Mixin_WithEq, is_Eq) {  //
    auto a = DataClass<int>{._value = 10};
    auto b = DataClass<int>{._value = 10};
    ASSERT_TRUE(a.equals(b));
}
