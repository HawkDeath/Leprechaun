#include "Window/Window.h"

#include "Log/Log.h"

namespace Leprechaun {

Window::Window(ApplicationConfig &appConfig)
    : mWindow(nullptr), mAppConfig(appConfig) {
  mWindow =
      glfwCreateWindow(appConfig.windowSize.width, appConfig.windowSize.height,
                       appConfig.title.c_str(), nullptr, nullptr);
  if (!mWindow) {
    ELOG("Failed to create window")
  }
}

Window::~Window() {
  if (mWindow) {
    glfwDestroyWindow(mWindow);
  }
}

} // namespace Leprechaun