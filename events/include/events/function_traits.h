#pragma once

#include <functional>
#include <type_traits>
#include <typeinfo>
#include <utility>

namespace events {
namespace meta {

// detects callable objects, not functions
// http://stackoverflow.com/questions/15393938/find-out-if-a-c-object-is-callable
template <typename T>
class is_callable_object {
private:
    using yes = char (&)[1];
    using no  = char (&)[2];

    struct Fallback {
        void operator()();
    };
    struct Derived : T, Fallback {};

    template <typename U, U>
    struct Check;

    template <typename>
    static yes test(...);

    template <typename C>
    static no test(Check<void (Fallback::*)(), &C::operator()>*);

public:
    static const bool value = sizeof(test<Derived>(0)) == sizeof(yes);
};

template <typename T>
static constexpr auto is_callable_object_v = is_callable_object<T>::value;

// function traits

inline namespace detail {
template <typename ReturnType, typename ClassType, typename... Args>
struct mem_function_traits {
    static constexpr auto arity = sizeof...(Args);

    using result_type           = ReturnType;
    using class_type            = ClassType;
    static constexpr auto valid = true;

    template <size_t i>
    struct arg {
        using type = std::tuple_element_t<i, std::tuple<Args...>>;
    };

    template <size_t i>
    using arg_t = typename arg<i>::type;

    using as_function_t = std::function<ReturnType(Args...)>;
};

template <typename ReturnType, typename... Args>
struct reg_function_traits {
    static constexpr auto arity = sizeof...(Args);

    using result_type           = ReturnType;
    static constexpr auto valid = true;

    template <size_t i>
    struct arg {
        using type = decltype(std::get<i>(std::tuple<Args...>()));
    };

    template <size_t i>
    using arg_t = typename arg<i>::type;

    using as_function_t = std::function<ReturnType(Args...)>;
};

}  // namespace detail

// no types defined
template <typename T, typename = void, typename = void>
struct function_traits {
    static constexpr auto valid = false;
};

// generic functions
template <typename T>
struct function_traits<
        T,
        std::enable_if_t<std::is_class<T>::value>,
        std::enable_if_t<is_callable_object_v<T>>>
    : public function_traits<decltype(&T::operator())> {};

template <typename T>
struct function_traits<T, std::enable_if_t<std::is_reference<T>::value>>
    : public function_traits<typename std::remove_reference_t<T>> {};

// const member functions
template <typename ReturnType, typename ClassType, typename... Args>
struct function_traits<
        ReturnType (ClassType::*)(Args...) const,
        std::enable_if_t<std::is_member_function_pointer<ReturnType (
                ClassType::*)(Args...)>::value>>
    : public mem_function_traits<ReturnType, ClassType, Args...> {};

// member functions
template <typename ReturnType, typename ClassType, typename... Args>
struct function_traits<
        ReturnType (ClassType::*)(Args...),
        std::enable_if_t<std::is_member_function_pointer<ReturnType (
                ClassType::*)(Args...)>::value>>
    : public mem_function_traits<ReturnType, ClassType, Args...> {};

// regular functions
template <typename ReturnType, typename... Args>
struct function_traits<
        ReturnType(Args...),
        std::enable_if_t<std::is_function<ReturnType(Args...)>::value>>
    : public reg_function_traits<ReturnType, Args...> {};

// is_callable

template <typename T>
struct is_callable
    : public std::integral_constant<bool, function_traits<T>::valid> {};

// result_of

template <typename T>
struct result_of {
    using type = std::result_of_t<T>;
};

template <typename R, typename... Args>
struct result_of<R (*)(Args...)> {
    using type = R;
};

template <typename R, typename... Args>
struct result_of<R (&)(Args...)> {
    using type = R;
};

template <typename R, typename C, typename... Args>
struct result_of<R (C::*)(Args...)> {
    using type = R;
};

template <typename R, typename C, typename... Args>
struct result_of<R (C::*)(Args...) const> {
    using type = R;
};

}  // namespace meta
}  // namespace events
