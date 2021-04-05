#include "Input/Input.h"
#include "Log/Log.h"

namespace Leprechaun {
Input::Input(GLFWwindow *window)
    : mWindow(window), mMouseMode(InputUtils::CursorMode::Normal),
      mMousePoistion(0.0f, 0.0f), mMouseDeltaValue(0.0f, 0.0f) {
  mKeyEvents.clear();
  mMouseEvents.clear();
  resetMouseState();
  resetKeyboardState();
}

void Input::resetMouseState() noexcept {
  for (auto &button : mInteractMouseButtons) {
    button = InputUtils::KeyState::None;
  }
}

void Input::resetKeyboardState() noexcept {
  for (auto &key : mInteractKeys) {
    key = InputUtils::KeyState::None;
  }
}

void Input::registerKeyEvent(KeyEvent &keyEvent) {
  mKeyEvents.push_back(std::move(keyEvent));
}

void Input::registerMouseEvent(KeyEvent &mouseEvent) {
  mMouseEvents.push_back(std::move(mouseEvent));
}

void Input::update() {
  mMouseDeltaValue = {}; // reset

  updateKeyboard();
  updateMouse();
}

void Input::updateKeyboard() {
  if (mKeyEvents.empty())
    return;

  if (mInteractKeys.empty())
    return;

  for (auto &_event : mKeyEvents) {
    auto isKeyPress = mInteractKeys[static_cast<int>(_event.key)];
    if (InputUtils::TestKeyState(isKeyPress, _event.state)) {
      _event.fn();
    }
  }
  resetKeyboardState();
}

void Input::updateMouse() {
  if (mMouseEvents.empty())
    return;

  if (mInteractMouseButtons.empty())
    return;

  for (auto &_mouseEvent : mMouseEvents) {
    auto isButtonPress =
        mInteractMouseButtons[static_cast<int>(_mouseEvent.button)];
    if (InputUtils::TestKeyState(isButtonPress, _mouseEvent.state)) {
      _mouseEvent.fn();
    }
  }
  resetMouseState();
}

void Input::setCursorMode(InputUtils::CursorMode newMode) {
  if (newMode == mMouseMode || mWindow == nullptr)
    return;

  if (newMode == InputUtils::CursorMode::Normal) {
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
  } else if (newMode == InputUtils::CursorMode::Hided) {
    glfwSetInputMode(mWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  }

  mMouseMode = newMode;
  double xPos, yPos;
  glfwGetCursorPos(mWindow, &xPos, &yPos);

  mMousePoistion = {static_cast<float>(xPos), static_cast<float>(yPos)};
  mMouseDeltaValue = {};
}

void Input::handleKeyInput(int key, int scancode, int action,
                           int mods) noexcept {

  (void)scancode;
  (void)mods;

  auto currState = static_cast<InputUtils::KeyState>(action);
  mInteractKeys[key] = currState;
}

void Input::handleMousePosition(double xPos, double yPos) noexcept {
  glm::vec2 newPosition = {static_cast<float>(xPos), static_cast<float>(yPos)};

  mMouseDeltaValue = newPosition - mMousePoistion;
  mMousePoistion = newPosition;
}

void Input::handleMouseButton(int mouseButton, int action, int mods) noexcept {
  (void)mods;
  auto currentState = static_cast<InputUtils::KeyState>(action);
  mInteractMouseButtons[mouseButton] = currentState;
}

} // namespace Leprechaun