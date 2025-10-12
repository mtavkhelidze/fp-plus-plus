#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>
#include <type_traits>  // Added for type checks

using namespace fp;

// NOLINTBEGIN(private-member-variables-in-classes)
// NOLINTBEGIN(misc-non-private-member-variables-in-classes)
// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)
// NOLINTBEGIN(readability-magic-numbers)

struct MyStruct {
    int value;

    // Constructor to avoid aggregate initialization warnings/issues
    explicit MyStruct(const int& v) : value(v) {}
};

// --- Basic Value Tests ---

TEST(Prelude_Identity, is_constexpr) {
    constexpr int x = 10;
    constexpr int y = identity(x);
    static_assert(y == 10, "identity should be constexpr");
}

TEST(Prelude_Identity, returns_same_value_for_int) {
    int x = 5;
    EXPECT_EQ(identity(x), x);
}

TEST(Prelude_Identity, returns_same_value_for_string) {
    std::string s = "hello";
    EXPECT_EQ(identity(s), s);
}

TEST(Prelude_Identity, returns_a_copy_for_lvalue) {
    int x = 50;
    auto result = identity(x);
    x = 100;
    EXPECT_EQ(result, 50);
}

// --- Reference and Constness Tests ---

TEST(Prelude_Identity, works_with_const_references) {
    const int x = 10;
    EXPECT_EQ(identity(x), x);
    static_assert(
      std::is_same_v<decltype(identity(x)), int>,
      "identity(const T&) should return T by value"
    );
}

TEST(Prelude_Identity, works_with_rvalue_references_and_moves) {
    std::string original_value = "rvalue_test";
    std::string s = identity(std::move(original_value));

    EXPECT_EQ(s, "rvalue_test");
    EXPECT_TRUE(original_value.empty());
}

TEST(Prelude_Identity, works_with_rvalue_literals) {
    std::string s = identity(std::string("literal_test"));
    EXPECT_EQ(s, "literal_test");
}

TEST(Prelude_Identity, works_with_custom_struct) {
    MyStruct s(42);

    EXPECT_EQ(identity(s).value, s.value);
    static_assert(
      std::is_same_v<decltype(identity(s)), MyStruct>,
      "identity(T) should return T by value"
    );
}

// NOLINTEND(readability-magic-numbers)
// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
// NOLINTEND(misc-non-private-member-variables-in-classes)
// NOLINTEND(private-member-variables-in-classes)
