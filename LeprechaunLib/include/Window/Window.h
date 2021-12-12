#pragma once

#include "ApplicationConfig.h"
#include "Input/Input.h"

#include <GLFW/glfw3.h>

#include <memory>

namespace Leprechaun {

class Window final {
public:
  Window(ApplicationConfig &appConfig);
  ~Window();

  void update();

  GLFWwindow *glfwWindow() const noexcept { return mWindow; }
  std::shared_ptr<Input> getInput() const noexcept { return mInput; }

  bool shouldClose() const { return glfwWindowShouldClose(mWindow); }
  void swapBuffer() const { glfwSwapBuffers(mWindow); }

private:
  static void handleFramebufferResize(GLFWwindow *window_, int w, int h);
  static void handleWindowResize(GLFWwindow *window_, int w, int h);
  static void handleMinimalize(GLFWwindow *window_, int status);

  // input
  static void handleKeyInput(GLFWwindow *window_, int key, int scancode,
                             int action, int mods);
  static void handleMousePosition(GLFWwindow *window_, double xPos,
                                  double yPos);
  static void handleMouseButton(GLFWwindow *window_, int mouseButton,
                                int action, int mods);

private:
  GLFWwindow *mWindow;
  std::shared_ptr<Input> mInput;
  ApplicationConfig &mAppConfig;
  bool mMinimalized;
};

} // namespace Leprechaun