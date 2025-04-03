#ifndef __FP_TEST_SHORTS_H__
#define __FP_TEST_SHORTS_H__

// string
constexpr auto hello = [](std::string name) { return "Hello " + name; };

// int
constexpr auto increment = [](int x) { return x + 1; };
constexpr auto int_to_string = [](int x) { return std::to_string(x); };
constexpr auto make_multiplier = [](int x) {
    return [x](int y) { return x * y; };
};
constexpr auto square = [](int x) { return x * x; };
constexpr auto triple = [](int x) { return x * 3; };

#endif  // __FP_TEST_SHORTS_H__
