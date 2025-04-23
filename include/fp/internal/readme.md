### Call Sequence

```
End user
└──> Id<A> (or any other container)
    └──> inherits from Storage<A>
          └──> alias to either:
                → BoxedStorage<Storage, A> (for non-fundamental types)
                → StackStorage<Storage, A> (for fundamental types)
```

### Specs

Id:

* Must be an unary type-class instance
* Hold its value in Storage
* Cannot be created other than through `Id::apply`, which maybe called by `pure`
* Cannot be:
    * moved
    * **not** copied, only recreated via `Id::apply`
* `Id::apply<T>` must return `Id<T>` with `T` decayed.
