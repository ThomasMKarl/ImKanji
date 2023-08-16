#include "Exceptions.hpp"
#include <iostream>


void imkanji::GlobalErrorHandler::handle(const Error & e) const
{
  setupConsole();
  PLOGE << colorize(e.releaseMessage, AnsiColorF::Red);
  PLOGD << colorize(e.debugMessage, AnsiColorF::Red);
  restoreConsole();
}

void imkanji::GlobalErrorHandler::handle(const FatalError & e) const
{
  setupConsole();
  PLOGE << colorize(e.releaseMessage, AnsiColorF::Red);
  PLOGD << colorize(e.debugMessage, AnsiColorF::Red);
  restoreConsole();
}
