#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

using namespace fp;
using namespace fp::laws;
using namespace fp::test;

// Law 1: Identity — stack and box
RC_GTEST_PROP(Core_Applicative_Laws, identity_stack_storage, ()) {
    auto fa = pure<StructWithPure>(*rc::gen::arbitrary<int>());
    RC_ASSERT(ApplicativeLaws<StructWithPure>::identity(fa));
}

RC_GTEST_PROP(Core_Applicative_Laws, identity_box_storage, ()) {
    auto a = *rc::gen::arbitrary<String>();
    auto fa = pure<StructWithPure>(a);
    RC_ASSERT(ApplicativeLaws<StructWithPure>::identity(fa));
}

// Law 2: Homomorphism
RC_GTEST_PROP(Core_Applicative_Laws, homomorphism, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ApplicativeLaws<StructWithPure>::homomorphism(triple, a));
}

// Law 3: Interchange
RC_GTEST_PROP(Core_Applicative_Laws, interchange, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto ff = pure<StructWithPure>(triple);
    RC_ASSERT(ApplicativeLaws<StructWithPure>::interchange(ff, a));
}

// Law 4: Composition
RC_GTEST_PROP(Core_Applicative_Laws, composition, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto ff = pure<StructWithPure>(triple);
    auto fg = pure<StructWithPure>(square);
    auto fa = pure<StructWithPure>(a);
    RC_ASSERT(ApplicativeLaws<StructWithPure>::composition(ff, fg, fa));
}
