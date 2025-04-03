#include <gtest/gtest.h>
//
#include <gmock/gmock.h>

#include <fp/fp>

using ::testing::_;
using ::testing::Test;

using namespace fp;

// Eq concept
struct EqInstance {
    char c;
    MOCK_CONST_METHOD0(called, bool());
    inline static const bool equals(const EqInstance& a, const EqInstance& b) {
        a.called();
        return a.c == b.c;
    }
};

TEST(EqInstance, satisfies_eq_concept) {
    static_assert(Eq<EqInstance>, "EqInstance does not satisfy the Eq concept");
};

TEST(Eq_Operator_Equals, works) {
    EqInstance a{'a'};
    EqInstance a1{'a'};
    EqInstance b{'b'};

    EXPECT_CALL(a, called()).Times(2);
    EXPECT_FALSE(a == b);
    EXPECT_TRUE(a == a1);
}

TEST(Eq_Operator_Not_Equals, works) {
    EqInstance a{'a'};
    EqInstance a1{'a'};
    EqInstance b{'b'};

    EXPECT_CALL(a, called()).Times(2);
    EXPECT_TRUE(a != b);
    EXPECT_FALSE(a != a1);
}
