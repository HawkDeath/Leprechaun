#include "BaseApplication.h"
#include "Log/Log.h"
#include <spdlog/spdlog.h>

#include <imgui/backends/imgui_impl_glfw.h>
#include <imgui/backends/imgui_impl_opengl3.h>

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
  

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();

  ImGui::StyleColorsDark();
  const char *glsl_version = "#version 330 core";
  // Setup Platform/Renderer backends
  ImGui_ImplGlfw_InitForOpenGL(mWindow->glfwWindow(), true);
  ImGui_ImplOpenGL3_Init(glsl_version);

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
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x, clear_color.y, clear_color.z, clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    {
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();
    }
    onDraw();

    // Rendering
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    mWindow->swapBuffer();
    deltaTime = glfwGetTime() - currentTime;
  }
  onShutdown();
  shutdown();
}

} // namespace Leprechaun