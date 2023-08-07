#include "Imgui.hpp"
#include <stdexcept>
#include <iostream>


imkanji::Color::Color(float red, float green, float blue, float alpha)
{
  values[r] = toInt(red);
  values[g] = toInt(green);
  values[b] = toInt(blue);
  values[a] = toInt(alpha);
}

auto imkanji::Color::imguiValue() const
{
  return IM_COL32(values[r], values[g], values[b], values[a]);
}

uint8_t imkanji::Color::toInt(float value)
{
  auto one = static_cast<uint8_t>(255);
  auto zero = static_cast<uint8_t>(0);
  return std::min(one, std::max(zero, static_cast<uint8_t>(255 * value)));
}

void imkanji::Text(uint64_t index, float scale, const Color & color, const char * fmt, ...)
{
  pushFont(index);
  scaleFont(scale);
  ImGui::PushStyleColor(ImGuiCol_Text, color.imguiValue());

  va_list args;
  va_start(args, fmt);
  ImGui::Text(fmt, args);
  va_end(args);

  ImGui::PopStyleColor();
  ImGui::PopFont();
  ImGui::PopItemWidth();
}

void imkanji::pushFont(uint64_t index)
{
  auto & io = ImGui::GetIO();
  auto numOfFonts = io.Fonts->Fonts.Size;
  if (index >= static_cast<uint64_t>(numOfFonts))
    throw std::runtime_error("got only " + std::to_string(numOfFonts) + " fonts");

  ImFont * font = io.Fonts->Fonts[index];
  ImGui::PushFont(font);
}

void imkanji::scaleFont(float factor)
{
  ImGui::PushItemWidth(ImGui::GetFontSize() * factor);
}
