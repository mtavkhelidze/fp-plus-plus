#include <gtest/gtest.h>

#include <fp/fp>
#include <functional>

using namespace fp;

TEST(Function, FunctionComposition) {
    auto addFive = [](const int &x) -> int { return x + 5; };
    auto multByThree = [](const int &x) -> int { return x * 3; };
    auto toString = [](const int &x) -> std::string {
        return std::to_string(x);
    };

    // const auto one = 10 << addFive << multByThree;
    // ASSERT_EQ(one, 45) << "Function composition failed";

    auto x = 10 << multByThree << addFive << addFive;
    ASSERT_EQ(x, 40) << "Function composition failed";

    auto y = "Misha" <<
             [](const std::string &s) -> std::string { return "Hello, " + s; };
    ASSERT_EQ(y, "Hello, Misha") << "Function composition failed";
}

// TEST(Function, ComplexArgumentComposition) {
//     auto linearTransform =
//       [](const std::pair<int, int> &p) -> std::pair<int, int> {
//         return {p.first * 2 + 1, p.second * 3 - 1};
//     };

//     auto length = [](const std::pair<int, int> &p) -> double {
//         return std::sqrt(p.first * p.first + p.second * p.second);
//     };

//     const auto transformationAndLength = linearTransform >>= length;

//     std::pair<int, int> input = {3, 4};
//     double result = transformationAndLength(input);

//     ASSERT_NEAR(
//       result,
//       std::sqrt((3 * 2 + 1) * (3 * 2 + 1) + (4 * 3 - 1) * (4 * 3 - 1)),
//       1e-6
//     );
// }
