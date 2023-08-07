#pragma once
#include <string>
#include <chrono>
#include <concepts>
#include <future>
#include <regex>
#include <any>
#include <optional>
#include <variant>
#include <plog/Log.h>


template<typename E>
  requires std::derived_from<E, std::exception>
std::string stdExceptionToString()
{
  if constexpr (std::is_same_v<E, std::invalid_argument>)
    return "invalid_argument";

  if constexpr (std::is_same_v<E, std::domain_error>)
    return "domain_error";

  if constexpr (std::is_same_v<E, std::length_error>)
    return "length_error";

  if constexpr (std::is_same_v<E, std::out_of_range>)
    return "out_of_range";

  if constexpr (std::is_same_v<E, std::range_error>)
    return "range_error";

  if constexpr (std::is_same_v<E, std::overflow_error>)
    return "overflow_error";

  if constexpr (std::is_same_v<E, std::underflow_error>)
    return "underflow_error";

  if constexpr (std::is_same_v<E, std::future_error>)
    return "future_error"; // (since C++11)

  if constexpr (std::is_same_v<E, std::regex_error>)
    return "regex_error"; // (since C++11)

  if constexpr (std::is_same_v<E, std::bad_array_new_length>)
    return "bad_array_new_length"; // (since C++ 11)

  if constexpr (std::is_same_v<E, std::ios_base::failure>)
    return "ios_base::failure"; // (since C++11)

  if constexpr (std::is_same_v<E, std::filesystem::filesystem_error>)
    return "filesystem::filesystem_error"; //(since C++17)

  if constexpr (std::is_same_v<E, std::system_error>)
    return "system_error"; // (since C++11)

  if constexpr (std::is_same_v<E, std::bad_any_cast>)
    return "bad_any_cast"; // (since C++17)

#if __cplusplus > 202002L
  if constexpr (std::is_same_v<E, std::chrono::nonexistent_local_time>)
    return "chrono::nonexistent_local_time"; // (since C++23)

  if constexpr (std::is_same_v<E, std::chrono::ambiguous_local_time>)
    return "chrono::ambiguous_local_time"; // (since C++23)

  if constexpr (std::is_same_v<E, std::format_error>)
    return "format_error"; //(since C++23)
#endif

  if constexpr (std::is_same_v<E, std::logic_error>)
    return "logic_error";

  if constexpr (std::is_same_v<E, std::runtime_error>)
    return "runtime_error";

  if constexpr (std::is_same_v<E, std::bad_typeid>)
    return "bad_typeid";

  if constexpr (std::is_same_v<E, std::bad_cast>)
    return "bad_cast";

  if constexpr (std::is_same_v<E, std::bad_alloc>)
    return "bad_alloc";

  if constexpr (std::is_same_v<E, std::bad_exception>)
    return "bad_exception";

  if constexpr (std::is_same_v<E, std::bad_weak_ptr>)
    return "bad_weak_ptr"; // (since C++11)

  if constexpr (std::is_same_v<E, std::bad_function_call>)
    return "bad_function_call"; // (since C++11)

  if constexpr (std::is_same_v<E, std::ios_base::failure>)
    return "ios_base::failure"; // (until C++11)

  if constexpr (std::is_same_v<E, std::bad_optional_access>)
    return "bad_optional_access"; // (since C++17)

  if constexpr (std::is_same_v<E, std::bad_variant_access>)
    return "bad_variant_access"; // (since C++17)

#if __cplusplus > 202002L
  if constexpr (std::is_same_v<E, std::bad_expected_access>)
    return "bad_expected_access"; // (since C++23)
#endif

  return "exception";
}

template<typename E>
  requires std::derived_from<E, std::exception>
void logException(const E & e)
{
  LOG_ERROR << "internal error";
  LOG_DEBUG << stdExceptionToString<E>();
  LOG_DEBUG << e.what();
}

#ifndef _STD_CATCH_BLOCK_
#define _STD_CATCH_BLOCK_                 \
  catch (const std::invalid_argument & e) \
  {                                       \
    logException(e);                      \
  }                                       \
  catch (const std::runtime_error & e)    \
  {                                       \
    logException(e);                      \
  }                                       \
  catch (const std::exception & e)        \
  {                                       \
    logException(e);                      \
  }                                       \
  catch (...)                             \
  {                                       \
    LOG_ERROR << "internal error";        \
    LOG_DEBUG << "unexpected exception";  \
  }
#endif
