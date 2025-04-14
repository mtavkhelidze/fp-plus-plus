#include <fp/fp.h>

#include <type_traits>

auto f_lambda = [](std::string x) -> std::string { return x; };
static_assert(fp_is_unary<decltype(f_lambda)>, "lambda is not callable");

int f_fn(int /* x */) { return 0; }
static_assert(fp_is_unary<decltype(f_fn)>, "functon is not callable");

struct f_struct {
    int operator()(int /* x */) { return 0; }
};
static_assert(
  std::is_invocable_r_v<int, f_struct, int>, "Struct is not callable"
);

int main() {  //
    return 0;
}
