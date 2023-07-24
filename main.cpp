#include <plog/Log.h>
#include <plog/Initializers/RollingFileInitializer.h>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include "MainWindow.hpp"
#include "Flashcard.hpp"
#include "Cardbox.hpp"


void initLogging(const char * path)
{
    if (path == nullptr)
        return;

    auto logFile = makeUtf8Path(path);
    if (std::filesystem::exists(logFile))
    {
        if (!std::filesystem::remove(logFile))
        {
            std::cout << "cannot remove old log at \"" << logFile.string() << "\"\n";
            return;
        }
    }
    plog::init(plog::debug, logFile.c_str());
}

int main(int, char**)
{
    initLogging("D:/playground/imgui/qtkanj.log");

    Cardbox::instance("resources/cardbox.json");

    auto mainWindow = Main_Window::createMax("Main Window");
    mainWindow.addFont("resources/fonts/dejavu/DejaVuSans.ttf", 20.0f);
    mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 20.0f);
    mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 30.0f);
    mainWindow.addFont("resources/fonts/kaisei/KaiseiHarunoUmi-Regular.ttf", 100.0f);
    
    setCustomStyle();

    try {
        mainWindow.renderLoop();
    }
    catch (const std::exception & e) {
        std::cout << e.what() << "\n";
        return EXIT_FAILURE;
    }
    catch (...) {
        std::cout << "unknown exception\n";
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
