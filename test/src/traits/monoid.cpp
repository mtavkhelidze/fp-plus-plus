#include <fp/fp.h>
#include <gtest/gtest.h>

using ::testing::Test;

using namespace fp::traits::monoid;
using namespace fp::syntax::monoid;

namespace str {

struct String {
    std::string s;
    static String empty() { return String{""}; }
};

inline constexpr auto combine(const String& a, const String& b) -> String {
    return String(a.s + b.s);
}
}  // namespace str

TEST(Monoid_String, satisfies_monoid_concept) {
    static_assert(
      Monoid<str::String>, "String does not satisfy the Monoid concept"
    );
}

class Monoid_Operator_Plus : public Test {
  public:
    str::String a{"a"};
    str::String b{"b"};
    str::String c{"c"};
};

TEST_F(Monoid_Operator_Plus, combines_two_values) {
    auto result = a + b;
    EXPECT_EQ(result.s, "ab");
}

TEST_F(Monoid_Operator_Plus, respects_left_identity) {
    auto result = str::String::empty() + a;
    EXPECT_EQ(result.s, a.s);
}

TEST_F(Monoid_Operator_Plus, respects_right_identity) {
    auto result = a + str::String::empty();
    EXPECT_EQ(result.s, a.s);
}
