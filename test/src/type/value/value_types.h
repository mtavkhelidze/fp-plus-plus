#ifndef TYPE_VALUE_VALUE_TYPES_H
#define TYPE_VALUE_VALUE_TYPES_H

#include <fp/fp.h>

template <typename A>
struct ValueStruct : fp::mixins::WithValue<ValueStruct<A>> {
    using Base = fp::mixins::WithValue<ValueStruct<A>>;
    using Base::Base;
};

#endif  // TYPE_VALUE_VALUE_TYPES_H
