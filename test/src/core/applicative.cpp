#include <fp/fp.h>
#include <fp_test.h>
#include <gtest/gtest.h>
#include <rapidcheck/gtest.h>

using namespace fp;
using namespace fp::laws;
using namespace fp::test;

// Law 1: Identity — stack and box
RC_GTEST_PROP(Core_Applicative_Laws, identity_stack_storage, ()) {
    auto fa = pure<StructApplicative>(*rc::gen::arbitrary<int>());
    RC_ASSERT(ApplicativeLaws<StructApplicative>::identity(fa));
}

RC_GTEST_PROP(Core_Applicative_Laws, identity_box_storage, ()) {
    auto a = *rc::gen::arbitrary<String>();
    auto fa = pure<StructApplicative>(a);
    RC_ASSERT(ApplicativeLaws<StructApplicative>::identity(fa));
}

// Law 2: Homomorphism
RC_GTEST_PROP(Core_Applicative_Laws, homomorphism, ()) {
    auto a = *rc::gen::arbitrary<int>();
    RC_ASSERT(ApplicativeLaws<StructApplicative>::homomorphism(triple, a));
}

// Law 3: Interchange
RC_GTEST_PROP(Core_Applicative_Laws, interchange, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto ff = pure<StructApplicative>(triple);
    RC_ASSERT(ApplicativeLaws<StructApplicative>::interchange(ff, a));
}

// Law 4: Composition
RC_GTEST_PROP(Core_Applicative_Laws, composition, ()) {
    auto a = *rc::gen::arbitrary<int>();
    auto ff = pure<StructApplicative>(triple);
    auto fg = pure<StructApplicative>(square);
    auto fa = pure<StructApplicative>(a);
    RC_ASSERT(ApplicativeLaws<StructApplicative>::composition(ff, fg, fa));
}
