#include <fp/fp.h>
#include <gmock/gmock.h>

using ::testing::Test;

using namespace fp::traits::semigroup;
using namespace fp::operators::semigroup;

namespace str {

struct String {
    std::string s;
};

inline constexpr auto combine(const String& a, const String& b) -> String {
    return String{a.s + " combine " + b.s};
}
}  // namespace str

TEST(Semigroup_String, satisfies_semigroup_concept) {
    static_assert(Semigroup<str::String>, "String is not a semigroup");
}

class Semigroup_Operator_Plus : public Test {
  public:
    str::String a{"a"};
    str::String b{"b"};
    str::String c{"c"};
};

TEST_F(Semigroup_Operator_Plus, calls_combine) {
    auto result = a + b;
    EXPECT_EQ(result.s, "a combine b");
}

TEST_F(Semigroup_Operator_Plus, satisfies_associativity) {
    auto result1 = (a + b) + c;
    auto result2 = a + (b + c);
    EXPECT_EQ(result1.s, result2.s);
}
