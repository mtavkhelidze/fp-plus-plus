#include <vector>
#ifndef FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#error "This file must be included from <fp/fp.h>"
#endif  // FP_PLUS_PLUS_INCLUDED_FROM_FP_FP
#ifndef FP_BOX_H
// NOLINTNEXTLINE:llvm-header-guard
#define FP_BOX_H

#include <memory>

#include "defs.h"

namespace fp {

template <typename T, typename... Ts>
struct Box {
  private:
    std::variant<std::shared_ptr<T>, std::vector<T>, Nothing> data = Nothing();

  public:
    // --- Accessors
    [[nodiscard]] [[clang::annotate("nullable")]]
    auto getOrNull() const -> const T* {
        if (data.index() == 0) {
            return std::get<std::shared_ptr<T>>(data).get();
        }
        if (data.index() == 1) { return std::get<std::vector<T>>(data).data(); }
        return nullptr;
    }
    // --- constructors
    // Concrete
    explicit Box(const T& t)
        requires(!std::is_pointer_v<T> && !std::is_null_pointer_v<T>)
        : data{std::make_shared<T>(t)} {}
    // Pointer: shared
    explicit Box(std::shared_ptr<T> ptr) : data(std::move(ptr)) {}
    // Pointer: unique
    explicit Box(std::unique_ptr<T>& ptr) : data(std::move(ptr)) {}
    // Pointer: raw
    explicit Box(T ptr)
        requires(std::is_pointer_v<T>)
        : data{std::make_shared<T>(ptr)} {}
    // Varargs; creates an array
    explicit Box(const T&& t, Ts&&... ts)
        requires(sizeof...(Ts) > 0)
    {
        constexpr size_t size = sizeof...(Ts) + 1;
        std::vector<T> vec = {std::move(t), std::move(ts)...};
        data = std::move(vec);
    }
    // nullptr: can't have it
    // explicit Box(std::nullptr_t) : data(Nothing()) {}

    // Move-only
    explicit Box(T&& t)
        requires(
          std::is_move_constructible_v<T> && !std::is_copy_constructible_v<T>
        )
        : data{std::make_shared<T>(std::move(t))} {}

    // nothing (default comes here)
    explicit Box<Nothing>() : data(Nothing()) {}

    // --- Other constructors
    ~Box() = default;
    auto operator=(Box&&) -> Box& = default;
    auto operator=(const Box&) -> Box& = default;
    Box(Box&&) = default;
    Box(const Box&) = default;
} FP_PLUS_PLUS_ALIGN_PACKED;

// Deduction guides
template <typename T>
Box(T&&) -> Box<std::decay_t<T>>;

template <typename U, std::size_t N>
Box(const std::array<U, N>&) -> Box<U*>;

Box(const char*) -> Box<std::string>;

Box() -> Box<Nothing>;

Box(std::nullptr_t) -> Box<Nothing>;
}  // namespace fp

#endif  // FP_BOX_H
