### Storage

Internal storage layer for FP++. Not part of the public API.

#### Overview

Two backends, selected automatically based on the inner type of the container:

- **`StorageStack`** — for fundamental types (`int`, `double`, etc.).
  Stack-allocated, zero overhead.
- **`StorageBox`** — for everything else. Heap-allocated via `Box`, managed by
  `shared_ptr<const T>`.

Selection is done at compile time in `WithValue` — the user never sees it.

#### Design

- **Copy-only** — no move operations. Copying is cheap: fundamentals copy by
  value, boxed types increment a `shared_ptr` reference count.
- **No empty state** — storage always holds a valid value. `Box` allows empty;
  storage does not.
- **`put` is the only construction path** — value constructors are `private`.
  Derived types construct via `put`, which normalises the type and returns the
  correctly-rebound container.
- **Immutable** — `get()` returns `const A&`. The stored value cannot be modified
  after construction.
