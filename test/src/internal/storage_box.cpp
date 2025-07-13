#include <fp/internal/storage/storage_box.h>
#include <gtest/gtest.h>

#include <string>
#include <type_traits>

using namespace fp::internal::storage;
template <typename A>
struct TestStruct : StorageBox<TestStruct<A>> {
    using Base = StorageBox<TestStruct<A>>;
    using Base::Base;

    static auto store(auto&& x) -> auto {
        return StorageBox<TestStruct<A>>::put(std::forward<decltype(x)>(x));
    }

    auto value() { return this->get(); }
    auto has_value() { return !this->empty(); }
};

TEST(StorageBox, copy_assignment_works) {
    auto a = TestStruct<std::string>::store(std::string("foo"));
    TestStruct<std::string> b =
      TestStruct<std::string>::store(std::string("bar"));

    b = a;  // copy assignment

    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(b.value(), a.value());
    EXPECT_NE(b.value().c_str(), a.value().c_str());
}

TEST(StorageBox, copy_box) {
    auto a = TestStruct<std::string>::store(std::string("hello"));
    auto b = a;

    EXPECT_TRUE(b.has_value());
    EXPECT_EQ(a.value(), b.value());
    EXPECT_NE(a.value().c_str(), b.value().c_str());
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

TEST(StorageBox, multiple_copies_are_distinct) {
    auto a = TestStruct<std::string>::store(std::string("copytest"));
    auto b = a;
    auto c = b;

    EXPECT_EQ(a.value(), b.value());
    EXPECT_EQ(b.value(), c.value());

    EXPECT_NE(a.value().c_str(), b.value().c_str());
    EXPECT_NE(b.value().c_str(), c.value().c_str());
    EXPECT_NE(a.value().c_str(), c.value().c_str());
}

TEST(StorageBox, not_empty_after_put) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_TRUE(box.has_value());
}

TEST(StorageBox, put_and_get_complex_type) {
    auto box = TestStruct<std::string>::store(std::string("hello"));
    EXPECT_EQ(box.value(), "hello");
}

TEST(StorageBox, self_copy_assignment_is_safe) {
    auto a = TestStruct<int>::store(42);
// we do this check already in operator=
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    a = a;
#pragma clang diagnostic pop
    EXPECT_TRUE(a.has_value());
    EXPECT_EQ(a.value(), 42);
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
