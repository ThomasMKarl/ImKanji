#include "Imgui.hpp"
#include <stdexcept>


void pushFont(uint64_t index)
{
    auto & io = ImGui::GetIO();
    auto numOfFonts = io.Fonts->Fonts.Size;
    if (index >= static_cast<uint64_t>(numOfFonts))
        throw std::runtime_error("got only " + std::to_string(numOfFonts) + " fonts");

    ImFont* font = io.Fonts->Fonts[index];
    ImGui::PushFont(font);
}

void scaleFont(float factor)
{
    ImGui::PushItemWidth(ImGui::GetFontSize() * factor);
}
