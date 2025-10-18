#ifndef TEST_SRC_TYPE_EQ_TEST_H
#define TEST_SRC_TYPE_EQ_TEST_H

#include <fp/fp.h>
#include <gtest/gtest.h>

template <typename A>
struct TestStruct
    : fp::mixins::WithValue<TestStruct<A>>
    , fp::mixins::WithEq<TestStruct, A> {
    using Base = fp::mixins::WithValue<TestStruct<A>>;
    using Base::Base;
};
#endif  // TYPE_EQ_TEST_H
