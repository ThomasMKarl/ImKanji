#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include "StdExceptions.hpp"
#include "Exceptions.hpp"
#include "MainWindow.hpp"
#include "Flashcard.hpp"
#include "Cardbox.hpp"
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

void main_gui()
{
  LOG_INFO << "starting...";

  imkanji::Cardbox::instance("resources/cardbox.json");

  auto mainWindow = imkanji::window::Main::createMax("Main Window");
  mainWindow.addFont("resources/fonts/dejavu/DejaVuSans.ttf", 20.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 20.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 30.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 100.0f);

  imkanji::window::setCustomStyle();

  mainWindow.renderLoop();
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

    if (imkanji::CmdConfig::instance().noGui())
      main_cmd();
    else
      main_gui();
  }
  catch (const BaseError & e)
  {
    e.handle(GlobalErrorHandler::instance());
  }
  _STD_CATCH_BLOCK_

  return EXIT_SUCCESS;
}
