#include <fp/fp.h>
#include <gtest/gtest.h>

using ::testing::Test;

using namespace fp::traits::eq;

// Eq concept implementations
namespace eq_char {
struct Char {
    char c;
    [[nodiscard]] auto equals(const Char& other) const -> bool {
        return this->c == other.c;
    }
};

};  // namespace eq_char

TEST(Eq_Char, satisfies_eq_concept) {
    static_assert(Eq<eq_char::Char>, "Char does not satisfy the Eq concept");
};

TEST(Eq_Operator_Equals, works) {
    const eq_char::Char a{.c = 'a'};
    const eq_char::Char b{.c = 'a'};
    const eq_char::Char c{.c = 'c'};

    EXPECT_EQ((b == a), (a == b));
    EXPECT_EQ((a != b), !(a == b));
    EXPECT_EQ((a == b), !(a != b));

    EXPECT_TRUE(a == a);
    EXPECT_FALSE(a != a);

    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a == c);

    EXPECT_TRUE(a != c);
    EXPECT_FALSE(a != b);
}
