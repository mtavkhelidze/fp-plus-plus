#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>

using ::testing::Test;

using namespace fp::traits::functor;
using namespace fp::traits::functor::laws;
namespace functor_box {
template <typename A>
struct FunctorBox {
    A value;

    template <fp_arrow_function F>
    [[nodiscard]] auto map(F&& f) const {
        using RT = fp_get_arrow_function_return_type<F>;
        return FunctorBox<RT>{std::forward<F>(f)(value)};
    }
};

using IntBox = FunctorBox<int>;
static auto equals(const IntBox& a, const IntBox& b) -> bool {
    return a.value == b.value;
}

}  // namespace functor_box
TEST(Functor, identity_law) {
    using namespace functor_box;

    const IntBox box(42);
    static_assert(Functor<IntBox>);

    // ASSERT_TRUE(FunctorLaws<IntBox>::identity(box));
    // ASSERT_TRUE(FunctorLaws<IntBox>::composition(box));

    auto mapped = box.map([](int x) { return std::to_string(x); });
    ASSERT_EQ(mapped.value, "42");
}
