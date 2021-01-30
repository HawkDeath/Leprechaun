#include "Input/Input.h"
#include "Log/Log.h"

namespace Leprechaun {
Input::Input(Window *window) : mWindow(window) {
  mKeyEvents.clear();
  for (auto &key : mInteractKeys) {
    key = InputUtils::KeyState::None;
  }
}
void Input::registerKeyEvent(KeyEvent &keyEvent) {
  LOG("[INPUT] Event added \'{0}\'", keyEvent.name)
  mKeyEvents.push_back(std::move(keyEvent));
}

void Input::update() {
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
}

void Input::handleKeyInput(int key, int scancode, int action, int mods) {

  auto currState = static_cast<InputUtils::KeyState>(action);
  mInteractKeys[key] = currState;

  LOG("[INPUT] key {} {}", key, action)
}

void Input::handleMousePosition(double xPos, double yPos) {}

void Input::handleMouseButton(int mouseButton, int action, int mods) {}

} // namespace Leprechaun