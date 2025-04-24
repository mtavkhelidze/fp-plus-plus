### Storage Abstraction

```mermaid
flowchart TD
    User[End user code] -- create via apply --> CRTP
    subgraph CRTP
        data["DataClass&lt;A&gt;"] --> SP["StorageProvider&lt;A&gt;"]
        SP -- complex type A --> Boxed["BoxedStorage&lt;Storage, A&gt;"]
        SP -- fundamental type A --> Stack["StackStorage&lt;Storage, A&gt;"]
        Boxed:::boxed
        Stack:::stack
    end
```

### Specs

DataClass:

* Must be an unary type-class instance
* Hold its value using StorageProvider
* Cannot be created other than through `apply`, which maybe called by `pure`
* Cannot be:
    * moved
    * **not** copied, only recreated via `apply`
* `apply<A>` returns `DataClass<A>` with `A` decayed.
