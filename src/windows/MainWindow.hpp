#pragma once
#include "Imgui.hpp"
#include <StbImage.hpp>
#include <stdexcept>
#include <utility>


void setStyleLightDefault();
void setStyleDarkDefault();
void setStyleClassicDefault();
void setCustomStyle();

class Main_Window
{
public:
    static Main_Window create(const std::pair<uint32_t, uint32_t> & size, 
                              const char * name,
                              GLFWmonitor * monitor = nullptr,
                              GLFWwindow * share = nullptr);

    static Main_Window createMax(const char * name);

    ImFont & addFont(const char * path, float size);

    GLFWwindow & handle() { return *mMainWindow; }

    void setAsIcon(StbImage & img)
    {    
        GLFWimage icon = { static_cast<int>(img.width()), static_cast<int>(img.height()), img.data() };
        glfwSetWindowIcon(mMainWindow, 1, &icon);
    }

    void renderLoop();

    ~Main_Window();

private:
    Main_Window() = default;

    void setupBeforeWindow();

    void setupAfterWindow();

    GLFWwindow * mMainWindow = nullptr;
};
