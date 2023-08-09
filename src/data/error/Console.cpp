#include "Console.hpp"

#include <iostream>

#ifdef _WIN32
#ifndef GLOG_NO_ABBREVIATED_SEVERITIES
#define GLOG_NO_ABBREVIATED_SEVERITIES
#endif
#include <windows.h>
#undef ERROR
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
static HANDLE stdoutHandle;
static DWORD outModeInit;
#endif

void setupConsole()
{
#ifdef _WIN32
  DWORD outMode = 0;
  stdoutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

  if (stdoutHandle == INVALID_HANDLE_VALUE)
    return;

  if (!GetConsoleMode(stdoutHandle, &outMode))
    return;

  outModeInit = outMode;
  outMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;

  SetConsoleMode(stdoutHandle, outMode);
#endif
}

void restoreConsole()
{
  std::cout << "\033[0m";
#ifdef _WIN32
  SetConsoleMode(stdoutHandle, outModeInit);
#endif
}

void addBreaks(std::string & in)
{
  if (in.back() != '\n')
    in.append("\n");
  if (in.front() != '\n')
    in = std::string{"\n" + in};
}

std::string colorize(const std::string & in, AnsiColorF foreground, AnsiColorB background)
{
#ifdef DEBUG
  std::string inColored{"\033[" + std::to_string(static_cast<int>(foreground))};
  if (background != AnsiColorB::None)
    inColored.append(";" + std::to_string(static_cast<int>(background)));
  inColored.append("m" + in + "\033[0m");
  return inColored;
#else
  return in;
#endif
}

std::string & colorize(std::string & in, AnsiColorF foreground, AnsiColorB background)
{
#ifdef DEBUG
  std::string inColored{"\033[" + std::to_string(static_cast<int>(foreground))};
  if (background != AnsiColorB::None)
    inColored.append(";" + std::to_string(static_cast<int>(background)));
  inColored.append("m" + in + "\033[0m");
  in = std::move(inColored);
#endif
  return in;
}
