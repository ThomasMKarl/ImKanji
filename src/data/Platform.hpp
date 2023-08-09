#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cinttypes>


namespace imkanji
{

using String = std::string;
using Strings = std::vector<String>;
using StringView = std::string_view;
using StringViews = std::vector<StringView>;
using Index = uint32_t;
using Indices = std::vector<Index>;

constexpr bool isDebug()
{
#ifdef DEBUG
  return true;
#else
  return false;
#endif
}

constexpr bool isRelease()
{
  return !isDebug();
}

template<typename T>
bool contains(const std::vector<T> & in, const T & val)
{
  for (const auto & elem: in)
    if (elem == val)
      return true;
  return false;
}

StringView trim(const StringView & in);

StringView trim(const String & in);

StringViews split(const String & val, char delim, bool trimspace = false);

Strings convert(const StringViews & in);

StringViews toVectorView(const String & in);

Strings toVector(const String & in);

String toString(const Strings & in);

std::filesystem::path makeUtf8Path(const StringView & path);

uint64_t replace(String & in, const StringView & toReplace, const StringView & replace);

template<typename... T>
String makeString(const StringView & format, T... args)
{
  auto bytes = std::snprintf(nullptr, 0, format.data(), args...);
  if (bytes < 0)
    return {};
  String res(bytes + 1, 0);
  std::snprintf(res.data(), bytes + 1, format.data(), args...);
  res.erase(res.end() - 1);
  return res;
}

} // namespace imkanji
