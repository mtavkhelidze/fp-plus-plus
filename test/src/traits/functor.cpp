#include <fp/fp.h>
#include <gtest/gtest.h>

#include <functional>

using ::testing::Test;

using namespace fp;
using namespace fp::tools::arrow;

namespace functor_box {

template <typename A>
struct FunctorBox {
    A value;

    template <typename F>
    [[nodiscard]] auto map(F&& f) const {
        using RT = fp_arrow_result<F, A>;
        return FunctorBox<RT>{std::forward<F>(f)(A{value})};
    }
};

}  // namespace functor_box

TEST(Functor, identity_law) {  // NOLINT
    using namespace functor_box;

    using IntBox = FunctorBox<int>;
    IntBox const ib(10);

    static_assert(Functor<IntBox, std::identity>);

    ASSERT_TRUE(ib.map(std::identity()).value == ib.value);
}

TEST(Functor, composition_law) {  // NOLINT
    using namespace functor_box;

    using IntBox = FunctorBox<int>;
    IntBox const ib(10);

    auto f = [](int x) { return x + 1; };
    auto g = [](int x) { return x * 2; };

    auto composed = ib.map(f).map(g);
    auto sequential = ib.map([&](int x) { return g(f(x)); });

    ASSERT_EQ(composed.value, sequential.value);
}
