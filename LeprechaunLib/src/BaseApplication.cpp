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

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mAppConfig.openGlSettings.majorVersion);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mAppConfig.openGlSettings.minorVersion);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mWindow = std::make_unique<Window>(mAppConfig);

  if (!mWindow) {
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