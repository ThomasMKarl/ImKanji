#pragma once
#include "Imgui.hpp"
#include <array>
#include "Platform.hpp"


namespace imkanji::window
{

class Grapheme
{
public:
  void draw(const char * title, bool * p_open = nullptr);

private:
  Strings found{};
  std::array<String, 3> selected{};
};

} // namespace imkanji::window
