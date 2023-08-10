#include "AppLauncherWin.hpp"
#include "Unicode.hpp"
#include "plog/Log.h"


[[nodiscard]] wchar_t * imkanji::toWideChar(const char * in)
{
  return toWideChar(in, strlen(in));
}

[[nodiscard]] wchar_t * imkanji::toWideChar(const char * in, uint64_t numElems)
{
  if (in == nullptr)
    return nullptr;

  if (checkUtf8(reinterpret_cast<const utf8char *>(in), numElems) == 0)
  {
    PLOGD << "string is not UTF8 encoded";
    return nullptr;
  }

  auto res = utf8ToWchar(reinterpret_cast<const utf8char *>(in));
  if (res == nullptr)
  {
    PLOGD << "failed to convert UTF8 to Wchar";
    return nullptr;
  }

  return res;
}

[[nodiscard]] char * imkanji::toCChar(const wchar_t * in)
{
  if (in == nullptr)
    return nullptr;

  auto res = wcharToUtf8(in);
  if (res == nullptr)
  {
    PLOGD << "failed to convert Wchar to UTF8";
    return nullptr;
  }

  if (checkUtf8(res, strlenUtf8(res)) == 0)
  {
    PLOGD << "string is not UTF8 encoded";
    return nullptr;
  }

  return reinterpret_cast<char *>(res);
}

imkanji::App::App(std::filesystem::path path) :
    mPathToApp(std::move(path))
{
  mBasePath = mPathToApp;
  mBasePath.remove_filename();
  setupLaunchStructs();
  createPipe();
}

imkanji::App & imkanji::App::operator=(App && rhs) noexcept
{
  if (this == &rhs)
    return *this;
  terminate();
  si = std::move(rhs.si);
  pi = std::move(rhs.pi);
  secAttr = std::move(rhs.secAttr);
  creationFlags = std::move(rhs.creationFlags);
  appStdoutRead = std::move(rhs.appStdoutRead);
  mPathToApp = std::move(rhs.mPathToApp);
  mBasePath = std::move(rhs.mBasePath);
  mLaunchAsyncResult = std::move(rhs.mLaunchAsyncResult);
  return *this;
}

imkanji::App::App(App && rhs) noexcept
{
  if (this == &rhs)
    return;
  terminate();
  si = std::move(rhs.si);
  pi = std::move(rhs.pi);
  secAttr = std::move(rhs.secAttr);
  creationFlags = std::move(rhs.creationFlags);
  appStdoutRead = std::move(rhs.appStdoutRead);
  mPathToApp = std::move(rhs.mPathToApp);
  mBasePath = std::move(rhs.mBasePath);
  mLaunchAsyncResult = std::move(rhs.mLaunchAsyncResult);
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
        PLOGD << "Application \"" << mPathToApp << "\" does not exist";
        return {};
      }
    }
  }

  if (std::filesystem::is_directory(mPathToApp))
  {
    PLOGD << "Application path \"" << mPathToApp << "\" is a directory";
    return {};
  }

  std::string cmd = mPathToApp.string() + extension + " ";

  for (auto & arg: args)
  {
    if (config.quotation)
      cmd.append(std::string{"\""} + arg.data() + "\" ");
    else
      cmd.append(std::string{arg} + " ");
  }

  if (config.requireConsole)
  {
    AllocConsole();
    creationFlags |= DETACHED_PROCESS;
  }
  else
  {
    creationFlags |= CREATE_NO_WINDOW;
  }

  auto help = toWideChar(cmd.c_str());
  auto retval = CreateProcessW(nullptr,       // no module name (use command line)
                               help,          // command line
                               nullptr,       // Process handle not inheritable
                               nullptr,       // Thread handle not inheritable
                               TRUE,          // Set handle inheritance
                               creationFlags, // creation flags
                               nullptr,       // use parents environment block
                               nullptr,       // starting directory
                               &si,           // Pointer to STARTUPINFO struct
                               &pi);          // Pointer to PROCESS_INFORMATION struct

  // Close write end side of the pipe handle to avoid blocking  when child exits
  CloseHandle(appStdoutWrite);
  appStdoutWrite = INVALID_HANDLE_VALUE;

  if (!retval)
  {
    if (help)
      free(help);
    PLOGD << "Could not launch (" << GetLastError() << ") \"" << cmd << "\"";
    return {};
  }

  // Wait until child process exits
  std::string result{};
  if (!config.async)
  {
    DWORD exitCode = STILL_ACTIVE;

    // Get stdout from chiild and write it to my stdout
    HANDLE myStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    // ReadFile terminates on child exit
    char readBuffer[512];
    DWORD numRead = 0;
    DWORD numWritten = 0;
    while (true)
    {
      // Read frompipe
      BOOL readSuccess = ReadFile(appStdoutRead, readBuffer, 512, &numRead, nullptr);
      if ((readSuccess == FALSE) || (numRead == 0))
        break; // child has exited

      // write to stdout
      if (config.toStdOut)
        WriteFile(myStdOut, readBuffer, numRead, &numWritten, nullptr);
      else
        result += readBuffer;
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    GetExitCodeProcess(pi.hProcess, &exitCode);

    if (static_cast<int>(exitCode) < 0 || static_cast<int>(exitCode) > 127)
    {
      PLOGD << "error code " << exitCode << " indicates an error";
    }

    if (help)
      free(help);
  }

  return result;
}

std::unique_ptr<imkanji::App> imkanji::App::launchAsync(std::filesystem::path path, const StringViews & args, const LaunchConfig & config)
{
  auto app = std::unique_ptr<App>{new App{std::move(path)}};
  app->mLaunchAsyncResult = std::async(std::launch::async, &App::execute, app.get(), args, config);
  return app;
}

std::string imkanji::App::getLaunchAsyncResult()
{
  return mLaunchAsyncResult.get();
}

bool imkanji::App::terminate()
{
  bool result = false;
  if (appStdoutRead != INVALID_HANDLE_VALUE)
    result |= CloseHandle(appStdoutRead) == 1;
  result |= CloseHandle(pi.hProcess) == 1;
  result |= CloseHandle(pi.hThread) == 1;
  return result;
}

void imkanji::App::createPipe()
{
  // Create a pipe for getting stderr/stdout communication from child
  secAttr.nLength = sizeof(SECURITY_ATTRIBUTES);
  secAttr.bInheritHandle = TRUE;
  secAttr.lpSecurityDescriptor = nullptr;

  CreatePipe(&appStdoutRead, &appStdoutWrite, &secAttr, 0);
  SetHandleInformation(appStdoutRead, HANDLE_FLAG_INHERIT, 0);
  si.hStdOutput = appStdoutWrite;
  si.hStdError = appStdoutWrite;
}

void imkanji::App::setupLaunchStructs()
{
  ZeroMemory(&si, sizeof(si));
  ZeroMemory(&pi, sizeof(pi));
  ZeroMemory(&secAttr, sizeof(secAttr));

  si.cb = sizeof(si);
  si.lpReserved = nullptr;
  si.lpDesktop = nullptr;
  si.lpTitle = (wchar_t *)L"bash";
  si.dwX = 0;
  si.dwY = 0;
  si.dwXSize = 0;
  si.dwYSize = 0;
  si.dwXCountChars = 0;
  si.dwYCountChars = 0;
  si.dwFillAttribute = 0;
  si.dwFlags = STARTF_USESTDHANDLES;
  si.wShowWindow = 0;
  si.cbReserved2 = 0;
  si.lpReserved2 = nullptr;
  si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
  si.hStdOutput = nullptr;
  si.hStdError = nullptr;
}
