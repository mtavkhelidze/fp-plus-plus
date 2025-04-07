#include <fp/fp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using namespace fp;

// NOLINTBEGIN: literal

TEST(Box_GetOrNull, literal_string) {
    auto box = Box("0xdeadbeef");
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
    EXPECT_EQ(*box.getOrNull(), "0xdeadbeef");
}
// NOLINTEND
