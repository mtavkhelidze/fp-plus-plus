#include <fp/internal/box.h>
#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers, hicpp-no-array-decay)
using ::testing::Test;
using namespace fp::internal::box;

TEST(Box_Construction, literal_initialization_list_to_tuple) {
    // list members must be of the same time, or it will go into std::tuple
    const int x = 10;
    const int& y = x;
    auto box3 = Box{1, x, y};
    static_assert(
      std::is_same_v<std::tuple<int, int, int>, decltype(box3)::kind>
    );

    auto v3 = box3.get();
    static_assert(std::is_same<std::tuple<int, int, int>, decltype(v3)>::value);

    auto misha = Box(1);
    EXPECT_EQ(std::get<0>(v3), 1);
    EXPECT_EQ(std::get<1>(v3), x);
    EXPECT_EQ(std::get<2>(v3), y);

    auto box1 = Box{x};
    static_assert(std::is_same_v<int, decltype(box1)::kind>);

    auto v1 = box1.get();
    static_assert(std::is_same_v<int, decltype(v1)>);
    EXPECT_EQ(v1, x);
}

TEST(Box_Construction, literal_fundamental) {
    auto box1 = Box(1);
    static_assert(std::is_same_v<int, decltype(box1)::kind>);
    ASSERT_EQ(box1.get(), 1);

    const double x = 1.0;
    auto box2 = Box(x);
    static_assert(std::is_same_v<double, decltype(box2)::kind>);
    ASSERT_EQ(box2.get(), 1);

    const int& y = x;
    auto box3 = Box(y);
    static_assert(std::is_same_v<int, decltype(box3)::kind>);
    ASSERT_EQ(box3.get(), 1);
}

TEST(Box_Construction, literal_string) {
    Box box1("hello");
    static_assert(std::is_same_v<std::string, decltype(box1)::kind>);
    ASSERT_TRUE(strcmp(box1.get().c_str(), "hello") == 0);

    auto str = "hello";
    auto& str_ref = str;
    auto box2 = Box(str_ref);
    static_assert(std::is_same_v<Box<std::string>, decltype(box2)>);
    ASSERT_EQ(box2.get(), "hello");
}

TEST(Box_Construction, nothing_empty) {
    auto box1 = Box();
    static_assert(std::is_same_v<Nothing, decltype(box1)::kind>);

    auto x1 = box1.get();
    ASSERT_TRUE(box1.empty());
    ASSERT_EQ(x1, Nothing());

    auto box2 = Box(nullptr);
    static_assert(std::is_same_v<Nothing, decltype(box2)::kind>);

    auto x2 = box2.get();
    ASSERT_TRUE(box2.empty());
    ASSERT_EQ(x2, Nothing());
}

TEST(Box_Construction, literal_c_arrays) {
    int arr1[] = {1, 2, 3};
    auto box1 = Box(arr1);
    static_assert(std::is_same_v<std::vector<int>, decltype(box1)::kind>);

    auto v1 = box1.get();
    static_assert(std::is_same_v<std::vector<int>, decltype(v1)>);
    EXPECT_EQ(v1[0], 1);
    EXPECT_EQ(v1[1], 2);
    EXPECT_EQ(v1[2], 3);

    std::string arr2[] = {"one", "two", "three"};
    auto box2 = Box(arr2);
    static_assert(std::is_same_v<std::vector<std::string>, decltype(box2)::kind>
    );

    auto v2 = box2.get();
    static_assert(std::is_same_v<std::vector<std::string>, decltype(v2)>);
    EXPECT_EQ(v2[0], "one");
    EXPECT_EQ(v2[1], "two");
    EXPECT_EQ(v2[2], "three");
}

TEST(Box_Construction, literal_varargs) {
    auto x = 10;
    auto y = &x;
    auto& z = x;
    auto a = "hello";

    auto box1 = Box(x, y, z, a);
    static_assert(std::is_same_v<
                  std::tuple<int, int*, int, const char*>, decltype(box1)::kind>
    );
    auto t1 = box1.get();
    ASSERT_EQ(std::get<0>(t1), x);
    ASSERT_EQ(std::get<1>(t1), y);
    ASSERT_EQ(std::get<2>(t1), z);
    ASSERT_EQ(std::get<3>(t1), a);

    auto box2 = Box{x, y, z, a};
    static_assert(std::is_same_v<
                  std::tuple<int, int*, int, const char*>, decltype(box2)::kind>
    );
    auto t2 = box2.get();
    ASSERT_EQ(std::get<0>(t2), x);
    ASSERT_EQ(std::get<1>(t2), y);
    ASSERT_EQ(std::get<2>(t2), z);
    ASSERT_EQ(std::get<3>(t2), a);

    auto box3 = Box{a};
    static_assert(std::is_same_v<std::string, decltype(box3)::kind>);
    auto t3 = box3.get();
    ASSERT_EQ(t3, std::string(a));
}

TEST(Box_Construction, object_copy_only_type) {
    // copy-only type
    struct CopyOnly {  // NOLINT
        CopyOnly() = default;
        CopyOnly(const CopyOnly&) = default;
        CopyOnly(CopyOnly&&) = delete;
    };
    auto box = Box(CopyOnly{});
    static_assert(std::is_same_v<CopyOnly, decltype(box)::kind>);
}

TEST(Box_Construction, move_only_rvalue_and_smart_ptr) {
    // move-only type and rvalue move-only smart pointer
    struct MoveOnly {
        MoveOnly() = default;
        MoveOnly(MoveOnly&&) = default;
        MoveOnly(const MoveOnly&) = delete;
        ~MoveOnly() = default;
    };
    auto box1 = Box(MoveOnly{});
    static_assert(std::is_same_v<MoveOnly, decltype(box1)::kind>);

    auto box2 = Box{std::make_unique<int>(5)};
    static_assert(std::is_same_v<std::unique_ptr<int>, decltype(box2)::kind>);
}

TEST(Box_Construction, function_pointer) {
    // function pointer
    using FuncType = int (*)(int);
    FuncType func = [](int x) { return x * 2; };
    auto box = Box(func);
    static_assert(std::is_same_v<FuncType, decltype(box)::kind>);

    auto f = box.get();
    ASSERT_EQ(f(5), 10);
}

TEST(Box_Construction, callable_lambda_expression) {
    // lambda expression
    auto lambda = []() { return 42; };
    auto box = Box(lambda);
    static_assert(std::is_same_v<Box<decltype(lambda)>, decltype(box)>);

    auto f = box.get();
    ASSERT_EQ(f(), 42);
}

TEST(Box_Construction, callable_std_function) {
    std::function<int(int)> const func = [](int x) { return x * 2; };
    auto box = Box(func);
    static_assert(std::is_same_v<std::function<int(int)>, decltype(box)::kind>);

    auto f = box.get();
    ASSERT_EQ(f(5), 10);
}

TEST(Box_Construction, shared_ptr) {
    // shared_ptr and rvalue shared_ptr
    auto ptr = std::make_shared<std::string>("hello");
    auto box1 = Box(ptr);
    static_assert(std::is_same_v<std::string, decltype(box1)::kind>);

    struct MyType {};
    auto box2 = Box(std::make_shared<MyType>());
    static_assert(std::is_same_v<MyType, decltype(box2)::kind>);
}

TEST(Box_Construction, std_array) {
    std::array<int, 3> xs = {1, 2, 3};

    auto box1 = Box(xs);
    static_assert(std::is_same_v<std::array<int, 3>, decltype(box1)::kind>);

    auto box2 = Box(xs.data());
    static_assert(std::is_same_v<int*, decltype(box2)::kind>);
}

TEST(Box_Construction, forwarding_reference_resolution) {
    auto makeBox = [](auto&& x) { return Box(std::forward<decltype(x)>(x)); };

    int i = 5;
    auto box1 = makeBox(i);  // lvalue
    static_assert(std::is_same_v<decltype(box1), Box<int>>);

    auto box2 = makeBox(10);  // rvalue
    static_assert(std::is_same_v<decltype(box2), Box<int>>);

    auto const ci = 42;
    auto box3 = makeBox(ci);  // const lvalue
    static_assert(std::is_same_v<decltype(box3), Box<int>>);
}

TEST(Box_Construction, reference_collapsing_behavior) {
    int x = 42;
    int& ref = x;
    int&& rref = 42;

    auto box1 = Box(ref);
    static_assert(std::is_same_v<Box<int>, decltype(box1)>);

    auto box2 = Box(std::move(rref));
    static_assert(std::is_same_v<Box<int>, decltype(box2)>);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers, hicpp-no-array-decay)
