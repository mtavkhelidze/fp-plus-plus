#include <gtest/gtest.h>
// do not sort
#include <gmock/gmock.h>

#include <fp/fp>

using ::testing::_;
using ::testing::Return;
using namespace fp;

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
