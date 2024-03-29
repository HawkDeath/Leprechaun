#include "Window/Window.h"

#include "Log/Log.h"

namespace Leprechaun {

Window::Window(ApplicationConfig &appConfig)
    : mWindow(nullptr), mInput(nullptr), mAppConfig(appConfig),
      mMinimalized(false) {
  mWindow =
      glfwCreateWindow(appConfig.windowSize.width, appConfig.windowSize.height,
                       appConfig.title.c_str(), nullptr, nullptr);
  if (!mWindow) {
    ELOG("Failed to create window");
  }
  LOG("GLFW {0}.{1}.{2}", GLFW_VERSION_MAJOR, GLFW_VERSION_MINOR,
      GLFW_VERSION_REVISION);
  LOG("Window size: {0}, {1}", appConfig.windowSize.width,
      appConfig.windowSize.height);

  glfwSetWindowUserPointer(mWindow, this);

  mInput = std::shared_ptr<Input>(new Input(mWindow));

  glfwSetWindowSizeCallback(mWindow, &handleWindowResize);
  glfwSetFramebufferSizeCallback(mWindow, &handleFramebufferResize);
  glfwSetWindowIconifyCallback(mWindow, &handleMinimalize);

  glfwSetKeyCallback(mWindow, &handleKeyInput);
  glfwSetMouseButtonCallback(mWindow, &handleMouseButton);
  glfwSetCursorPosCallback(mWindow, &handleMousePosition);

  glfwGetFramebufferSize(mWindow, &mAppConfig.framebufferSize.width,
                         &mAppConfig.framebufferSize.height);
}

Window::~Window() {
  if (mWindow) {
    LOG("Window shutdown");
    glfwDestroyWindow(mWindow);
  }
}

void Window::update() {
  mInput->update();
  if (mMinimalized) {
    glfwWaitEvents();
  } else {
    glfwPollEvents();
  }
}

void Window::handleFramebufferResize(GLFWwindow *window_, int w, int h) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  window->mAppConfig.framebufferSize.width = w;
  window->mAppConfig.framebufferSize.height = h;
}

void Window::handleWindowResize(GLFWwindow *window_, int w, int h) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  window->mAppConfig.windowSize.width = w;
  window->mAppConfig.windowSize.height = h;
}

void Window::handleMinimalize(GLFWwindow *window_, int status) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  window->mMinimalized = static_cast<bool>(status);
}

// input
void Window::handleKeyInput(GLFWwindow *window_, int key, int scancode,
                            int action, int mods) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  auto input = window->mInput;
  input->handleKeyInput(key, scancode, action, mods);
}

void Window::handleMousePosition(GLFWwindow *window_, double xPos,
                                 double yPos) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  auto input = window->mInput;
  input->handleMousePosition(xPos, yPos);
}

void Window::handleMouseButton(GLFWwindow *window_, int mouseButton, int action,
                               int mods) {
  auto window = reinterpret_cast<Window *>(glfwGetWindowUserPointer(window_));
  auto input = window->mInput;
  input->handleMouseButton(mouseButton, action, mods);
}

} // namespace Leprechaun