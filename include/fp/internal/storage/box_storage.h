#ifndef FP_INTERNAL_STOEAGE_BOX_STORAGE_H
#define FP_INTERNAL_STOEAGE_BOX_STORAGE_H
#pragma once

#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP

#include <fp/internal/storage/box.h>
#include <fp/tools/inner_type.h>
#include <fp/tools/rebind.h>

namespace fp::internal::storage {
/**
 * StorageBox: Immutable boxed value storag for non-trivial typese.
 *
 * - No move operations allowed.
 * - Copy operations allowed.
 * - Constructed only via static put().
 * - Always contains a valid boxed value; no empty state.
 */
template <class Container>
    requires(
      !std::is_fundamental_v<fp::tools::inner_type::fp_inner_type<Container>>
    )
struct StorageBox {
  private:
    using A = fp::tools::inner_type::fp_inner_type<Container>;

    template <typename TC, typename T>
    using rebind = fp::tools::rebind::fp_rebind<TC, T>;

    using Box = Box<A>;
    Box box;

  protected:
    explicit StorageBox(const Box& b) noexcept : box(b) {}
    StorageBox(const StorageBox& other) noexcept = default;
    inline StorageBox& operator=(const StorageBox& other) noexcept = default;
    ~StorageBox() noexcept = default;

  private:
    StorageBox() noexcept = delete;
    StorageBox(StorageBox&&) noexcept = delete;
    StorageBox& operator=(StorageBox&&) noexcept = delete;

  protected:
    inline constexpr auto get() const noexcept -> const A& { return box.get(); }

    /**
     * Boxes a raw value of type T, normalizing it to the FP type U (A),
     *        rebinds the container to U, and returns the derived container.
     *
     * T - raw C++ type of the value to be boxed.
     * U (A) - normalized FP type stored inside the Box.
     */
    template <typename T>
    static auto put(T&& value) {
        auto box = Box{std::forward<T>(value)};
        using U = typename decltype(box)::kind;
        using Derived = rebind<Container, U>;
        return Derived{box};
    }

#ifdef FP_PLUS_PLUS_TESTING
  protected:
    static constexpr const char* _tag = "StorageBox";
#endif
};

}  // namespace fp::internal::storage

#endif  // FP_INTERNAL_STOEAGE_BOX_STORAGE_H
