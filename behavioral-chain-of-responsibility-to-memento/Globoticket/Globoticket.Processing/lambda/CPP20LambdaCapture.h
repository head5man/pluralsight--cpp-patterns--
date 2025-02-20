#pragma once


template<typename Function>
struct function_traits;

template <typename Ret, typename... Args>
struct function_traits<Ret(Args...)> {
  typedef Ret(*ptr)(Args...);
};

template <typename Ret, typename... Args>
struct function_traits<Ret(* const)(Args...)> : function_traits<Ret(Args...)> {};

template <typename Cls, typename Ret, typename... Args>
struct function_traits<Ret(Cls::*)(Args...) const> : function_traits<Ret(Args...)> {};

using voidfun = void(*)();

template <typename F>
voidfun lambda_to_void_function(F lambda) {
  static auto lambda_copy = lambda;

  return []() {
    lambda_copy();
    };
}

// requires C++20
template <typename F>
auto lambda_to_pointer(F lambda) -> typename function_traits<decltype(&F::operator())>::ptr {
  static auto lambda_copy = lambda;

  return[]<typename... Args>(Args... args) {
    return lambda_copy(args...);
  };
}