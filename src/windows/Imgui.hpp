#pragma once

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif
#include <GLFW/glfw3.h>
#include "imgui/imgui.h"
#include "imgui/imgui_stdlib.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"


class Color
{
public:
  Color(float red, float green, float blue, float alpha = 1.0);

  float red() const { return values[r] * 255.0f; }
  float green() const { return values[g] * 255.0f; }
  float blue() const { return values[b] * 255.0f; }
  float alpha() const { return values[a] * 255.0f; }
  void red(float value) { values[r] = toInt(value); }
  void green(float value) { values[g] = toInt(value); }
  void blue(float value) { values[b] = toInt(value); }
  void alpha(float value) { values[a] = toInt(value); }

  auto imguiValue() const;

private:
  enum c {r, g, b, a};
  uint8_t values[4];

  uint8_t toInt(float value);
};

static Color red{1.0, 0.0, 0.0, 1.0};
static Color green{0.0, 1.0, 0.0, 1.0};
static Color blue{0.0, 0.0, 1.0, 1.0};
static Color white_o{1.0, 1.0, 1.0, 1.0};
static Color black_o{0.0, 0.0, 0.0, 1.0};
static Color white_t{1.0, 1.0, 1.0, 0.0};
static Color black_t{0.0, 0.0, 0.0, 0.0};

void Text(uint64_t index, float scale, const Color & color, const char * fmt, ...);
void pushFont(uint64_t index);
void scaleFont(float factor);
