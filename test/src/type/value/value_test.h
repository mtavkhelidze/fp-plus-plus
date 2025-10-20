#ifndef TEST_SRC_TYPE_EQ_TEST_H
#define TEST_SRC_TYPE_EQ_TEST_H

#include <fp/fp.h>

template <typename A>
struct ValueStruct : fp::mixins::WithValue<ValueStruct<A>> {
    using Base = fp::mixins::WithValue<ValueStruct<A>>;
    using Base::Base;
};
#endif  // TYPE_EQ_TEST_H
