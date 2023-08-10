#pragma once
#include <future>
#include "Platform.hpp"


namespace imkanji
{

class Pipe
{
public:
  Pipe() = default;

  bool open(const StringView & cmd, const StringView & mode = "r");

  ~Pipe() { close(); }
  Pipe & operator=(const Pipe &) = delete;
  Pipe(const Pipe &) = delete;
  Pipe & operator=(Pipe &&) = default;
  Pipe(Pipe &&) = default;

  std::string get();
  bool flush();
  bool close();

private:
  bool mOpen{false};
  FILE * mHandle{nullptr};
};

struct LaunchConfig
{
  bool quotation{true};
  bool isCommand{false};
  bool requireConsole{false};
  bool toStdOut{false};
  bool async{false};
};

class App
{
public:
  static std::unique_ptr<App> createSyncHandle(std::filesystem::path path, std::filesystem::path workingDir = "/")
  {
    return std::unique_ptr<App>{new App{std::move(path), std::move(workingDir)}};
  }

  ~App() { terminate(); }
  App & operator=(const App &) = delete;
  App(const App &) = delete;
  App & operator=(App &&) = default;
  App(App &&) = default;

  std::string execute(const StringViews & args, const LaunchConfig & config = LaunchConfig{});
  static std::unique_ptr<App> launchAsync(std::filesystem::path path,
                                          const StringViews & args,
                                          const LaunchConfig & config,
                                          std::filesystem::path workingDir = "/");
  std::string getLaunchAsyncResult();
  bool terminate();
  const std::filesystem::path & getPathToApp() const { return mPathToApp; }

private:
  App(std::filesystem::path path, std::filesystem::path workingDir) :
      mPathToApp(std::move(path)), mWorkingDir(std::move(workingDir)), mBasePath(mPathToApp)
  {
    mBasePath.remove_filename();
  }

  Pipe handle{};

  std::filesystem::path mPathToApp{};
  std::filesystem::path mWorkingDir{};
  std::filesystem::path mBasePath{};

  std::future<String> launchAsyncHandle{};
};

} // namespace imkanji
