// NOLINTBEGIN(misc-use-internal-linkage,hicpp-named-parameter,readability-named-parameter,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,modernize-use-trailing-return-type,bugprone-unused-local-non-trivial-variable)

#include <fp/fp.h>
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>

using ::testing::Test;

namespace fp {

TEST(Box_Construction, can_hold_rvalue) {
    auto box = Box(42);
    static_assert(std::is_same_v<Box<int>, decltype(box)>);
}

TEST(Box_Construction, can_hold_raw) {
    int x[] = {1, 2};
    auto box = Box(x);
    static_assert(std::is_same_v<Box<int*>, decltype(box)>);
}

TEST(Box_Construction, can_hold_lvalue) {
    const int x = 42;
    const auto& y = x;
    auto box = Box(y);
    static_assert(std::is_same_v<Box<int>, decltype(box)>);
}

TEST(Box_Construction, can_hold_string_literal) {
    auto box = Box("hello");
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
}

TEST(Box_Construction, can_take_shared_ptr) {
    auto ptr = std::make_shared<std::string>("hello");
    auto box = Box(ptr);
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
}

TEST(Box_Construction, can_take_unique_ptr) {
    auto ptr = std::make_unique<const char*>("hello");
    auto box = Box(ptr);
    static_assert(std::is_same_v<Box<const char*>, decltype(box)>);
}

// NOLINTBEGIN(cert-err58-cpp,cppcoreguidelines-owning-memory)
TEST(Box_Construction, can_hold_nullptr) {
    auto box = Box(nullptr);
    static_assert(std::is_same_v<Box<nullptr_t>, decltype(box)>);
}
// NOLINTEND(cert-err58-cpp,cppcoreguidelines-owning-memory)

TEST(Box_Construction, literal_array) {
    auto box = Box{1, 2, 3};
    static_assert(std::is_same_v<Box<int, int, int>, decltype(box)>);
}

TEST(Box_Construction, can_take_std_array) {
    std::array<int, 3> xs = {1, 2, 3};
    auto box = Box(&xs);
    static_assert(std::is_same_v<Box<std::array<int, 3>*>, decltype(box)>);
}

TEST(Box_Construction, nullptr_value) {
    auto box = Box(nullptr);
    static_assert(std::is_same_v<Box<nullptr_t>, decltype(box)>);
}

TEST(Box_Construction, move_only) {
    struct MoveOnly {
        MoveOnly() = default;
        MoveOnly(MoveOnly&&) = default;
        MoveOnly(const MoveOnly&) = delete;
    };
    auto box1 = Box(MoveOnly{});
    static_assert(std::is_same_v<Box<MoveOnly>, decltype(box1)>);

    auto box2 = Box{std::make_unique<int>(5)};
    static_assert(std::is_same_v<Box<std::unique_ptr<int>>, decltype(box2)>);
}
}  // namespace fp

// NOLINTEND(misc-use-internal-linkage,hicpp-named-parameter,readability-named-parameter,cppcoreguidelines-avoid-magic-numbers,readability-magic-numbers,modernize-use-trailing-return-type,bugprone-unused-local-non-trivial-variable)
