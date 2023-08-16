#include "Console.hpp"

#include <iostream>

#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
static HANDLE stdoutHandle;
static DWORD outModeInit;
#endif

void imkanji::setupConsole()
{
#ifdef RELEASE
  return;
#endif
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

void imkanji::restoreConsole()
{
#ifdef RELEASE
  return;
#endif
  std::cout << "\033[0m";
#ifdef _WIN32
  SetConsoleMode(stdoutHandle, outModeInit);
#endif
}

void imkanji::addBreaks(std::string & in)
{
  if (in.back() != '\n')
    in.append("\n");
  if (in.front() != '\n')
    in = std::string{"\n" + in};
}

std::string imkanji::colorize(const std::string & in, AnsiColorF foreground, AnsiColorB background)
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

std::string & imkanji::colorize(std::string & in, AnsiColorF foreground, AnsiColorB background)
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
