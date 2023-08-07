#pragma once
#include "Imgui.hpp"


namespace imkanji::menubar
{

class Main
{
public:
  Main() = default;

  void draw();

private:
  bool mShowBuildInfo = false;
  bool mShowMetrics = false;
  bool mShowLogging = false;
  bool mShowStyleEditor = false;
};

} // namespace imkanji::menubar
