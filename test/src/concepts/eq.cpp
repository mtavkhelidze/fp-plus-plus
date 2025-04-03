#include <gtest/gtest.h>
// do not sort
#include <gmock/gmock.h>

#include <fp/fp>

using ::testing::_;
using ::testing::Return;
using namespace fp;

// Eq concept
class TestEq {
  public:
    MOCK_METHOD(bool, equals, (const TestEq&), (const));
};

TEST(Syntax_Eq_Operator_Equals, calls_equals) {
    TestEq a, b;

    EXPECT_CALL(a, equals(_)).WillOnce(Return(true));
    EXPECT_TRUE(a == b);

    EXPECT_CALL(a, equals(_)).WillOnce(Return(false));
    EXPECT_FALSE(a == b);
}

TEST(Syntax_Eq_Operator_Not_Equals, calls_equals) {
    TestEq a, b;

    EXPECT_CALL(a, equals(_)).WillOnce(Return(true));
    EXPECT_FALSE(a != b);

    EXPECT_CALL(a, equals(_)).WillOnce(Return(false));
    EXPECT_TRUE(a != b);
}
