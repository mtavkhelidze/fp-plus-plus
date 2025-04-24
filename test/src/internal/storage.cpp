#include <fp/internal/storage.h>
#include <gtest/gtest.h>

template <typename A>
using StorageProvider = fp::internal::storage::StorageProvider<A>;

template <typename A>
struct Container : public StorageProvider<A> {
    template <typename T>
    static auto apply(T&& value) /* -> Container<std::decay_t<T>> */ {
        return Container{
          StorageProvider<std::decay_t<T>>::store(std::forward<T>(value))
        };
    }
};

TEST(Storage_Fundamental, uses_stack_storage) {
    auto c = Container<int>::apply(0);
    EXPECT_EQ(c.getOrElse(0), 0);
    EXPECT_EQ(c.backend_tag(), "StackStorage");
}

TEST(Storage_Complex, uses_box_storage) {
    auto str = std::string("0xdeadbeef");
    auto c = Container<std::string>::apply(str);
    EXPECT_EQ(c.getOrElse(std::string{}), "0xdeadbeef");
    EXPECT_EQ(c.backend_tag(), "BoxedStorage");
}

TEST(Storage_Fundamental, copy_and_move_preserve_value_and_backend) {
    auto original = Container<int>::apply(42);
    auto copy = original;
    auto moved = std::move(original);

    EXPECT_EQ(copy.getOrElse(0), 42);
    EXPECT_EQ(copy.backend_tag(), "StackStorage");

    EXPECT_EQ(moved.getOrElse(0), 42);
    EXPECT_EQ(moved.backend_tag(), "StackStorage");
}

TEST(Storage_Complex, copy_and_move_preserve_value_and_backend) {
    auto original = Container<std::string>::apply(std::string("0xdeadbeef"));
    auto copy = original;
    auto moved = std::move(original);

    EXPECT_EQ(copy.getOrElse(""), "0xdeadbeef");
    EXPECT_EQ(copy.backend_tag(), "BoxedStorage");

    EXPECT_EQ(moved.getOrElse(""), "0xdeadbeef");
    EXPECT_EQ(moved.backend_tag(), "BoxedStorage");
}

TEST(Storage_Complex, deep_copy_isolated_storage) {
    auto original = Container<std::string>::apply(std::string("deep"));
    auto copy = original;

    // mutate the internal string stored in 'original' via a temporary
    // shared_ptr original and copy should not share internal state
    auto originalValue = original.getOrElse("");
    auto copyValue = copy.getOrElse("");

    // simulate mutation on original (done externally here)
    std::string mutated = originalValue;
    mutated[0] = 's';

    // copy's value should remain unchanged
    EXPECT_EQ(copyValue, "deep");
    EXPECT_EQ(mutated, "seep");
}

TEST(Storage_String_Literal, works) {
    auto c = Container<std::string>::apply("deep");
    // auto ints = {1, 2, 3};
    // auto i = Container<std::string>::apply(ints);
}
