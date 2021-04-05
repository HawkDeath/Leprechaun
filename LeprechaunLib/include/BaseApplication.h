#pragma once
// clang-format off
#include <glad/glad.h>
// clang-format on

#include "Window/ApplicationConfig.h"
#include "Window/Window.h"

#include <GLFW/glfw3.h>
#include <imgui.h>

#include <memory>

namespace Leprechaun {
class BaseApplication {
public:
  explicit BaseApplication() = default;
  explicit BaseApplication(int argc, char *argv[],
                           ApplicationConfig &appConfig);
  ~BaseApplication();

  void run();

protected:
  virtual void onInitialize() {}
  virtual void onShutdown() {}
  virtual void onUpdate(const float &delta) {(void)delta;}
  virtual void onDraw() {}

protected:
  std::unique_ptr<Window> mWindow;
  ApplicationConfig mAppConfig;
  ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

private:
  bool initialize();
  void shutdown();
};

} // namespace Leprechaun

#define IMPLEMENT_DEMO(application)                                            \
  int main(int argc, char *argv[]) {                                           \
    std::unique_ptr<application> app =                                         \
        std::make_unique<application>(argc, argv);                             \
    app->run();                                                                \
    return 0;                                                                  \
  }
