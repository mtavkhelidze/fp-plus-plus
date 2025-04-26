#ifndef FP_TEST_INCLUDE__SHORTS_H_
#define FP_TEST_INCLUDE__SHORTS_H_
#pragma once

#include <iostream>
#include <string>

namespace fp::test {

template <typename... Args>
void print_err(Args&&... args) {
    (std::cerr << ... << std::forward<Args>(args)) << std::endl;
}

// string
constexpr auto hello = [](const std::string& name) { return "Hello " + name; };

// int
constexpr auto increment = [](int x) { return x + 1; };
constexpr auto int_to_string = [](int x) { return std::to_string(x); };
constexpr auto make_multiplier = [](int x) {
    return [x](int y) { return x * y; };
};
constexpr auto square = [](int x) { return x * x; };
constexpr auto triple = [](int x) { return x * 3; };

}  // namespace fp::test

#endif  // FP_TEST_INCLUDE__SHORTS_H_
