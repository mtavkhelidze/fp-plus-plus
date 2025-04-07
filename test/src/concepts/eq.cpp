#include <fp/fp.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

using ::testing::_;
using ::testing::Test;

using namespace fp;

// Eq concept
struct EqInstance {
    char c;
    MOCK_CONST_METHOD0(called, bool());
    static auto equals(const EqInstance& a, const EqInstance& b) -> bool {
        a.called();
        return a.c == b.c;
    }
};

TEST(EqInstance, satisfies_eq_concept) {
    static_assert(Eq<EqInstance>, "EqInstance does not satisfy the Eq concept");
};

TEST(Eq_Operator_Equals, works) {
    const EqInstance a{.c = 'a'};
    const EqInstance a1{.c = 'a'};
    const EqInstance b{.c = 'b'};

    EXPECT_CALL(a, called()).Times(2);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a == a1);
}

TEST(Eq_Operator_Not_Equals, works) {
    const EqInstance a{.c = 'a'};
    const EqInstance a1{.c = 'a'};
    const EqInstance b{.c = 'b'};

    EXPECT_CALL(a, called()).Times(2);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a1);
}
