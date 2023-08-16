#include <iostream>
#include <stdexcept>
#include <filesystem>
#include "StdExceptions.hpp"
#include "Exceptions.hpp"
#include "MainWindow.hpp"
#include "Flashcard.hpp"
#include "Cardbox.hpp"
#include "CmdConfig.hpp"


void main_gui()
{
/*#ifdef _WIN32
  HWND window;
  AllocConsole();
  window = FindWindowA("ConsoleWindowClass", nullptr);
  ShowWindow(window, imkanji::isDebug() ? 0 : 1);
#endif*/

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
    imkanji::initLogging("qtkanj.log");

    imkanji::PlatformInfo::init("ImKanji", "Kanji Training with ImGui");
    imkanji::CmdConfig::init(argc, argv);
    imkanji::PlatformInfo::instance().log();

    PLOGD << "starting...";

    if (imkanji::CmdConfig::instance().noGui())
      main_cmd();
    else
      main_gui();
  }
  catch (const imkanji::BaseError & e)
  {
    e.handle(imkanji::GlobalErrorHandler::instance());
  }
  _STD_CATCH_BLOCK_

  PLOGD << "shutting down...";

  return EXIT_SUCCESS;
}
