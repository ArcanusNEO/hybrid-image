#ifndef _NEOCC_SDK_
#define _NEOCC_SDK_

// C
#ifndef _GLIBCXX_NO_ASSERT
  #include <cassert>
#endif
#include <cctype>
#include <cerrno>
#include <cfloat>
#include <ciso646>
#include <climits>
#include <clocale>
#include <cmath>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <cwchar>
#include <cwctype>

#if __cplusplus >= 201103L
  #include <ccomplex>
  #include <cfenv>
  #include <cinttypes>
  #include <cstdalign>
  #include <cstdbool>
  #include <cstdint>
  #include <ctgmath>
  #include <cuchar>
#endif

// C++
#include <algorithm>
#include <bitset>
#include <complex>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <locale>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <utility>
#include <valarray>
#include <vector>

#if __cplusplus >= 201103L
  #include <array>
  #include <atomic>
  #include <chrono>
  #include <codecvt>
  #include <condition_variable>
  #include <forward_list>
  #include <future>
  #include <initializer_list>
  #include <mutex>
  #include <random>
  #include <ratio>
  #include <regex>
  #include <scoped_allocator>
  #include <system_error>
  #include <thread>
  #include <tuple>
  #include <type_traits>
  #include <typeindex>
  #include <unordered_map>
  #include <unordered_set>
#endif

#if __cplusplus >= 201402L
  #include <shared_mutex>
#endif

#if __cplusplus >= 201703L
  #include <any>
  #include <charconv>
  // #include <execution>
  #include <filesystem>
  #include <memory_resource>
  #include <optional>
  #include <string_view>
  #include <variant>
#endif

#if __cplusplus >= 202002L
  #include <barrier>
  #include <bit>
  #include <compare>
  #include <concepts>
  #if __cpp_impl_coroutine
    #include <coroutine>
  #endif
  #include <latch>
  #include <numbers>
  #include <ranges>
  #include <semaphore>
  #include <source_location>
  #include <span>
  #include <stop_token>
  #include <syncstream>
  #include <version>
#endif

#if __cplusplus > 202002L
  #include <expected>
  #include <spanstream>
  #if __has_include(<stacktrace>)
    #include <stacktrace>
  #endif
  #include <stdatomic.h>
#endif

// customized src

#define gcd (std::__gcd)

template <typename T>
static inline T lcm(const T& x, const T& y) {
  return x / gcd(x, y) * y;
}

template <typename T>
static inline typename std::enable_if<std::is_integral<T>::value, T>::type
lowbit(const T& x) {
  return (x) & (-x);
}

template <typename T>
static inline T square(const T& x) {
  return x * x;
}

template <typename T>
static inline T cube(const T& x) {
  return x * x * x;
}

template <typename T>
static inline typename std::enable_if<std::is_arithmetic<T>::value, T>::type
fast_pow(T __base, long long __exponent) {
  T ans = 1;
  bool r = __exponent < 0;
  if (r) __exponent = -__exponent;
  while (__exponent) {
    if (__exponent & 1) ans *= __base;
    __base *= __base;
    __exponent >>= 1;
  }
  if (r) return (1.0l / ans);
  return ans;
}

template <typename T, typename U>
static inline typename std::enable_if<std::is_integral<T>::value &&
    std::is_integral<U>::value && sizeof(T) >= sizeof(U),
  T>::type
fast_pow(T __base, unsigned long long __exponent, U __modulo) {
  T ans = 1;
  __base %= __modulo;
  while (__exponent) {
    if (__exponent & 1) {
      ans *= __base;
      ans %= __modulo;
    }
    __base *= __base;
    __base %= __modulo;
    __exponent >>= 1;
  }
  return ans;
}

static constexpr uint64_t base10[] = {1ul, 10ul, 100ul, 1000ul, 10000ul,
  100000ul, 1000000ul, 10000000ul, 100000000ul, 1000000000ul, 10000000000ul,
  100000000000ul, 1000000000000ul, 10000000000000ul, 100000000000000ul,
  1000000000000000ul, 10000000000000000ul, 100000000000000000ul,
  1000000000000000000ul, 10000000000000000000ul};

static const auto pil = acos(-1.0l);
static const auto el = exp(1.0l);
static constexpr auto epsl = 1e-8l;

#endif  // _NEOCC_SDK_
