#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;

static const auto difference = [](int a, int b) -> int { return a - b; };

struct MoveOnlyAdder {
    MoveOnlyAdder() = default;
    MoveOnlyAdder(MoveOnlyAdder&&) = default;
    ~MoveOnlyAdder() = default;
    auto operator=(MoveOnlyAdder&&) -> MoveOnlyAdder& = default;

    MoveOnlyAdder(const MoveOnlyAdder&) = delete;
    auto operator=(const MoveOnlyAdder&) -> MoveOnlyAdder& = delete;

    auto operator()(int a, int b) const -> int { return a + b; }
};

TEST(Prelude_Flip, flips) { ASSERT_EQ(flip(difference)(10, 1), -9); }

TEST(Prelude_Flip, flips_lambda) {
    auto divide = [](double a, double b) { return a / b; };
    auto flipped_divide = flip(divide);
    ASSERT_DOUBLE_EQ(flipped_divide(2.0, 10.0), 5.0);
}

TEST(Prelude_Flip, flips_move_only) {
    auto flipped_adder = flip(MoveOnlyAdder{});
    ASSERT_EQ(flipped_adder(3, 4), 7);
}
