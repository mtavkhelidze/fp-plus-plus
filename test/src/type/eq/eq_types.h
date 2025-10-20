#ifndef TEST_SRC_TYPE_EQ_EQ_TEST_H
#define TEST_SRC_TYPE_EQ_EQ_TEST_H

#include <fp/fp.h>

template <typename A>
struct EqStruct
    : fp::mixins::WithValue<EqStruct<A>>
    , fp::mixins::WithEq<EqStruct, A> {
    using Base = fp::mixins::WithValue<EqStruct<A>>;
    using Base::Base;
};

struct CustomWithOperators {
    int value;  // NOLINT

    [[nodiscard]] constexpr auto operator==(
      const CustomWithOperators& other
    ) const noexcept -> bool {
        return value == other.value;
    }

    // Required for operator!= to work by default, or implement it manually
    [[nodiscard]] constexpr auto operator!=(
      const CustomWithOperators& other
    ) const noexcept -> bool {
        return value != other.value;
    }
};

template <typename A>
struct CustomWithEq : fp::mixins::WithEq<CustomWithEq, int> {
    using Base = fp::mixins::WithEq<CustomWithEq, int>;
    using Base::Base;

    int value;  // NOLINT
    explicit CustomWithEq(A a) : value(a) {}

    [[nodiscard]] constexpr auto operator==(
      const CustomWithEq& other
    ) const noexcept -> bool {
        return value == other.value;
    }

    // Required for operator!= to work by default, or implement it manually
    [[nodiscard]] constexpr auto operator!=(
      const CustomWithEq& other
    ) const noexcept -> bool {
        return value != other.value;
    }
};

#endif  // TEST_SRC_TYPE_EQ_EQ_TEST_H
