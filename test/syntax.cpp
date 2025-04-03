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

// Monoid concept
class TestMonoid {
  public:
    const TestMonoid combine(const TestMonoid& other) const {
        return TestMonoid{};
    }
    static const TestMonoid empty() { return TestMonoid(); }
    // ^^^ Monoid concept
    //
    // MOCK_METHOD(const TestMonoid, combine, (const TestMonoid&), (const));
    // TestMonoid(const TestMonoid&) {};
    // TestMonoid() {}
    // TestMonoid(TestMonoid&& other) noexcept {}
};

TEST(Syntax_Monoid_Operator_Addition, calls_combine) {
    auto a = TestMonoid();
    auto b = TestMonoid();

    // EXPECT_CALL(a, combine(_)).WillOnce(Return(expected));
    auto actual = a + b;

    // EXPECT_EQ(ectual, expected);
}

// TEST(SyntaxTest, MonoidPlusEqualsCallsCombine) {
//     TestMonoid a, b, result;

//     EXPECT_CALL(a, combine(b)).WillOnce(Return(result));
//     a += b;
//     EXPECT_EQ(a, result);
// }
