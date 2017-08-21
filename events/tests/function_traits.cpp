#include <events/function_traits.h>

#include <gtest/gtest.h>

struct Foo {
    int         bar(int) { return 1; }
    int         ba() { return 2; }
    static int  b() { return 3; }
    static void c(int, int) {}
    int         operator()() { return 5; }
};

TEST(fn_traits, basics) {
    using namespace events;

    using traits1 = meta::function_traits<decltype(&Foo::bar)>;
    using traits2 = meta::function_traits<decltype(&Foo::ba)>;
    using traits3 = meta::function_traits<decltype(Foo::b)>;
    using traits4 = meta::function_traits<decltype(Foo::c)>;
    using traits5 = meta::function_traits<decltype(&Foo::operator())>;

    static_assert(traits1::arity == 1, "arity check");
    static_assert(traits2::arity == 0, "arity check");
    static_assert(traits3::arity == 0, "arity check");
    static_assert(traits4::arity == 2, "arity check");
    static_assert(traits5::arity == 0, "arity check");

    static_assert(
            std::is_same<traits1::result_type, int>::value,
            "result_type check");
    static_assert(
            std::is_same<traits2::result_type, int>::value,
            "result_type check");
    static_assert(
            std::is_same<traits3::result_type, int>::value,
            "result_type check");
    static_assert(
            std::is_same<traits4::result_type, void>::value,
            "result_type check");
    static_assert(
            std::is_same<traits5::result_type, int>::value,
            "result_type check");

    auto lambda         = [](int i) { std::cout << i << "lambda\n"; };
    using lambda_traits = meta::function_traits<decltype(lambda)>;

    static_assert(lambda_traits::arity == 1, "arity check");
    static_assert(
            std::is_same<lambda_traits::arg_t<0>, int>::value, "arg type");
    static_assert(
            std::is_same<lambda_traits::result_type, void>::value,
            "result_type check");

    static_assert(meta::is_callable<decltype(Foo::b)>::value, "");
    static_assert(!meta::is_callable<std::add_pointer<int()>>::value, "");
    static_assert(!std::is_same<int (*)(), decltype(Foo::b)>::value, "");

    static_assert(
            std::is_same<std::function<int(int)>, traits1::as_function_t>::
                    value,
            "");
}
