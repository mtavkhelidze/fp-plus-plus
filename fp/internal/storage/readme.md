### Box &lt;A&gt;

Generic value holder (`Box`) that wraps a value of type `A` stripped down of C++
bells and whistles like reference, const reference, and similar. It's immutable,
copy-only and possessive: once you give something to Box, it owns it.

- The boxed value is heap-allocated and managed via `shared_ptr<const A>`.
- Once boxed, the value cannot be modified through any API exposed by `Box`. This
  prevents accidental or intentional mutation through normal usage.
- True immutability depends on `A` not exposing mutating behavior via `mutable`
  fields or internal `const_cast` tricks.
- Move construction and move assignment are disallowed. `Box` is copy-only —
  copying is cheap as it merely increments the `shared_ptr` reference count.
- Special constructors handle pointer types, tuples, C-style arrays, and null.
- This approach prioritizes immutability-by-design over absolute enforcement.
#### Empty state:

- `Box` can be in an empty state via the default constructor `Box()`.
- This is an internal implementation detail — not part of the public API.
- `empty()` tests for this state. Calling `get()` on an empty `Box` is undefined
  behaviour.
- Public API types built on `Box` (e.g. `Id<A>`) guarantee a non-empty box.

#### Pointers:

- When boxing a `std::unique_ptr<A>`, ownership is unconditionally transferred.
  The original pointer is null after construction.
- When boxing a `std::shared_ptr<A>`, ownership is shared via reference counting.
- When boxing a raw pointer `A*`, `Box` stores the pointer value but does NOT
  take ownership of the pointee. The caller remains responsible for lifetime
  management. Prefer `std::shared_ptr` or `std::unique_ptr` for automatic
  lifetime management.
