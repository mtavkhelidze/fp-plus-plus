#include <exception>
// keep ^^^ on top

#include <fp/fp.h>
#include <gtest/gtest.h>
#include <rapidcheck.h>
#include <rapidcheck/gtest.h>

#include "shorts.h"

using namespace fp;

// TEST(Option, reference_types) {
//     int value = 10;
//     Option<int&> opt = Some(value);
//     EXPECT_EQ(opt.getOrElse(value), 10);
// }

TEST(Option_None, get_or_else_default_value) {
    Option<int> none = None<int>();
    EXPECT_EQ(none.getOrElse(42), 42);  // Should return default value 42
}
TEST(Option, multiple_some_values) {
    Option<int> opt1 = Some(42);
    Option<int> opt2 = Some(100);
    EXPECT_EQ(opt1.getOrElse(0), 42);
    EXPECT_EQ(opt2.getOrElse(0), 100);
}

TEST(Option, non_copyable_type) {
    auto ptr = std::make_unique<int>(42);
    Option<std::unique_ptr<int>> opt =
      Some(std::move(ptr));  // Move the unique_ptr
    EXPECT_EQ(*opt.getOrElse(std::make_unique<int>(0)), 42);
}

TEST(Option, nested_option) {
    Option<Option<int>> nested = Some(Some(42));
    EXPECT_EQ(nested.getOrElse(None<int>()).getOrElse(0), 42);
}

TEST(Option, holds_types_properly) {
    const char* name = "name";
    Option<const char*> char_some = Some(name);
    EXPECT_EQ(char_some.type_name(), "T*");

    Option<Nothing> none = None();
    EXPECT_EQ(none.type_name(), "Nothing");

    std::string lvalue = "lvalue_test";
    auto opt1 = Some<std::string&>(lvalue);
    EXPECT_EQ(opt1.type_name(), "T&");

    auto opt2 = Some(std::string("rvalue_test"));
    EXPECT_EQ(opt2.type_name(), "T");
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
