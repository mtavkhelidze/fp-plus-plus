#include <gtest/gtest.h>

#include <fp/fp>

using ::testing::Test;

using namespace fp;

struct MonoidInstance {
    std::string label;
    static const MonoidInstance combine(
      const MonoidInstance& a, const MonoidInstance& b
    ) {
        return MonoidInstance{a.label + b.label};
    };
    static const MonoidInstance empty() { return MonoidInstance{""}; }
};

TEST(MonoidInstance, satisfies_monoid_concept) {
    static_assert(
      Monoid<MonoidInstance>,
      "MonoidInstance does not satisfy the Monoid concept"
    );
}

class Monoid_Operator_Spaceship : public Test {
  public:
    MonoidInstance a{"a"};
    MonoidInstance b{"b"};
    MonoidInstance c{"c"};
};

TEST_F(Monoid_Operator_Spaceship, calls_static_combine) {
    auto result = a <=> b;
    EXPECT_EQ(result.label, "ab");
}

TEST_F(Monoid_Operator_Spaceship, works_when_chained) {
    auto result = a <=> b <=> c;
    EXPECT_EQ(result.label, "abc");
}

TEST_F(Monoid_Operator_Spaceship, respects_associativity) {
    auto result = a <=> (c <=> b);
    EXPECT_EQ(result.label, "acb");
}
