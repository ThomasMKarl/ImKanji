#pragma once
#include "Imgui.hpp"


class Main_MenuBar
{
public:
    Main_MenuBar() = default;

    void draw();

private:
    bool mShowBuildInfo = false;
    bool mShowMetrics = false;
    bool mShowLogging = false;
    bool mShowStyleEditor = false;
};