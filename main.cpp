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

int main(int, char **)
{
  initLogging("qtkanj.log");

  LOG_INFO << "starting...";

  imkanji::Cardbox::instance("resources/cardbox.json");

  auto mainWindow = imkanji::window::Main::createMax("Main Window");
  mainWindow.addFont("resources/fonts/dejavu/DejaVuSans.ttf", 20.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 20.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 30.0f);
  mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 100.0f);

  imkanji::window::setCustomStyle();

  try
  {
    mainWindow.renderLoop();
  }
  catch (const BaseError & e)
  {
    e.handle(GlobalErrorHandler::instance());
  }
  _STD_CATCH_BLOCK_

  return EXIT_SUCCESS;
}
