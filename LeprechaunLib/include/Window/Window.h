#pragma once

#include "ApplicationConfig.h"
#include <GLFW/glfw3.h>

namespace Leprechaun {

class Window {
public:
  Window(ApplicationConfig &appConfig);
  ~Window();

  GLFWwindow *glfwWindow() const { return mWindow; }

  bool shouldClose() const { return glfwWindowShouldClose(mWindow); }
  void swapBuffer() const { glfwSwapBuffers(mWindow); }

private:
  GLFWwindow *mWindow;
  ApplicationConfig mAppConfig;
};

} // namespace Leprechaun