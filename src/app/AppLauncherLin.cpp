#include "AppLauncherLin.hpp"
#include "LogWindow.hpp"


bool imkanji::Pipe::open(const StringView & cmd, const StringView & mode)
{
  close();
  mHandle = popen(cmd.data(), mode.data());
  if (mHandle)
    mOpen = true;
#ifdef DEBUG
  else
  {
    int help = errno;
    DIMLOG("failed to open pipe (errno %s)", std::strerror(help));
  }
#endif
  return mOpen;
}

bool imkanji::Pipe::flush()
{
  if (mOpen && mHandle)
    return std::fflush(mHandle) == 0;
  return true;
}

std::string imkanji::Pipe::get()
{
  if (!mOpen)
    return {};
  std::string result{};
  char buffer[128];
  while (true)
  {
    auto ret = std::fgets(buffer, sizeof(buffer), mHandle);
    if (!ret)
      break;
    result.append(buffer);
  }
  return result;
}

bool imkanji::Pipe::close()
{
  if (mOpen && mHandle)
  {
    auto ret = pclose(mHandle);
    if (ret >= 0)
      mOpen = false;
#ifdef DEBUG
    else
    {
      int help = errno;
      DIMLOG("failed to close pipe (errno %s)", std::strerror(help));
    }
#endif
  }

  return !mOpen;
}

std::string imkanji::App::execute(const StringViews & args, const LaunchConfig & config)
{
  std::string extension{};
  if (!config.isCommand)
  {
    if (!std::filesystem::exists(mPathToApp))
    {
      extension = ".exe";
      auto newpath = mPathToApp;
      newpath.concat(extension);
      if (!std::filesystem::exists(newpath))
      {
        DIMLOG("Application \"%s\" does not exist", mPathToApp.c_str());
        return {};
      }
    }
  }

  if (std::filesystem::is_directory(mPathToApp))
  {
    DIMLOG("Application path \"%s\" is a directory", mPathToApp.c_str());
    return {};
  }

  if (!std::filesystem::is_directory(mWorkingDir))
  {
    DIMLOG("Working directory \"%s\" is not a directory", mWorkingDir.c_str());
    return {};
  }

  std::string cmd = "cd " + mWorkingDir.string() + " && " + mPathToApp.string() + extension + " ";

  for (auto & arg: args)
  {
    String append = arg.data();
    if (config.quotation)
    {
      
      replace(append, "'", "\"'\"");
      cmd.append("'" + append + "' ");
    }
    else
      cmd.append(append + " ");
  }

  if (!handle.open(cmd.c_str()))
  {
    DIMLOG("failed to open pipe", "");
    return {};
  }

  std::string result = handle.get();

  if (!handle.close())
  {
    DIMLOG("failed to close pipe", "");
  }

  if (config.toStdOut)
  {
    std::printf("%s", result.c_str());
    return {};
  }

  return result;
}

std::unique_ptr<imkanji::App> imkanji::App::launchAsync(std::filesystem::path path,
                                                        const StringViews & args,
                                                        const LaunchConfig & config,
                                                        std::filesystem::path workingDir)
{
  auto app = std::unique_ptr<App>{new App{std::move(path), std::move(workingDir)}};
  app->launchAsyncHandle = std::async(std::launch::async, &App::execute, app.get(), args, config);
  return app;
}

std::string imkanji::App::getLaunchAsyncResult()
{
  return launchAsyncHandle.get();
}

bool imkanji::App::terminate()
{
  return handle.close();
}
