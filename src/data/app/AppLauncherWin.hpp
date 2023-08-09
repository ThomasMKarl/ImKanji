#pragma once
#include <windows.h>
#include <memory>
#include <string>
#include <filesystem>
#include <future>
#include <vector>
#include "Platform.hpp"


namespace imkanji
{

template<uint64_t N>
[[nodiscard]] wchar_t * toWideChar(const char (&in)[N]) { return toWideChar(in, N); }
[[nodiscard]] wchar_t * toWideChar(const char * in);
[[nodiscard]] wchar_t * toWideChar(const char * in, uint64_t numElems);
[[nodiscard]] char * toCChar(const wchar_t * in);

struct LaunchConfig
{
  bool quotation{};
  bool isCommand{};
  bool requireConsole{};
  bool toStdOut{};
  bool async{};
};

class App
{
public:
  static std::unique_ptr<App> createSyncHandle(std::filesystem::path path)
  {
    return std::unique_ptr<App>{new App{std::move(path)}};
  }

  ~App() { terminate(); }
  App & operator=(const App &) = delete;
  App(const App &) = delete;
  App & operator=(App &&) noexcept;
  App(App && rhs) noexcept;

  std::string execute(const StringViews & args, const LaunchConfig & config = {});
  static std::unique_ptr<App> launchAsync(std::filesystem::path path, const StringViews & args, const LaunchConfig & config = {});
  std::string getLaunchAsyncResult();
  bool terminate();
  const std::filesystem::path & getPathToApp() const { return mPathToApp; }

private:
  explicit App(std::filesystem::path path);

  void createPipe();
  void setupLaunchStructs();

  STARTUPINFOW si{};
  PROCESS_INFORMATION pi{};
  SECURITY_ATTRIBUTES secAttr{};
  DWORD creationFlags{NORMAL_PRIORITY_CLASS};
  HANDLE appStdoutRead{INVALID_HANDLE_VALUE};
  HANDLE appStdoutWrite{INVALID_HANDLE_VALUE};

  std::filesystem::path mPathToApp{};
  std::filesystem::path mBasePath{};

  std::future<std::string> mLaunchAsyncResult{};
};

} // namespace imkanji
