#include <gtest/gtest.h>

#include "fp/fp.h"

namespace fp {
TEST(Box_getOrNull, default_typed_box) {
    Box<int> box;
    EXPECT_EQ(box.getOrNull(), nullptr);
}
TEST(Box_getOrNull, default_box) {
    Box<Nothing> box = Box();
    EXPECT_EQ(box.getOrNull(), nullptr);
}

TEST(Box_getOrNull, empty_box) {
    auto emptyBox = Box();
    EXPECT_EQ(emptyBox.getOrNull(), nullptr);
}

TEST(Box_getOrNull, with_value) {
    int value = 42;
    Box<int> box(value);
    auto result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, value);
}

TEST(Box_getOrNull, with_shared_pointer) {
    std::shared_ptr<int> sharedPtr = std::make_shared<int>(42);
    auto box = Box(sharedPtr);
    auto result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(*result, *sharedPtr);
}

TEST(Box_getOrNull, with_raw_pointer) {
    int value = 42;
    Box<int*> box(&value);
    auto result = box.getOrNull();
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(**result, value);
}

TEST(Box_getOrNull, with_nullptr) {
    Box<int*> box(nullptr);
    EXPECT_EQ(*box.getOrNull(), nullptr);
}
}  // namespace fp
