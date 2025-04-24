
template <template <typename> typename TC, typename T>
struct CRTPBase {
    T t;
    CRTPBase(T t) : t(t) {}
};

template <typename T>
struct CRTPDerived : public CRTPBase<CRTPDerived, T> {
    using Base = CRTPBase<CRTPDerived, T>;
    using Base::Base;
};

auto main() -> int {  //
    CRTPDerived<int> derived(10);
    return 0;
}
