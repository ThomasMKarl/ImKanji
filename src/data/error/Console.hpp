#pragma once

#include <string>

enum class AnsiColorF
{
  None = 0,
  Black = 30,
  Red = 31,
  Green = 32,
  Yellow = 33,
  Blue = 34,
  Magenta = 35,
  Cyan = 36,
  White = 37
};

enum class AnsiColorB
{
  None = 0,
  Black = 40,
  Red = 41,
  Green = 42,
  Yellow = 43,
  Blue = 44,
  Magenta = 45,
  Cyan = 46,
  White = 47
};

void setupConsole();
void restoreConsole();
void addBreaks(std::string & in);
std::string colorize(const std::string & in, AnsiColorF foreground, AnsiColorB background = AnsiColorB::None);
std::string & colorize(std::string & in, AnsiColorF foreground, AnsiColorB background);
