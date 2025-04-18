#include <fp/__internal/box.h>
#include <gtest/gtest.h>

#include <memory>

using namespace fp;
using namespace fp::__internal::box;

TEST(Box_getOrNull, default_typed_box) {
    Box<int> const box;
    EXPECT_EQ(box.getOrNull(), nullptr);
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
    int const value = 42;
    Box<int> const box(value);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, value);
}

TEST(Box_getOrNull, with_shared_pointer) {
    std::shared_ptr<int> const sharedPtr = std::make_shared<int>(42);
    auto box = Box(sharedPtr);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, *sharedPtr);
}

TEST(Box_getOrNull, with_raw_pointer) {
    int value = 42;  // NOLINT:(cppcoreguidelines-avoid-magic-numbers)
    Box<int *> const box(&value);
    const auto *result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(**result, value);
}

TEST(Box_getOrNull, with_nullptr) {
    Box<int *> const box(nullptr);
    EXPECT_EQ(*box.getOrNull(), nullptr);
}
