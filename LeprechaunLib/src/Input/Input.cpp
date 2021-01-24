#include "Input/Input.h"
#include "Log/Log.h"

namespace Leprechaun {
Input::Input(Window *window) : mWindow(window) {}

void Input::registerKeyEvent(KeyEvent &keyEvent) {
  auto eventInMap = mKeyEvents.find(keyEvent.name);
  if (eventInMap != mKeyEvents.find(keyEvent.name)) {
    ELOG("{0} has been found", keyEvent.name)
    return;
  }

  for (const auto &i : mKeyEvents) {
    if (TestKey(i.second.key, keyEvent.key)) {
      ELOG("Key {} is in use", keyEvent.key)
      return;
    }
  }
  mKeyEvents.insert(std::make_pair<>(keyEvent.name, keyEvent));
  LOG("Event {} has been added", keyEvent.name)
}

void Input::update() {
  if (mKeyEvents.empty())
    return;

  if (keys.empty())
    return;
  KeyEvent *eventToRun = nullptr;

  auto key = std::find_if(
      keys.begin(), keys.end(),
      [&](std::pair<InputUtils::Key, InputUtils::KeyState> key) -> bool {
        for (auto &i : mKeyEvents) {
          if (TestKey(i.second.key, key.first) &&
              InputUtils::TestKeyState(i.second.state, key.second)) {
            eventToRun = &i.second;
            return true;
          }

          return false;
        }
      });

  if (eventToRun) {
    eventToRun->fn();
  }
}

void Input::handleKeyInput(int key, int scancode, int action, int mods) {
  auto currKey = static_cast<InputUtils::Key>(key);
  auto currState = static_cast<InputUtils::KeyState>(action);

  auto findKey = std::find_if(
      keys.begin(), keys.end(),
      [&](std::pair<InputUtils::Key, InputUtils::KeyState> keyStat) -> bool {
        if (TestKey(keyStat.first, currKey)) {
          return true;
        }
        return false;
      });

  if (findKey != keys.end()) { // has been found
    findKey->second = currState;
    LOG("[INPUT] Update key {} {}", findKey->first, findKey->second)
    return;
  }
  std::pair<InputUtils::Key, InputUtils::KeyState> stat = {currKey, currState};
  keys.push_back(stat);
  LOG("[INPUT] key {} {}", key, action)
}

void Input::handleMousePosition(double xPos, double yPos) {}

void Input::handleMouseButton(int mouseButton, int action, int mods) {}

} // namespace Leprechaun