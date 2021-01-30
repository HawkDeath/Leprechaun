#pragma once

#include "InputUtils.h"

#include <functional>
#include <memory>
#include <string>

#include <array>
#include <unordered_map>
#include <utility>

// TODO:
// * mouse button events
// * mouse position update

namespace Leprechaun {

struct KeyEvent {
  std::string name;
  InputUtils::Key key;
  InputUtils::KeyState state;

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

private:
  Input(Window *window);
  void update();

  void handleKeyInput(int key, int scancode, int action, int mods);
  void handleMousePosition(double xPos, double yPos);
  void handleMouseButton(int mouseButton, int action, int mods);

private:
  Window *mWindow;
  std::vector<KeyEvent> mKeyEvents;
  std::array<InputUtils::KeyState, InputUtils::NUM_OF_KEYS> mInteractKeys;
};

} // namespace Leprechaun