#include <fp/internal/box.h>
#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <deque>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <type_traits>
#include <unordered_set>
#include <utility>
#include <vector>
#include <variant>
#include <functional>
#include <optional>
#include <set>
#include <unordered_map>


// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, hicpp-no-array-decay)

using ::testing::Test;
using namespace fp;
using namespace fp::internal::box;

TEST(Box_Construction, box_with_nothing_in_it) {
    // Nothing type (std::monostate)
    [[maybe_unused]] Box const box;
    static_assert(std::is_same_v<Box<Nothing>, std::decay_t<decltype(box)>>);
}

TEST(Box_Construction, array_non_pointer) {
    // array (non-pointer)
    int arr[3] = {1, 2, 3};                                   // NOLINT
    auto box = Box(arr);                                      // NOLINT
    static_assert(std::is_same_v<Box<int*>, decltype(box)>);  // NOLINT
}
TEST(Box_Construction, array_of_pointers) {
    // array of pointers
    int a = 1, b = 2, c = 3;    // NOLINT
    int* arr[] = {&a, &b, &c};  // NOLINT
    auto box = Box(arr);        // NOLINT
    static_assert(std::is_same_v<Box<int**>, decltype(box)>);
}

TEST(Box_Construction, const_lvalue_ref) {
    // const lvalue ref
    const int x = 42;
    [[maybe_unused]] auto box = Box(x);
    static_assert(std::is_same_v<Box<int>, decltype(box)>);
}

TEST(Box_Construction, copy_only_type) {
    // copy-only type
    struct CopyOnly {  // NOLINT
        CopyOnly() = default;
        CopyOnly(const CopyOnly&) = default;
        CopyOnly(CopyOnly&&) = delete;
    };
    [[maybe_unused]] auto box = Box(CopyOnly{});
    static_assert(std::is_same_v<Box<CopyOnly>, decltype(box)>);
}

TEST(Box_Construction, function_pointer) {
    // function pointer
    using FuncType = void (*)();
    FuncType func = nullptr;
    [[maybe_unused]] auto box = Box(func);
    static_assert(std::is_same_v<Box<FuncType>, decltype(box)>);
}

TEST(Box_Construction, lambda_expression) {
    // lambda expression
    auto lambda = []() { return 42; };
    [[maybe_unused]] auto box = Box(lambda);
    static_assert(std::is_same_v<Box<decltype(lambda)>, decltype(box)>);
}

TEST(Box_Construction, literal_parameter_pack) {
    // literal parameter pack
    [[maybe_unused]] auto box = Box{1, 2, 3};
    static_assert(std::is_same_v<Box<int, int, int>, decltype(box)>);
}

TEST(Box_Construction, move_only_rvalue_and_smart_ptr) {
    // move-only type and rvalue move-only smart pointer
    struct MoveOnly {
        MoveOnly() = default;
        MoveOnly(MoveOnly&&) = default;
        MoveOnly(const MoveOnly&) = delete;
        ~MoveOnly() = default;
    };
    [[maybe_unused]] auto box1 = Box(MoveOnly{});
    static_assert(std::is_same_v<Box<MoveOnly>, decltype(box1)>);

    [[maybe_unused]] auto box2 = Box{std::make_unique<int>(5)};
    static_assert(std::is_same_v<Box<std::unique_ptr<int>>, decltype(box2)>);
}

TEST(Box_Construction, nullptr_type) {
    // nullptr_t
    [[maybe_unused]] auto box = Box(nullptr);
    static_assert(std::is_same_v<Box<Nothing>, decltype(box)>);
}

TEST(Box_Construction, rvalue) {
    // rvalue
    [[maybe_unused]] auto box1 = Box(42);
    static_assert(std::is_same_v<Box<int>, decltype(box1)>);

    int const x = 42;
    [[maybe_unused]] auto box2 = Box(x);
    static_assert(std::is_same_v<Box<int>, decltype(box2)>);
}

TEST(Box_Construction, shared_ptr) {
    // shared_ptr and rvalue shared_ptr
    auto ptr = std::make_shared<std::string>("hello");
    [[maybe_unused]] auto box1 = Box(ptr);
    static_assert(std::is_same_v<Box<std::string>, decltype(box1)>);

    struct MyType {};
    [[maybe_unused]] auto box2 = Box(std::make_shared<MyType>());
    static_assert(std::is_same_v<Box<MyType>, decltype(box2)>);
}

TEST(Box_Construction, std_array) {
    // std::array*
    std::array<int, 3> xs = {1, 2, 3};
    [[maybe_unused]] auto box = Box(xs.data());
    static_assert(std::is_same_v<Box<int*>, decltype(box)>);
}

TEST(Box_Construction, std_deque) {
    // std::deque as a value
    std::deque<int> const deq = {1, 2, 3};
    [[maybe_unused]] auto box = Box(deq);
    static_assert(std::is_same_v<Box<std::deque<int>>, decltype(box)>);
}

TEST(Box_Construction, std_function) {
    // std::function
    std::function<int(int)> const func = [](int x) { return x * 2; };
    [[maybe_unused]] auto box = Box(func);
    static_assert(std::is_same_v<Box<std::function<int(int)>>, decltype(box)>);
}

TEST(Box_Construction, std_list) {
    // std::list as a value
    std::list<int> const lst = {1, 2, 3};
    [[maybe_unused]] auto box = Box(lst);
    static_assert(std::is_same_v<Box<std::list<int>>, decltype(box)>);
}

TEST(Box_Construction, std_map) {
    // std::map as a value
    std::map<int, std::string> const mp = {
      {1, "one"  },
      {2, "two"  },
      {3, "three"}
    };
    [[maybe_unused]] auto box = Box(mp);
    static_assert(std::is_same_v<Box<std::map<int, std::string>>, decltype(box)>
    );
}

TEST(Box_Construction, std_optional) {
    // std::optional
    std::optional<int> const opt = 42;
    [[maybe_unused]] auto box = Box(opt);
    static_assert(std::is_same_v<Box<std::optional<int>>, decltype(box)>);
}

TEST(Box_Construction, std_set) {
    // std::set as a value
    std::set<int> const st = {1, 2, 3};
    [[maybe_unused]] auto box = Box(st);
    static_assert(std::is_same_v<Box<std::set<int>>, decltype(box)>);
}

TEST(Box_Construction, std_unordered_map) {
    // std::unordered_map as a value
    std::unordered_map<int, std::string> const umap = {
      {1, "one"  },
      {2, "two"  },
      {3, "three"}
    };
    [[maybe_unused]] auto box = Box(umap);
    static_assert(
      std::is_same_v<Box<std::unordered_map<int, std::string>>, decltype(box)>
    );
}
TEST(Box_Construction, std_unordered_set) {
    // std::unordered_set as a value
    std::unordered_set<int> const ust = {1, 2, 3};
    [[maybe_unused]] auto box = Box(ust);
    static_assert(std::is_same_v<Box<std::unordered_set<int>>, decltype(box)>);
}

TEST(Box_Construction, std_vector) {
    // std::vector as a value
    std::vector<int> vec = {1, 2, 3};  // NOLINT
    [[maybe_unused]] auto box = Box(vec);
    static_assert(std::is_same_v<Box<std::vector<int>>, decltype(box)>);
}

TEST(Box_Construction, string_literal) {
    // string literal
    [[maybe_unused]] auto box = Box("hello");
    static_assert(std::is_same_v<Box<std::string>, decltype(box)>);
}

TEST(Box_Construction, unique_ptr) {
    // unique_ptr and rvalue unique_ptr
    auto ptr = std::make_unique<const char*>("hello");
    [[maybe_unused]] auto box1 = Box(ptr);
    static_assert(std::is_same_v<Box<const char*>, decltype(box1)>);

    [[maybe_unused]] auto box2 = Box(std::make_unique<const char*>("hello"));
    static_assert(
      std::is_same_v<
        Box<std::unique_ptr<const char*, std::default_delete<const char*>>>,
        decltype(box2)>
    );
}

TEST(Box_Construction, forwarding_reference_resolution) {
    auto makeBox = [](auto&& x) { return Box(std::forward<decltype(x)>(x)); };

    int i = 5;
    [[maybe_unused]] auto box1 = makeBox(i);  // lvalue
    static_assert(std::is_same_v<decltype(box1), Box<int>>);

    [[maybe_unused]] auto box2 = makeBox(10);  // rvalue
    static_assert(std::is_same_v<decltype(box2), Box<int>>);

    auto const ci = 42;
    [[maybe_unused]] auto box3 = makeBox(ci);  // const lvalue
    static_assert(std::is_same_v<decltype(box3), Box<int>>);
}

TEST(Box_Construction, reference_collapsing_behavior) {
    int x = 42;
    int& ref = x;
    int&& rref = 42;

    [[maybe_unused]] auto box1 = Box(ref);
    static_assert(std::is_same_v<Box<int>, decltype(box1)>);

    [[maybe_unused]] auto box2 = Box(std::move(rref));
    static_assert(std::is_same_v<Box<int>, decltype(box2)>);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, hicpp-no-array-decay)
