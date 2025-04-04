#include <fp/fp.h>
#include <gtest/gtest.h>

#include "shorts.h"

using namespace fp;

// TEST(Option, is_Eq) { static_assert(Eq<Option<int>>, "Option is not Eq"); }

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
