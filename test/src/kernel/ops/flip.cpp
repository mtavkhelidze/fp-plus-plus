#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::test;

// flip(f)(b)(a) == f(a)(b)
TEST(Kernel_Ops_Flip, basic_law) {
    auto f = [](int a) -> auto {
        return [a](const String& b) -> String { return b + std::to_string(a); };
    };
    auto flipped = flip(f);
    EXPECT_EQ(f(42)(String("x")), flipped(String("x"))(42));
}

// flip(flip(f))(a)(b) == f(a)(b)
TEST(Kernel_Ops_Flip, double_flip_is_identity) {
    auto f = [](int a) -> auto { return [a](int b) -> int { return a - b; }; };
    auto ff = flip(flip(f));
    EXPECT_EQ(f(10)(3), ff(10)(3));
}

// type change A -> B -> C where all different
TEST(Kernel_Ops_Flip, type_change) {
    auto f = [](int a) -> auto {
        return [a](const String& b) -> std::size_t { return b.size() + a; };
    };
    auto flipped = flip(f);
    EXPECT_EQ(flipped(String("hello"))(2), f(2)(String("hello")));
}

TEST(Kernel_Ops_Flip, flipped_always_is_identity) {
    auto flipped_always = flip(always);
    const auto result = flipped_always(241);
    EXPECT_EQ(result("forty-two"), "forty-two");
}

// TEST(Kernel_Ops_Flip, flipped_map2) {
//     auto fa = pure<StructApplicative>(12);
//     auto fb = pure<StructApplicative>(21);
//     auto fn1 = map2(always(identity));
//     auto fn2 = fn1(fa);
//     auto r = fn2(fb);
//     EXPECT_EQ(r.value(), 21);
// }
