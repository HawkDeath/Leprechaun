#if 0
#include "BaseApplication.h"
#include "Log/Log.h"
#include <spdlog/spdlog.h>


namespace Leprechaun {

  BaseApplication::BaseApplication(int argc, char* argv[],
    ApplicationConfig& appConfig)
    : mWindow{nullptr}, mAppConfig{ appConfig } {
  (void)argc;
  (void)argv;
}

BaseApplication::~BaseApplication() {
  mWindow.release();
  glfwTerminate();
}

bool BaseApplication::initialize() {
  glfwSetErrorCallback([](int error, const char *description) -> void {
    ELOG("[GLFW] {}: {}", error, description);
  });
  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

  mWindow = std::make_unique<Window>(mAppConfig);

  if (!mWindow) {
      ELOG("Failed to create window");
    return false;
  }

  return true;
}
void BaseApplication::shutdown() { }

void BaseApplication::run() {
  if (!initialize())
    return;

  onInitialize();

  auto currentTime = glfwGetTime();
  double deltaTime = currentTime;
  while (!mWindow->shouldClose()) {
    currentTime = glfwGetTime();

    mWindow->update();

    onUpdate(static_cast<float>(deltaTime));

    int display_w, display_h;
    glfwGetFramebufferSize(mWindow->glfwWindow(), &display_w, &display_h);

    onDraw();

    // Rendering

    mWindow->swapBuffer();
    deltaTime = glfwGetTime() - currentTime;
  }
  onShutdown();
  shutdown();
}

} // namespace Leprechaun
#endif