#ifndef FP_TYPE_FUNCTOR_FUNCTOR_TYPES_H
#define FP_TYPE_FUNCTOR_FUNCTOR_TYPES_H
#pragma once

#include <fp/fp.h>

template <typename A>
struct FunctorStruct : fp::mixins::WithValue<FunctorStruct<A>> {
  public:
    using Base = fp::mixins::WithValue<FunctorStruct<A>>;
    using Base::Base;

    auto map(auto& f) -> FunctorStruct {
        return fp::type::classes::Functor::map<A>(*this)(f);
    }
};

#endif  // FP_TYPE_FUNCTOR_FUNCTOR_TYPES_H
