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


namespace imkanji
{

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
  PLOGE << "internal error";
  PLOGD << "name: " << stdExceptionToString<E>();
  PLOGD << "message: " << e.what();
}

} // namespace imkanji

#ifndef _STD_CATCH_BLOCK_
#define _STD_CATCH_BLOCK_                             \
  catch (const std::invalid_argument & e)             \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::domain_error & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::length_error & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::out_of_range & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::range_error & e)                  \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::overflow_error & e)               \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::underflow_error & e)              \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::future_error & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::regex_error & e)                  \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_array_new_length & e)         \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::ios_base::failure & e)            \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::filesystem::filesystem_error & e) \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::system_error & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_any_cast & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::logic_error & e)                  \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::runtime_error & e)                \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_typeid & e)                   \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_cast & e)                     \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_alloc & e)                    \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_exception & e)                \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_weak_ptr & e)                 \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_function_call & e)            \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_optional_access & e)          \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::bad_variant_access & e)           \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (const std::exception & e)                    \
  {                                                   \
    imkanji::logException(e);                         \
  }                                                   \
  catch (...)                                         \
  {                                                   \
    PLOGE << "internal error";                        \
    PLOGD << "unexpected exception";                  \
  }
#endif
