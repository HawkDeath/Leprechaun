#pragma once

#include "InputUtils.h"

#include <glm/glm.hpp>

#include <functional>
#include <memory>
#include <string>

#include <array>
#include <unordered_map>
#include <utility>

namespace Leprechaun {

struct KeyEvent {
  KeyEvent() = default;
  std::string name = "";
  union {
    InputUtils::Key key;
    InputUtils::MouseButton button;
  };
  InputUtils::KeyState state = InputUtils::KeyState::None;

  std::function<void()> fn = nullptr;
};

struct MousePosition {
  double x;
  double y;
};

struct MouseEvent {
  std::string name;
  InputUtils::MouseButton mouseButton;
  std::function<void(MousePosition &)> fn = nullptr;
};

class Input final : public std::enable_shared_from_this<Input> {
  friend class Window;

public:
  void registerKeyEvent(KeyEvent &keyEvent);
  void registerMouseEvent(KeyEvent &mouseEvent);

  void setCursorMode(InputUtils::CursorMode newMode);

  auto getMousePosition() const noexcept { return mMousePoistion; }
  auto getMouseDelta() const noexcept { return mMouseDeltaValue; }

private:
  Input(GLFWwindow *window);
  void update();
  void updateKeyboard();
  void updateMouse();

  void resetMouseState() noexcept;
  void resetKeyboardState() noexcept;

  void handleKeyInput(int key, int scancode, int action, int mods) noexcept;
  void handleMousePosition(double xPos, double yPos) noexcept;
  void handleMouseButton(int mouseButton, int action, int mods) noexcept;

private:
  GLFWwindow *mWindow;

  // Keyboard support
  std::vector<KeyEvent> mKeyEvents;
  std::array<InputUtils::KeyState, InputUtils::NUM_OF_KEYS> mInteractKeys;

  // Mouse support
  std::vector<KeyEvent> mMouseEvents;
  std::array<InputUtils::KeyState, InputUtils::NUM_OF_MOUSE_BUTTONS>
      mInteractMouseButtons;

  InputUtils::CursorMode mMouseMode;

  glm::vec2 mMousePoistion;
  glm::vec2 mMouseDeltaValue;
};

} // namespace Leprechaun