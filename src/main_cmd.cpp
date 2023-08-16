#include <iostream>
#include <filesystem>
#include "StdExceptions.hpp"
#include "Platform.hpp"
#include "Exceptions.hpp"
#include "CmdConfig.hpp"


void main_cmd()
{
  throw imkanji::Error{"TBI!", "bla"};
}

int main(int argc, const char ** argv)
{
  try
  {
    imkanji::initLogging("qtkanj.log");

    imkanji::PlatformInfo::init("ImKanji", "Kanji Training with ImGui");
    imkanji::CmdConfig::init(argc, argv);
    imkanji::PlatformInfo::instance().print();

    imkanji::timedCout("starting...");

    main_cmd();
  }
  catch (const imkanji::BaseError & e)
  {
    PLOGI << "blub";
    e.handle(imkanji::GlobalErrorHandler::instance());
  }
  _STD_CATCH_BLOCK_

  imkanji::timedCout("shutting down...");

  return EXIT_SUCCESS;
}
