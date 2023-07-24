#pragma once
#include "Imgui.hpp"
#include <array>
#include "Platform.hpp"


class Grapheme_Window
{
public:
    void draw(const char* title, bool* p_open = nullptr);

private:
    std::vector<std::string> found{};
    std::array<std::string, 3> selected{};
};