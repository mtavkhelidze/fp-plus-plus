#include <fp/fp.h>
#include <gtest/gtest.h>

using ::testing::Test;

using namespace fp::traits;
using namespace fp::syntax::monoid;

namespace str {

struct String {
    std::string s;
    static const String empty() { return String{""}; }
};

auto combine(const String& a, const String& b) -> const String {
    return String{a.s + b.s};
}
}  // namespace str

TEST(Monoid_String, satisfies_monoid_concept) {
    static_assert(
      Monoid<str::String>, "String does not satisfy the Monoid concept"
    );
}

class Monoid_Operator_Spaceship : public Test {
  public:
    str::String a{"a"};
    str::String b{"b"};
    str::String c{"c"};
};

TEST_F(Monoid_Operator_Spaceship, calls_static_combine) {
    auto result = a <=> b;
    EXPECT_EQ(result.s, "ab");
}

TEST_F(Monoid_Operator_Spaceship, works_with_empty) {
    auto result = a <=> str::String::empty() <=> c;
    EXPECT_EQ(result.s, "ac");
}

TEST_F(Monoid_Operator_Spaceship, works_when_chained) {
    auto result = a <=> b <=> c;
    EXPECT_EQ(result.s, "abc");
}

TEST_F(Monoid_Operator_Spaceship, respects_associativity) {
    auto result = a <=> (c <=> b);
    EXPECT_EQ(result.s, "acb");
}
