#include <fp/core/all.h>
#include <fp/internal/storage/storage_box.h>
#include <fp/tools/all.h>
#include <gtest/gtest.h>

#include <string>
#include <type_traits>

using namespace fp::internal::storage;
using namespace fp::core;
using namespace fp::tools;

template <typename A>
struct TestStruct : StorageBox<TestStruct<A>> {
    using Base = StorageBox<TestStruct<A>>;
    using Base::Base;

    static auto store(auto&& x) -> auto {
        return Base::put(std::forward<decltype(x)>(x));
    }

    auto value() const -> auto& { return this->get(); }
    auto has_value() const { return !this->empty(); }
};

TEST(StorageBox, const_accessors) {
    auto box = TestStruct<std::string>::store(std::string("const test"));
    const auto& const_box = box;
    EXPECT_EQ(const_box.value(), "const test");
    EXPECT_TRUE(const_box.has_value());
}

TEST(StorageBox, copy_assignment_is_shallow) {
    auto a = TestStruct<std::string>::store(std::string("foo"));
    // Get the address of the string data in 'a'
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto a_ptr = (unsigned long)(a.value().c_str());
#pragma clang diagnostic pop

    TestStruct<std::string> b =
      TestStruct<std::string>::store(std::string("bar"));

    b = a;  // copy assignment

    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(b.value(), a.value());  // Content is equal ("foo")
    EXPECT_EQ((unsigned long)(b.value().c_str()), a_ptr);
}

TEST(StorageBox, multiple_copies_share_data) {  // Renamed for clarity
    auto a = TestStruct<std::string>::store(std::string("copytest"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto a_ptr = (unsigned long)(a.value().c_str());
#pragma clang diagnostic pop

    auto b = a;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto b_ptr = (unsigned long)(b.value().c_str());  // Should be same as a_ptr
#pragma clang diagnostic pop

    auto c = b;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdangling-gsl"
    auto c_ptr = (unsigned long)(c.value().c_str());  // Should be same as a_ptr
#pragma clang diagnostic pop

    EXPECT_EQ(a.value(), b.value());
    EXPECT_EQ(b.value(), c.value());

    EXPECT_EQ(a_ptr, b_ptr);
    EXPECT_EQ(b_ptr, c_ptr);
    EXPECT_EQ(a_ptr, c_ptr);
}

TEST(StorageBox, doesnt_allow_move) {
    static_assert(
      !std::is_move_constructible_v<StorageBox<TestStruct<int>>>,
      "StorageBox should not be move constructible"
    );
    static_assert(
      !std::is_move_assignable_v<StorageBox<TestStruct<int>>>,
      "StorageBox should not be move assignable"
    );
}

TEST(StorageBox, empty_box_behavior) {
    auto box = TestStruct<Nothing>::store(nothing);
    ASSERT_TRUE(box.has_value());
}

TEST(StorageBox, not_empty_after_put) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_TRUE(box.has_value());
}

TEST(StorageBox, put_and_get_complex_type) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_EQ(box.value(), "hello");
}

TEST(StorageBox, self_copy_assignment_explicit) {
    auto box = TestStruct<std::string>::store(std::string("abc"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    box = box;
#pragma clang diagnostic pop
    EXPECT_TRUE(box.has_value());
    EXPECT_EQ(box.value(), "abc");
}

TEST(StorageBox, self_copy_assignment_is_safe) {
    auto a = TestStruct<std::string>::store(std::string("safe"));
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    a = a;
#pragma clang diagnostic pop
    EXPECT_TRUE(a.has_value());
    EXPECT_EQ(a.value(), "safe");
}

TEST(StorageBox, works_with_various_types) {
    // int
    auto int_box = TestStruct<int>::store(7);
    EXPECT_EQ(int_box.value(), 7);

    // double
    auto double_box = TestStruct<double>::store(3.14);
    EXPECT_EQ(double_box.value(), 3.14);

    // user-defined struct
    struct Point {
        int x, y;
    };
    auto point_box = TestStruct<Point>::store(Point{1, 2});
    EXPECT_EQ(point_box.value().x, 1);
    EXPECT_EQ(point_box.value().y, 2);
}

TEST(StorageBox, default_constructs_empty_with_correct_type) {
    TestStruct<const std::string&> box;
    EXPECT_FALSE(box.has_value());
    static_assert(
      std::same_as<
        decltype(std::declval<decltype(box)>().value()), const std::string&>
    );
}
