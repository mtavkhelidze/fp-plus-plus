#include <fp/fp.h>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include "shorts.h"

using namespace fp;

TEST(Option_Some, with_references) {
    int just_int = 42;
    int& non_const_ref = just_int;
    auto o_non_const_ref = Some(non_const_ref);
    static_assert(std::is_same_v<decltype(o_non_const_ref), Option<const int>>);

    const int const_int = 42;
    const int& const_ref = const_int;
    auto o_const_ref = Some(const_ref);
    static_assert(std::is_same_v<decltype(o_const_ref), Option<const int>>);
}

TEST(Option_Some, with_callables) {
    std::function<int(int)> func_obj = [](int x) { return x * 2; };
    auto o_func = Some(func_obj);
    static_assert(
      std::is_same_v<decltype(o_func), Option<const std::function<int(int)>>>,
      "Failed with std::function"
    );

    auto lambda = [](int x) { return x + 1; };
    auto o_lambda = Some(lambda);
    static_assert(
      std::is_same_v<decltype(o_lambda), Option<const decltype(lambda)>>,
      "Failed with lambda"
    );

    int (*func_ptr)(int) = [](int x) { return x * 3; };
    auto o_func_ptr = Some(func_ptr);
    static_assert(
      std::is_same_v<decltype(o_func_ptr), Option<int (*const)(int)>>,
      "Failed with function pointer"
    );
}

TEST(Option_Some, with_void_and_nullptr) {
    void* void_null = nullptr;
    auto o = Some(void_null);
    static_assert(std::is_same_v<decltype(o), Option<void* const>>);

    const void* const_void_null = nullptr;
    auto const_o = Some(const_void_null);
    static_assert(std::is_same_v<decltype(const_o), Option<const void* const>>);
}

TEST(Option_Some, with_pointer) {
    const int const_int = 42;
    const int* const_int_ptr = &const_int;

    auto const_o = Some(const_int_ptr);
    static_assert(std::is_same_v<decltype(const_o), Option<const int* const>>);

    int just_int = 42;
    int* int_ptr = &just_int;

    auto o = Some(int_ptr);
    static_assert(std::is_same_v<decltype(o), Option<int* const>>);
}

TEST(Option_Some, with_const_integral) {
    const int const_int = 42;

    auto o = Some(const_int);
    static_assert(std::is_same_v<decltype(o), Option<const int>>);

    const auto const_o = Some(const_int);
    static_assert(std::is_same_v<decltype(const_o), const Option<const int>>);
}

TEST(Option_Some, with_plain_integral) {
    int just_int = 42;

    auto o = Some(just_int);
    static_assert(std::is_same_v<decltype(o), Option<const int>>);

    const auto const_o = Some(just_int);
    static_assert(std::is_same_v<decltype(const_o), const Option<const int>>);
}
