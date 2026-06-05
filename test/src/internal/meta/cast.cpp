/**
 * Copyright 2026 Misha Tavkhelidze <misha.tavkhelidze@gmail.com>.
 * SPDX-License-Identifier: MIT
 */

#include <fp/fp.h>
#include <gtest/gtest.h>

#include <functional>
#include <initializer_list>
#include <memory>
#include <type_traits>

using namespace fp;
// NOLINTBEGIN(hicpp-avoid-c-arrays)

TEST(fp_cast, tuple_normalisation) {
    // each element normalised independently
    static_assert(std::is_same_v<
                  fp::cast<Tuple<const char*, int, std::initializer_list<int>>>,
                  Tuple<String, int, Vector<int>>>);

    // nested — cast recurses into inner tuple
    static_assert(std::is_same_v<
                  fp::cast<Tuple<const char*, Tuple<const char*, int>>>,
                  Tuple<String, Tuple<String, int>>>);

    // empty tuple
    static_assert(std::is_same_v<fp::cast<Tuple<>>, Tuple<>>);
}

TEST(fp_cast, c_array_becomes_vector) {
    static_assert(std::is_same_v<fp::cast<int[3]>, Vector<int>>);
    static_assert(std::is_same_v<fp::cast<double[10]>, Vector<double>>);
}

TEST(fp_cast, char_array_becomes_string) {
    static_assert(std::is_same_v<fp::cast<char[5]>, String>);
}
// NOLINTEND(hicpp-avoid-c-arrays)
TEST(fp_cast, unique_ptr_becomes_is_taken_as_is) {
    static_assert(
      std::is_same_v<fp::cast<std::unique_ptr<int>>, std::unique_ptr<int>>
    );
}

TEST(fp_cast, type_int) {  //
    static_assert(std::is_same_v<fp::cast<int>, int>);
}

TEST(fp_cast, strips_reference) {
    static_assert(std::is_same_v<fp::cast<int&>, int>);
    static_assert(std::is_same_v<fp::cast<int&&>, int>);
    static_assert(std::is_same_v<fp::cast<const int&>, int>);
}

TEST(fp_cast, strips_const) {
    static_assert(std::is_same_v<fp::cast<const int>, int>);
    static_assert(std::is_same_v<fp::cast<const String>, String>);
}

TEST(fp_cast, pointer_stays_pointer) {
    static_assert(std::is_same_v<fp::cast<int*>, int*>);
    static_assert(std::is_same_v<fp::cast<const int*>, const int*>);
}

TEST(fp_cast, string_literal_becomes_string) {
    static_assert(std::is_same_v<fp::cast<const char*>, String>);
}

TEST(fp_cast, complex_type) {
    static_assert(std::is_same_v<fp::cast<Vector<int>>, Vector<int>>);
}

TEST(fp_cast, function_pointer) {
    using FuncType = int (*)(int);
    static_assert(std::is_same_v<fp::cast<FuncType>, FuncType>);
}

TEST(fp_cast, lambda) {
    auto lambda = []() { return 42; };
    static_assert(std::is_same_v<fp::cast<decltype(lambda)>, decltype(lambda)>);
}

TEST(fp_cast, std_function) {
    static_assert(
      std::is_same_v<fp::cast<std::function<int(int)>>, std::function<int(int)>>
    );
}

TEST(fp_cast, shared_ptr_becomes_inner_type) {
    static_assert(std::is_same_v<fp::cast<std::shared_ptr<int>>, int>);
}
