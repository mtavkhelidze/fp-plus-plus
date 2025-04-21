#include <fp/internal/box.h>
#include <gtest/gtest.h>

#include <memory>
#include <utility>

using namespace fp;
using namespace fp::internal::box;

inline constexpr int forty_two = 42;

TEST(Box_getOrNull, default_typed_box) {
    Box<int> const box;
    EXPECT_EQ(box.getOrNull(), nullptr);
}

TEST(Box_getOrNull, move_semantics) {
    Box<int> box1(forty_two);
    const Box<int> box2(std::move(box1));
    EXPECT_NE(box2.getOrNull(), nullptr);
    EXPECT_EQ(*box2.getOrNull(), forty_two);
}

TEST(Box_getOrNull, raw_pointer_stack_warning_documentation_only) {
    // NOTE: This is a documentation-only test.
    // Do NOT use pointers to stack memory with Box.
    // Box assumes ownership via shared_ptr which is unsafe for stack-allocated memory.
    SUCCEED();
}

struct Complex {
    int a; // NOLINT
    std::string b; // NOLINT

    auto operator==(const Complex& other) const -> bool {
        return a == other.a && b == other.b;
    }
} __attribute__((aligned(32))); // NOLINT

TEST(Box_getOrNull, complex_type) {
    const Complex c{10, "hello"};
    const Box<Complex> box(c);
    ASSERT_NE(box.getOrNull(), nullptr);
    EXPECT_EQ(*box.getOrNull(), c);
}
TEST(Box_getOrNull, default_box) {
    Box<Nothing> const box = Box();
    EXPECT_EQ(box.getOrNull(), nullptr);
}

TEST(Box_getOrNull, empty_box) {
    auto emptyBox = Box();
    EXPECT_EQ(emptyBox.getOrNull(), nullptr);
}

TEST(Box_getOrNull, with_value) {
    int const value = forty_two; // NOLINT
    Box<int> const box(value);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, value);
}

TEST(Box_getOrNull, with_shared_pointer) {
    std::shared_ptr<int> const sharedPtr = std::make_shared<int>(forty_two);
    auto box = Box(sharedPtr);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, *sharedPtr);
}

TEST(Box_getOrNull, with_raw_pointer) {
    int value = forty_two;  // NOLINT:(cppcoreguidelines-avoid-magic-numbers)
    Box<int *> const box(&value);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(**result, value);
}

TEST(Box_getOrNull, with_nullptr) {
    Box<int *> const box(nullptr);
    EXPECT_EQ(*box.getOrNull(), nullptr);
}
