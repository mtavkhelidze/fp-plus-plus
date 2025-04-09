#include <fp/fp.h>
#include <gtest/gtest.h>

#include <string>
#include <tuple>
#include <type_traits>

namespace fp {
TEST(DISABLE_Box_GetOrNull, literal_array) {
    auto box = Box(1, 2, 3);
    auto [a, b, c] =
      std::tuple{box.getOrNull()[0], box.getOrNull()[1], box.getOrNull()[2]};
    EXPECT_EQ(a, 1);
    EXPECT_EQ(b, 2);
    EXPECT_EQ(c, 3);
};

TEST(DISABLE_Box_GetOrNull, literal_string) {
    auto box = Box("0xdeadbeef");
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
    EXPECT_EQ(*box.getOrNull(), "0xdeadbeef");
};

TEST(DISABLE_Box_GetOrNull, array_pointer) {
    auto box = Box(new std::string[2]{"hello", "world"});
    static_assert(std::is_same_v<Box<std::string *>, decltype(box)>);
    auto *boxed = *box.getOrNull();
    auto [a, b] = std::tuple{boxed[0], boxed[1]};
    EXPECT_EQ(a, "hello");
    EXPECT_EQ(b, "world");
};

}  // namespace fp
