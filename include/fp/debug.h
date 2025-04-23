#ifndef FP_DEBUG_H
#define FP_DEBUG_H

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#pragma once
#include <string_view>

template <typename T>
consteval std::string_view type_name() {
#if defined(__clang__)
    constexpr auto p = std::string_view(__PRETTY_FUNCTION__);
    return p.substr(p.find('=') + 2, p.size() - p.find(']') - 3);
#elif defined(__GNUC__)
    constexpr auto p = std::string_view(__PRETTY_FUNCTION__);
    return p.substr(p.find('=') + 2, p.rfind(';') - p.find('=') - 2);
#elif defined(_MSC_VER)
    constexpr auto p = std::string_view(__FUNCSIG__);
    return p.substr(p.find('<') + 1, p.rfind('>') - p.find('<') - 1);
#else
    return "unsupported compiler";
#endif
}
#endif  // FP_DEBUG_H
