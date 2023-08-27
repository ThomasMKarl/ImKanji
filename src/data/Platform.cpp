#include "Platform.hpp"
#include <iostream>
#include <plog/Log.h>
#ifdef WIN32
#include <windows.h>
#endif
#ifdef LINUX
#include <limits.h>
#include <unistd.h>
#endif


namespace imkanji
{
#include "version.cpp"
}

imkanji::PlatformInfo globalPlatformInfoInstance = imkanji::PlatformInfo::nullBehaiviour();

imkanji::PlatformInfo imkanji::PlatformInfo::nullBehaiviour()
{
  PlatformInfo res{};
  res.mInitialWorkingDir = std::filesystem::current_path().string();

#ifdef WIN32
  wchar_t result[MAX_PATH];
  auto path = std::filesystem::path{std::wstring{result, GetModuleFileNameW(nullptr, result, MAX_PATH)}};
#endif
#ifdef LINUX
  char result[PATH_MAX];
  auto count = readlink("/proc/self/exe", result, PATH_MAX);
  auto path = std::filesystem::path{String{result, count > 0 ? static_cast<uint64_t>(count) : 0ULL}};
#endif

  res.mAppDir = path.parent_path().string();
  res.mAppPath = path.string();
  res.mAppName = path.filename().string();

  std::error_code ec{};
  std::filesystem::current_path(res.mAppDir, ec);
  if (ec)
    PLOGW << "cannot change working directory to " << res.mAppDir << "\nerror " << ec.value() << ": " << ec.message();
  else
    PLOGI << "changed working directory to " << res.mAppDir;
  return res;
}

imkanji::PlatformInfo & imkanji::PlatformInfo::instance()
{
  return globalPlatformInfoInstance;
}

imkanji::PlatformInfo & imkanji::PlatformInfo::init(String name, String description)
{
  globalPlatformInfoInstance.mName = std::move(name);
  globalPlatformInfoInstance.mDescription = std::move(description);

  globalPlatformInfoInstance.mReviewNumber = std::atoi(GIT_REV);

  StringView tag{GIT_TAG};
  auto first = tag.find_first_of('.');
  if (first == std::string::npos)
    return globalPlatformInfoInstance;

  globalPlatformInfoInstance.mMajorVersion = std::atoi(tag.substr(0, first).data());
  auto second = tag.find_first_of('.', first);
  if (second == std::string::npos)
    globalPlatformInfoInstance.mMinorVersion = std::atoi(tag.substr(first + 1).data());
  else
  {
    globalPlatformInfoInstance.mMinorVersion = std::atoi(tag.substr(first + 1, second - first).data());
    auto third = tag.find_first_of('.', second);
    if (third == std::string::npos)
      return globalPlatformInfoInstance;
    globalPlatformInfoInstance.mMinorSubVersion = std::atoi(tag.substr(second + 1).data());
  }
  return globalPlatformInfoInstance;
}

imkanji::StringView imkanji::PlatformInfo::gitTag() const
{
  return GIT_TAG;
}

imkanji::StringView imkanji::PlatformInfo::gitRev() const
{
  return GIT_REV;
}

imkanji::StringView imkanji::PlatformInfo::gitBranch() const
{
  return GIT_BRANCH;
}

imkanji::String imkanji::PlatformInfo::serialize() const
{
  std::ostringstream oss{};
  oss << "--- " << mName << (mDescription.empty() ? "" : " - " + mDescription) << " ---\n";
  oss << "    Version: " << mMajorVersion << "." << mMinorVersion << "." << mMinorSubVersion << "\n";
  oss << "    App Name: " << mAppName << "\n";
  oss << "    App Directory: " << mAppDir << "\n";
  oss << "    App Path: " << mAppPath << "\n";
  if constexpr (isDebug())
  {
    oss << "    Revision: " << mReviewNumber << "\n";
    oss << "    GIT_REV: " << GIT_REV << "\n";
    oss << "    GIT_BRANCH: " << GIT_BRANCH << "\n";
    oss << "    GIT_TAG: " << GIT_TAG << "\n";
    oss << "    Initial Working Directory: " << mInitialWorkingDir << "\n";
  }
  oss << "----------\n";
  return oss.str();
}

void imkanji::PlatformInfo::log() const
{
  PLOGI << serialize();
}

void imkanji::PlatformInfo::print() const
{
  std::cout << serialize() << '\n';
}


imkanji::StringView imkanji::trim(const StringView & in)
{
  String whitespaces = "\n\r\t ";
  auto begin = in.find_first_not_of(whitespaces);
  auto end = in.find_last_not_of(whitespaces);
  return StringView{in.data() + begin, end - begin};
}

imkanji::StringView imkanji::trim(const String & in)
{
  String whitespaces = "\n\r\t ";
  auto begin = in.find_first_not_of(whitespaces);
  auto end = in.find_last_not_of(whitespaces);
  return StringView{in.data() + begin, end - begin};
}

imkanji::StringViews imkanji::split(const String & val, char delim, bool trimspace)
{
  String d{delim};
  StringViews res{};
  if (val.empty())
    return res;

  std::size_t begin = 0;
  auto found = 0ULL;
  while (begin < val.size())
  {
    found = val.find_first_of(delim, begin);
    if (found == String::npos)
      found = val.size();
    if (trimspace)
      res.emplace_back(trim(StringView{val.data() + begin, found - begin}));
    else
      res.emplace_back(StringView{val.data() + begin, found - begin});
    begin = found + 1;
  }

  return res;
}

imkanji::Strings imkanji::convert(const StringViews & in)
{
  Strings res{};
  res.reserve(in.size());
  for (const auto & view: in)
    res.emplace_back(view);
  return res;
}

imkanji::StringViews imkanji::toVectorView(const String & in)
{
  return split(in, ',', true);
}

imkanji::Strings imkanji::toVector(const String & in)
{
  return convert(split(in, ',', true));
}

imkanji::String imkanji::toString(const Strings & in)
{
  String res{};
  if (in.empty())
    return res;

  for (const auto & s: in)
    res.append(s + ", ");
  res.pop_back();
  res.pop_back();
  return res;
}

std::filesystem::path imkanji::makeUtf8Path(const StringView & path)
{
  return std::filesystem::path(reinterpret_cast<const char8_t *>(path.data()));
}

uint64_t imkanji::replace(String & in, const StringView & toReplace, const StringView & replace)
{
  uint64_t count{0};
  for (std::string::size_type pos{};
       in.npos != (pos = in.find(toReplace.data(), pos, toReplace.length()));
       pos += replace.length(), ++count)
    in.replace(pos, toReplace.length(), replace.data(), replace.length());
  return count;
}

uint64_t imkanji::getUnixTimeInMS()
{
  return duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

uint64_t imkanji::getUnixTimeInS()
{
  return duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
}

imkanji::String imkanji::getTimestamp(const StringView & fmt)
{
  std::time_t t = std::time(nullptr);
  std::tm tm = *std::localtime(&t);
  std::ostringstream oss{};
  oss << std::put_time(&tm, fmt.data());
  return oss.str();
}

void imkanji::free(void * ptr)
{
  if (ptr)
    std::free(ptr);
}

void imkanji::free(void ** ptr)
{
  if (*ptr)
    std::free(*ptr);
  *ptr = nullptr;
}
