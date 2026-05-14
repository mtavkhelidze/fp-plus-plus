#include <fp/fp.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

#include <string>

using namespace fp;
using namespace fp::laws;

static auto intToStr = [](const int& d) -> String {
    return std::to_string(d) + "1";
};
static auto intSquared = [](const int& x) -> int { return x * x; };
static auto toTuple = [](const int& d) {
    return [&](const String& s) -> Tuple<int, String> { return Tuple{d, s}; };
};

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, ledft_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::left_identity(intToStr, a));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, right_identity, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::right_identity(intSquared, a));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, associativity, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::associativity(toTuple(42), intToStr, intSquared, i));
}

RC_GTEST_PROP(Kernel_Ops_Compose_Laws, variadic_consistency, ()) {
    auto i = *rc::gen::arbitrary<int>();
    RC_ASSERT(ComposeLaws::variadic(toTuple(42), intToStr, intSquared, i));
}
