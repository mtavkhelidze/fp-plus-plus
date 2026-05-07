#include <fp/fp.h>
#include <gtest/gtest.h>

using namespace fp;
using namespace fp::internal::storage;

template <typename A>
struct TestStruct : StorageStack<TestStruct<A>> {
    using Base = StorageStack<TestStruct<A>>;
    using Base::Base;

    static auto store(auto&& x) -> auto {
        return Base::put(std::forward<decltype(x)>(x));
    }

    [[nodiscard]] auto value() const -> auto& { return this->get(); }
};

TEST(StorageStack, move_is_deleted) {
    static_assert(std::is_move_constructible_v<TestStruct<int>>, "isnt");
}

TEST(StorageStack, copy_assignment_copies_value) {
    auto original = TestStruct<int>::store(123);
    auto copy = TestStruct<int>::store(0);
    copy = original;
    EXPECT_EQ(copy.value(), 123);
    EXPECT_EQ(original.value(), 123);
}

TEST(StorageStack, copy_constructor_copies_value) {
    auto original = TestStruct<int>::store(99);
    const auto copy = original;
    EXPECT_EQ(copy.value(), 99);
    EXPECT_EQ(original.value(), 99);
}

TEST(StorageStack, self_assignment_does_nothing) {
    auto box = TestStruct<int>::store(123);

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wself-assign-overloaded"
    box = box;  // self-assign
#pragma clang diagnostic pop

    EXPECT_EQ(box.value(), 123);
}

TEST(StorageStack, move_assignment_uses_copy) {
    auto original = TestStruct<int>::store(99);
    auto moved = TestStruct<int>::store(0);
    moved = std::move(original);
    EXPECT_EQ(moved.value(), 99);
    EXPECT_EQ(original.value(), 99);
}

TEST(StorageStack, stores_double) {
    auto box = TestStruct<double>::store(3.14);
    EXPECT_DOUBLE_EQ(box.value(), 3.14);
}
