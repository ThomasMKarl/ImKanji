#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>
#include <filesystem>
#include "StdExceptions.hpp"
#include "Platform.hpp"
#include "Exceptions.hpp"
#include "CmdConfig.hpp"


void initLogging(const std::string_view & path)
{
  if (path.empty())
    return;

  auto logFile = imkanji::makeUtf8Path(path.data());
  if (std::filesystem::exists(logFile))
  {
    if (!std::filesystem::remove(logFile))
    {
      LOG_ERROR << "cannot remove old log at \"" << logFile.string() << "\"\n";
      return;
    }
  }
  plog::init(plog::debug, logFile.c_str());
}

void main_cmd()
{
  std::cout << "TBI!\n";
}

int main(int argc, const char ** argv)
{
  try
  {
    initLogging("qtkanj.log");

    imkanji::CmdConfig::init(argc, argv);

    main_cmd();
  }
  catch (const BaseError & e)
  {
    e.handle(GlobalErrorHandler::instance());
  }
  _STD_CATCH_BLOCK_

  return EXIT_SUCCESS;
}
