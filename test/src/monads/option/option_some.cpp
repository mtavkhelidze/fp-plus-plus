#include <exception>
// keep ^^^ on top

#include <fp/fp.h>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include "shorts.h"

using namespace fp;

TEST(Option_Some, creates_some_from_lvalue_reference) {
    std::string lvalue = "lvalue_test";
    auto opt = Some<std::string&>(lvalue);
    // static_assert(std::is_same_v<decltype(opt), Option<std::string>>);
    // EXPECT_EQ(opt.getOrElse("lvalue_value"), lvalue);
}

RC_GTEST_PROP(
  Option_Some, creates_some_from_rvalue, (const std::string& input)
) {
    auto opt = Some(std::string(input));
    static_assert(std::is_same_v<decltype(opt), Option<std::string>>);
    RC_ASSERT(opt.getOrElse("default_value") == input);
}

TEST(Option_None, returns_correct_type) {
    auto a = None();
    static_assert(std::is_same_v<decltype(a), Option<Nothing>>);

    auto b = None<int>();
    static_assert(std::is_same_v<decltype(b), Option<int>>);
}
