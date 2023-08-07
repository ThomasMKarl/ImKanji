#pragma once
#include "Imgui.hpp"
#include "Exceptions.hpp"
#include <StbImage.hpp>
#include <stdexcept>
#include <utility>


namespace imkanji::window
{

void setStyleLightDefault();
void setStyleDarkDefault();
void setStyleClassicDefault();
void setCustomStyle();

class Main
{
public:
  static Main create(const std::pair<uint32_t, uint32_t> & size,
                     const char * name,
                     GLFWmonitor * monitor = nullptr,
                     GLFWwindow * share = nullptr);

  static Main createMax(const char * name);

  ImFont & addFont(const char * path, float size);

  GLFWwindow & handle() { return *mMainWindow; }

  void setAsIcon(StbImage & img)
  {
    GLFWimage icon = {static_cast<int>(img.width()), static_cast<int>(img.height()), img.data()};
    glfwSetWindowIcon(mMainWindow, 1, &icon);
  }

  void renderLoop();

  ~Main();

private:
  Main() = default;

  void setupBeforeWindow();

  void setupAfterWindow();

  GLFWwindow * mMainWindow = nullptr;

  class ErrorHandler : public BaseErrorHandler
  {
  public:
    static const ErrorHandler & instance();
    void handle(const Error & e) const override;
    void handle(const FatalError & e) const override;

  private:
    ErrorHandler() = default;
  };
};

} // namespace imkanji::window
