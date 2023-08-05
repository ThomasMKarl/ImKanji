#include "Exceptions.hpp"


void GlobalErrorHandler::handle(const Error &e) const
{
  setupConsole();
  LOG_ERROR << colorize(e.releaseMessage, AnsiColorF::Red);
  LOG_DEBUG << colorize(e.debugMessage, AnsiColorF::Red);
  restoreConsole();
}

void GlobalErrorHandler::handle(const FatalError &e) const
{
  setupConsole();
  LOG_ERROR << colorize(e.releaseMessage, AnsiColorF::Red);
  LOG_DEBUG << colorize(e.debugMessage, AnsiColorF::Red);
  restoreConsole();
}
