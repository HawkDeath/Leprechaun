#include "BaseApplication.h"
#include <spdlog/spdlog.h>



namespace Leprechaun {

BaseApplication::BaseApplication(int argc, char *argv[]) : mWindow(nullptr) {
  (void)argc;
  (void)argv;
}

BaseApplication::~BaseApplication() { glfwTerminate(); }

bool BaseApplication::initialize() {
  glfwSetErrorCallback([](int error, const char *description) -> void {
    spdlog::error("[GLFW] {}: {}", error, description);
  });
  if (!glfwInit())
    return false;

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  mWindow = glfwCreateWindow(1280, 720, "LeprechaunLib", nullptr, nullptr);

  if (!mWindow) {
    return false;
  }

  glfwMakeContextCurrent(mWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwDestroyWindow(mWindow);
    spdlog::error("Failed to load opengl");
    return false;
  }

}
void BaseApplication::shutdown() { glfwDestroyWindow(mWindow); }

void BaseApplication::run() {
  if (!initialize())
    return;

  onInitialize();

  while (!glfwWindowShouldClose(mWindow)) {

    glfwPollEvents();

    onUpdate(0.0f);

    int display_w, display_h;
    glfwGetFramebufferSize(mWindow, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);

    onDraw();
    glfwSwapBuffers(mWindow);
  }
  onShutdown();
  shutdown();
}

} // namespace Leprechaun