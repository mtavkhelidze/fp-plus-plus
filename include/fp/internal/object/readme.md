### Storage Abstraction

```mermaid
flowchart TD
    User[End user code] -- create via apply --> CRTP
    subgraph CRTP
        data["DataClass&lt;A&gt;"] --> SP["Object&lt;A&gt;"]
        SP -- complex type A --> Boxed["StorageBox&lt;Storage, A&gt;"]
        SP -- fundamental type A --> Stack["StorageStack&lt;Storage, A&gt;"]
        Boxed:::boxed
        Stack:::stack
    end
```

### Specs

DataClass:

* Must be an unary type-class instance
* Hold its value using Object
* Cannot be created other than through `apply`, which maybe called by `pure`
* Cannot be:
    * moved
    * **not** copied, only recreated via `apply`
* `apply<A>` returns `DataClass<A>` with `A` decayed.
