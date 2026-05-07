## FP++ Design Decisions

### DD-001 · Mirror Scala Cats for project structure

The project structure is modelled after
Scala [Cats](https://typelevel.org/cats/),
with explicit layers for `kernel`, `core`, `data`, `syntax`, and `laws`. C++
concepts map directly onto Cats-style explicit typeclass registration, and the
kernel/core split honestly reflects the difference in complexity between ground
types (`Eq`, `Order`) and higher-kinded machinery (`Functor`, `Monad`). Cats is
the *model*, not the law — where C++ semantics diverge from Scala, the C++ way
wins (see DD-005).

### DD-002 · Three distinct inclusion contracts

FP++ has exactly three materialization points, each with a different contract:

| Include                        | Safe in `.h`?   | Who uses it                                  |
|--------------------------------|-----------------|----------------------------------------------|
| `#include <fp/fp.h>`           | yes             | Application code — pulls in everything       |
| `#include <fp/core/functor.h>` | yes             | Library authors — surgical, minimal exposure |
| `using namespace fp::syntax`   | no, `.cpp` only | Application code — opts into ergonomics      |

`fp.h` and the granular headers are safe anywhere because they define only
within `fp::` — no free names, no operators injected. `fp::syntax` is an
ergonomics layer that must never appear in a header, as it would leak names into
every downstream translation unit.

### DD-003 · `fp/fp.h` is a contract header, not a convenience header

`#include <fp/fp.h>` is the canonical way for application code to consume
the library: it provides all typeclasses, data types, and instances under the
`fp::` namespace, with no side-effects on the global namespace. It is explicitly
safe to use in header files.

### DD-004 · Granular headers are for library authors

`#include <fp/core/functor.h>` (and its siblings) exist for code that
builds *on top of* FP++ and wants to constrain on a single typeclass without
forcing its own users to pull in the full library. This mirrors the distinction
in Cats between `import cats._` (consumer) and `import cats.Functor` (library
author constraining a type parameter).

### DD-005 · Data types and their canonical instances are co-located

A data type and its typeclass instances live in the same header (e.g.
`data/option.h` defines both `Option<A>` and `Functor<Option>`). The
`data/instances` split in Cats is a Scala artifact — it exists to control
implicit resolution scope, a mechanism C++ does not have. A separate
`instances/` layer is retained only as an escape hatch for orphan instances
(third-party instances for types you do not own).
