#include <iostream>

template <typename Function>
struct infix {
    explicit infix(Function f) : f(f) {}
    Function f;
};

template <typename Left, typename Function>
struct LeftAndFunction {
    template <typename Left_>
    LeftAndFunction(Left_ &&left, Function f)
        : left(std::forward<Left_>(left)), f(f) {}

    Left left;
    Function f;
};

template <typename Left, typename Function>
LeftAndFunction<std::remove_reference_t<Left>, Function> operator<<(
  Left &&left, infix<Function> const &infix
) {
    return LeftAndFunction<std::remove_reference_t<Left>, Function>(
      std::forward<Left>(left), infix.f
    );
}

template <typename Left, typename Function, typename Right>
decltype(auto) operator>>(LeftAndFunction<Left, Function> lf, Right &&right) {
    return lf.f(lf.left, std::forward<Right>(right));
}

// #define _(x) << x $

auto add = infix{[](auto a, auto b) { return a + b; }};
int main() {
    auto result = 2 << add >> 10;
    std::cout << result << std::endl;
    return 0;
}
