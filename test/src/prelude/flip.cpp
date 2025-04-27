#include <fp/prelude/flip.h>
#include <gtest/gtest.h>

using namespace fp::prelude;

auto difference = [](int a, int b) { return a - b; };

struct MoveOnlyAdder {
    MoveOnlyAdder() = default;
    MoveOnlyAdder(MoveOnlyAdder&&) = default;
    MoveOnlyAdder& operator=(MoveOnlyAdder&&) = default;

    MoveOnlyAdder(const MoveOnlyAdder&) = delete;
    MoveOnlyAdder& operator=(const MoveOnlyAdder&) = delete;

    int operator()(int a, int b) const { return a + b; }
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
