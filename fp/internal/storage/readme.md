### Box

Generic value holder (`Box`) that wraps a value of type `T`, enforcing
shared ownership and idiot-resistant immutability.

- The boxed value is heap-allocated and managed via `shared_ptr<const
T>`.
- Once boxed, the value cannot be modified through any API exposed by `Box`.
  This prevents accidental or intentional mutation through normal usage.
- True immutability depends on `T` not exposing mutating behavior via
  `mutable` fields or internal `const_cast` tricks.
- Move construction and move assignment are disallowed to preserve
  immutability and clarity of ownership.
- Copying is allowed and cheap, as it only increments the reference count
  of the underlying `shared_ptr`.
- Special constructors handle pointer types, tuples, C-style arrays, and
  null.
- This approach prioritizes immutability-by-design over absolute
  enforcement.

#### Pointers:

- When boxing raw pointers (e.g., `T*`), `Box` stores a copy of the
  pointer value but does NOT take ownership of the pointee.
- The caller remains responsible for managing the lifetime and deleting
  the allocated memory if applicable.
- To enable automatic lifetime management, prefer boxing
  `std::shared_ptr` or `std::unique_ptr` instead of raw pointers.
