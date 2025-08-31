#pragma once
#include <tuple>
#include <type_traits>

namespace stt {
    template <typename T>
    struct fn_traits;

    template <typename Ret, typename... Args>
    struct fn_traits<Ret(*)(Args...)> {
        using ret_t = Ret;
        using args_t = std::tuple<Args...>;
        static constexpr bool is_member = false;
    };

    template <typename Ret, typename Class, typename... Args>
    struct fn_traits<Ret(Class::*)(Args...)> {
        using ret_t = Ret;
        using class_t = Class;
        using args_t = std::tuple<Args...>;
        static constexpr bool is_member = true;
    };

    template <typename Ret, typename Class, typename... Args>
    struct fn_traits<Ret(Class::*)(Args...) const> {
        using ret_t = Ret;
        using class_t = Class;
        using args_t = std::tuple<Args...>;
        static constexpr bool is_member = true;
    };

    template <typename Lambda>
    struct fn_traits : fn_traits<decltype(&Lambda::operator())> {};

    template <typename Derived, typename Base, typename = void>
    struct extends {
        static constexpr bool value = std::is_base_of_v<Base, Derived>;
        using type = Derived;
    };

    template <typename Derived, typename Base>
    struct extends<Derived, Base, std::enable_if_t<std::is_member_function_pointer_v<Derived>>> {
        using traits = fn_traits<Derived>;
        static_assert(!std::is_void_v<typename traits::class_t>, "Member function pointer must have a class type");
        static constexpr bool value = std::is_base_of_v<Base, typename traits::class_t>;
        using type = Derived;
    };

    template <typename Derived, typename Base>
    using extends_t = typename extends<Derived, Base>::type;

    template <typename Derived, typename Base>
    constexpr bool extends_v = extends<Derived, Base>::value;

    template <typename T, typename = void>
    struct is_callable : std::false_type {};

    template <typename T>
    struct is_callable<T, std::void_t<decltype(&T::operator())>> : std::true_type {};

    template <typename T>
    constexpr bool is_callable_v = is_callable<T>::value;

    template <typename T>
    using ret_type_t = typename fn_traits<T>::ret_t;

    template <typename T>
    using args_type_t = typename fn_traits<T>::args_t;

    template <typename T>
    constexpr bool is_member_callable_v = fn_traits<T>::is_member;
};