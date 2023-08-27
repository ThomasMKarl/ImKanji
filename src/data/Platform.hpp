#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <filesystem>
#include <cinttypes>
#include <iostream>
#include <chrono>

#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <plog/Initializers/ConsoleInitializer.h>
#include <plog/Record.h>
#include <plog/Util.h>

#ifdef _WIN32
#   define EXPORT __declspec(dllexport)
#else
#   define EXPORT __attribute__ ((visibility ("default")))
#endif


namespace imkanji
{

using String = std::string;
using Strings = std::vector<String>;
using StringView = std::string_view;
using StringViews = std::vector<StringView>;
using Index = uint32_t;
using Indices = std::vector<Index>;

constexpr const char * rfcTimeFormat = "%Y-%m-%dT%H:%M:%SZ";

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
#ifdef RELEASE
  return true;
#else
  return false;
#endif
}

constexpr bool isProfile()
{
#ifdef PROFILE
  return true;
#else
  return false;
#endif
}

enum class Arch
{
  Unknown,
  x86_64,
  x86_32,
  Arm2,
  Arm3,
  Arm4T,
  Arm5,
  Arm6T2,
  Arm6,
  Arm7,
  Arm7A,
  Arm7R,
  Arm7M,
  Arm7S,
  Arm64,
  Mips,
  SuperH,
  PowerPC,
  PpwerPC64,
  Sparc,
  M68k
};

constexpr bool is64bit()
{
#if defined(__x86_64__) || defined(_M_X64)
  return true;
#elif defined(__aarch64__) || defined(_M_ARM64)
  return true;
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
  return true;
#endif
  return false;
}

constexpr bool isArm()
{
#if defined(__ARM_ARCH_2__)
  return true;
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
  return true;
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
  return true;
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
  return true;
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
  return true;
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
  return true;
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return true;
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return true;
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return true;
#elif defined(__ARM_ARCH_7M__)
  return true;
#elif defined(__ARM_ARCH_7S__)
  return true;
#elif defined(__aarch64__) || defined(_M_ARM64)
  return true;
#endif
  return false;
}

constexpr bool isX86()
{
#if defined(__x86_64__) || defined(_M_X64)
  return true;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  return true;
#endif
  return false;
}

constexpr Arch getArchitecture()
{
#if defined(__x86_64__) || defined(_M_X64)
  return Arch::x86_64;
#elif defined(i386) || defined(__i386__) || defined(__i386) || defined(_M_IX86)
  return Arch::x86_32;
#elif defined(__ARM_ARCH_2__)
  return Arch::Arm2;
#elif defined(__ARM_ARCH_3__) || defined(__ARM_ARCH_3M__)
  return Arch::Arm3;
#elif defined(__ARM_ARCH_4T__) || defined(__TARGET_ARM_4T)
  return Arch::Arm4T;
#elif defined(__ARM_ARCH_5_) || defined(__ARM_ARCH_5E_)
  return Arch::Arm5;
#elif defined(__ARM_ARCH_6T2_) || defined(__ARM_ARCH_6T2_)
  return Arch::Arm6T2;
#elif defined(__ARM_ARCH_6__) || defined(__ARM_ARCH_6J__) || defined(__ARM_ARCH_6K__) || defined(__ARM_ARCH_6Z__) || defined(__ARM_ARCH_6ZK__)
  return Arch::Arm6;
#elif defined(__ARM_ARCH_7__) || defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return Arch::Arm7;
#elif defined(__ARM_ARCH_7A__) || defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return Arch::Arm7A;
#elif defined(__ARM_ARCH_7R__) || defined(__ARM_ARCH_7M__) || defined(__ARM_ARCH_7S__)
  return Arch::Arm7R;
#elif defined(__ARM_ARCH_7M__)
  return Arch::Arm7M;
#elif defined(__ARM_ARCH_7S__)
  return Arch::Arm7S;
#elif defined(__aarch64__) || defined(_M_ARM64)
  return Arch::Arm64;
#elif defined(mips) || defined(__mips__) || defined(__mips)
  return Arch::Mips;
#elif defined(__sh__)
  return Arch::SuperH;
#elif defined(__powerpc) || defined(__powerpc__) || defined(__powerpc64__) || defined(__POWERPC__) || defined(__ppc__) || defined(__PPC__) || defined(_ARCH_PPC)
  return Arch::PowerPC;
#elif defined(__PPC64__) || defined(__ppc64__) || defined(_ARCH_PPC64)
  return Arch::PowerPC64;
#elif defined(__sparc__) || defined(__sparc)
  return Arch::Sparc;
#elif defined(__m68k__)
  return Arch::M68k;
#else
  return Arch::Unknown;
#endif
}

class PlatformInfo
{
public:
  static PlatformInfo & instance();
  static PlatformInfo & init(String name, String description = "");

  static PlatformInfo nullBehaiviour();

  uint32_t majorVersion() const { return mMajorVersion; }
  uint32_t minorVersion() const { return mMinorVersion; }
  uint32_t minorSubVersion() const { return mMinorSubVersion; }
  uint32_t reviewVersion() const { return mReviewNumber; }
  StringView gitTag() const;
  StringView gitRev() const;
  StringView gitBranch() const;
  const String & name() const { return mName; }
  const String & description() const { return mDescription; }
  const String & initialWorkingDir() const { return mInitialWorkingDir; }
  const String & appDir() const { return mAppDir; }
  const String & appPath() const { return mAppPath; }
  const String & appName() const { return mAppName; }

  void print() const;
  void log() const;

private:
  PlatformInfo() = default;
  uint32_t mMajorVersion{0};
  uint32_t mMinorVersion{0};
  uint32_t mMinorSubVersion{0};
  uint32_t mReviewNumber{0};
  String mName{"N/A"};
  String mDescription{};
  String mInitialWorkingDir{};
  String mAppDir{};
  String mAppPath{};
  String mAppName{};

  String serialize() const;
};

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

void free(void * ptr);

void free(void ** ptr);

template<typename T>
uint64_t sizeInBytes(uint64_t numOfElems = 1)
{
  using U = std::remove_cvref_t<T>;
  return numOfElems * sizeof(U);
}

template<typename T, typename U = std::remove_cvref_t<T>>
U * malloc(uint64_t count)
{
  auto res = reinterpret_cast<U *>(std::malloc(sizeInBytes<U>(count)));
  if (res)
    return res;
  throw std::bad_alloc{};
}

template<typename T, typename U = std::remove_cvref_t<T>>
U * realloc(T ** in, uint64_t count)
{
  auto res = reinterpret_cast<U *>(std::realloc(*in, sizeInBytes<U>(count)));
  if (res)
    return *res;
  throw std::bad_alloc{};
}

template<typename T, typename U = std::remove_cvref_t<T>>
U * malloc(T ** in, uint64_t count)
{
  if (in)
    return realloc(*in, count);
  else
  {
    *in = malloc<T>(count);
    return *in;
  }
}

uint64_t getUnixTimeInMS();

uint64_t getUnixTimeInS();

String getTimestamp(const StringView & fmt = rfcTimeFormat);

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

template<typename... T>
std::ostringstream timedPrintf(const StringView & format, T... args)
{
  std::ostringstream oss{};

  auto str = makeString(format, args...);
  auto lines = split(str, '\n');
  if (lines.empty())
    return oss;

  auto currentTime = getTimestamp(rfcTimeFormat);
  auto indents = currentTime.size() + 4 * sizeof(char);
  String indent(indents, ' ');

  oss << '[' << currentTime << "]: " << lines.front() << '\n';
  for (auto it = std::begin(lines) + 1; it < std::end(lines); ++it)
    oss << indent << *it << '\n';
  return oss;
}

template<typename... T>
void timedCout(const StringView & format, T... args)
{
  std::cout << timedPrintf(format, args...).str();
}

template<typename... T>
void timedCerr(const StringView & format, T... args)
{
  std::cerr << timedPrintf(format, args...).str();
}

template<typename... T>
void timedClog(const StringView & format, T... args)
{
  std::clog << timedPrintf(format, args...).str();
}

class MessageTimestampFormatter
{
public:
  static plog::util::nstring header()
  {
    return plog::util::nstring();
  }

  static plog::util::nstring format(const plog::Record & record)
  {
    tm t;
    plog::util::localtime_s(&t, &record.getTime().time);
    plog::util::nostringstream ss;

    ss << t.tm_year + 1900 << "-" << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mon + 1 << PLOG_NSTR("-") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_mday << PLOG_NSTR(" ");
    ss << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_hour << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_min << PLOG_NSTR(":") << std::setfill(PLOG_NSTR('0')) << std::setw(2) << t.tm_sec << PLOG_NSTR(".") << std::setfill(PLOG_NSTR('0')) << std::setw(3) << static_cast<int>(record.getTime().millitm) << PLOG_NSTR(" ");
    ss << std::setfill(PLOG_NSTR(' ')) << std::setw(5) << std::left << severityToString(record.getSeverity()) << PLOG_NSTR(" ");
    ss << record.getMessage() << PLOG_NSTR("\n");

    return ss.str();
  }
};

template<std::size_t N>
void initLogging(const char (&path)[N])
{
  StringView pathView = path;
  if (pathView.empty())
    return;
  auto logFile = imkanji::makeUtf8Path(pathView.data());
  if (std::filesystem::exists(logFile))
  {
    if (!std::filesystem::remove(logFile))
    {
      imkanji::timedCerr("cannot remove old log at \"%s\"", logFile.c_str());
      return;
    }
  }

  if constexpr (imkanji::isDebug())
  {
    static plog::RollingFileAppender<plog::TxtFormatter> fileAppender(logFile.c_str());
    static plog::ConsoleAppender<plog::TxtFormatter> consoleAppender{};
    plog::init(plog::debug, &fileAppender).addAppender(&consoleAppender);
  }
  else
  {
    static plog::RollingFileAppender<imkanji::MessageTimestampFormatter> fileAppender(logFile.c_str());
    plog::init(plog::error, &fileAppender);
  }
}

} // namespace imkanji
