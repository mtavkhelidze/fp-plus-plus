#ifndef __FP_PP_FUNCTIONS_H__
#define __FP_PP_FUNCTIONS_H__

#ifndef __FP_PLUS_PLUS__
#error "This file must be included from fp/fp"
#endif

namespace fp {

auto id = [](auto x) { return x; };

}  // namespace fp
#endif  // __FP_PP_FUNCTIONS_H__
