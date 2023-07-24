#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cinttypes>


using String = std::string;
using Strings = std::vector<String>;
using Index = uint32_t;

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

std::string_view trim(const std::string_view & in);

std::string_view trim(const std::string & in);

std::vector<std::string_view> split(const std::string & val, char delim, bool trimspace = false);

Strings convert(const std::vector<std::string_view> & in);

std::vector<std::string_view> toVectorView(const std::string & in);

Strings toVector(const std::string & in);

String toString(const Strings & in);

std::filesystem::path makeUtf8Path(const char * path);

template<typename... T>
String makeString(const char * format, T... args)
{
    auto bytes = std::snprintf(nullptr, 0, format, args...);
    char * buffer = reinterpret_cast<char*>(std::malloc(bytes + 1));
    std::snprintf(buffer, bytes + 1, format, args...);
    String res{buffer};
    free(buffer);
    return res;
}
