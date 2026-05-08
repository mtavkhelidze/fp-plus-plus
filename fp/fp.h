#ifndef FP_FP_H
#define FP_FP_H
#pragma once

#define FP_PLUS_PLUS_INCLUDED_FROM_FP_FP 1
#include <fp/data/data.h>
#include <fp/internal/meta/meta.h>
#include <fp/internal/storage/storage.h>
#undef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

namespace fp {
using namespace fp::data;
using fp::internal::meta::cast::cast;
}  // namespace fp

#endif  // FP_FP_H
