#ifndef LEPRECHAUN_INPUTUTILS_H
#define LEPRECHAUN_INPUTUTILS_H

// #include <GLFW/glfw3.h>
#include "glfw/include/GLFW/glfw3.h"

#include <cstdint>
#include <cstdlib>

namespace Leprechaun {
    namespace InputUtils {
        enum class Key : std::int32_t {
            Space = GLFW_KEY_SPACE,
            Apostrophe = GLFW_KEY_APOSTROPHE,
            Comma = GLFW_KEY_COMMA,
            Minus = GLFW_KEY_MINUS,
            Period = GLFW_KEY_PERIOD,
            Slash = GLFW_KEY_SLASH,
            Key_0 = GLFW_KEY_0,
            Key_1 = GLFW_KEY_1,
            Key_2 = GLFW_KEY_2,
            Key_3 = GLFW_KEY_3,
            Key_4 = GLFW_KEY_4,
            Key_5 = GLFW_KEY_5,
            Key_6 = GLFW_KEY_6,
            Key_7 = GLFW_KEY_7,
            Key_8 = GLFW_KEY_8,
            Key_9 = GLFW_KEY_9,
            Semicolon = GLFW_KEY_SEMICOLON,
            Equal = GLFW_KEY_EQUAL,
            A = GLFW_KEY_A,
            B = GLFW_KEY_B,
            C = GLFW_KEY_C,
            D = GLFW_KEY_D,
            E = GLFW_KEY_E,
            F = GLFW_KEY_F,
            G = GLFW_KEY_G,
            H = GLFW_KEY_H,
            I = GLFW_KEY_I,
            J = GLFW_KEY_J,
            K = GLFW_KEY_K,
            L = GLFW_KEY_L,
            M = GLFW_KEY_M,
            N = GLFW_KEY_N,
            O = GLFW_KEY_O,
            P = GLFW_KEY_P,
            Q = GLFW_KEY_Q,
            R = GLFW_KEY_R,
            S = GLFW_KEY_S,
            T = GLFW_KEY_T,
            U = GLFW_KEY_U,
            V = GLFW_KEY_V,
            W = GLFW_KEY_W,
            X = GLFW_KEY_X,
            Y = GLFW_KEY_Y,
            Z = GLFW_KEY_Z,
            LeftBracket = GLFW_KEY_LEFT_BRACKET,
            Backslash = GLFW_KEY_BACKSLASH,
            RightBracket = GLFW_KEY_RIGHT_BRACKET,
            GraveAccent = GLFW_KEY_GRAVE_ACCENT,
            World_1 = GLFW_KEY_WORLD_1,
            World_2 = GLFW_KEY_WORLD_2,
            Escape = GLFW_KEY_ESCAPE,
            Enter = GLFW_KEY_ENTER,
            Tab = GLFW_KEY_TAB,
            Backspace = GLFW_KEY_BACKSPACE,
            Insert = GLFW_KEY_INSERT,
            Delete = GLFW_KEY_DELETE,
            Right = GLFW_KEY_RIGHT,
            Left = GLFW_KEY_LEFT,
            Up = GLFW_KEY_UP,
            Down = GLFW_KEY_DOWN,
            PageUp = GLFW_KEY_UP,
            PageDown = GLFW_KEY_DOWN,
            Home = GLFW_KEY_HOME,
            End = GLFW_KEY_END,
            CapsLock = GLFW_KEY_CAPS_LOCK,
            ScrollLock = GLFW_KEY_SCROLL_LOCK,
            NumLock = GLFW_KEY_NUM_LOCK,
            PrintScreen = GLFW_KEY_PRINT_SCREEN,
            Pause = GLFW_KEY_PAUSE,
            F1 = GLFW_KEY_F1,
            F2 = GLFW_KEY_F2,
            F3 = GLFW_KEY_F3,
            F4 = GLFW_KEY_F4,
            F5 = GLFW_KEY_F5,
            F6 = GLFW_KEY_F6,
            F7 = GLFW_KEY_F7,
            F8 = GLFW_KEY_F8,
            F9 = GLFW_KEY_F9,
            F10 = GLFW_KEY_F10,
            F11 = GLFW_KEY_F11,
            F12 = GLFW_KEY_F12,
            F13 = GLFW_KEY_F13,
            F14 = GLFW_KEY_F14,
            F15 = GLFW_KEY_F15,
            F16 = GLFW_KEY_F16,
            F17 = GLFW_KEY_F17,
            F18 = GLFW_KEY_F18,
            F19 = GLFW_KEY_F19,
            F20 = GLFW_KEY_F20,
            F21 = GLFW_KEY_F21,
            F22 = GLFW_KEY_F22,
            F23 = GLFW_KEY_F23,
            F24 = GLFW_KEY_F24,
            F25 = GLFW_KEY_F25,
            Keypad_0 = GLFW_KEY_KP_0,
            Keypad_1 = GLFW_KEY_KP_1,
            Keypad_2 = GLFW_KEY_KP_2,
            Keypad_3 = GLFW_KEY_KP_3,
            Keypad_4 = GLFW_KEY_KP_4,
            Keypad_5 = GLFW_KEY_KP_5,
            Keypad_6 = GLFW_KEY_KP_6,
            Keypad_7 = GLFW_KEY_KP_7,
            Keypad_8 = GLFW_KEY_KP_8,
            Keypad_9 = GLFW_KEY_KP_9,
            Keypad_Decimal = GLFW_KEY_KP_DECIMAL,
            Keypad_Divide = GLFW_KEY_KP_DIVIDE,
            Keypad_Multiply = GLFW_KEY_KP_MULTIPLY,
            Keypad_Subtract = GLFW_KEY_KP_SUBTRACT,
            Keypad_Add = GLFW_KEY_KP_ADD,
            Keypad_Enter = GLFW_KEY_KP_ENTER,
            Keypad_Equal = GLFW_KEY_KP_EQUAL,
            LeftShift = GLFW_KEY_LEFT_SHIFT,
            LeftCtrl = GLFW_KEY_LEFT_CONTROL,
            LeftAlt = GLFW_KEY_LEFT_ALT,
            LeftSuper = GLFW_KEY_LEFT_SUPER,
            RightShift = GLFW_KEY_RIGHT_SHIFT,
            RightCtrl = GLFW_KEY_RIGHT_CONTROL,
            RightAlt = GLFW_KEY_RIGHT_ALT,
            RightSuper = GLFW_KEY_RIGHT_SUPER,
            Menu = GLFW_KEY_MENU,
            Count = GLFW_KEY_LAST
        };

        enum class KeyState : std::int32_t {
            None = 0xFFFF,
            Up = 0x0000,
            Down = 0x0001,
            Hold = 0x0002
        };

        enum class MouseButton : std::size_t {
            Button1 = GLFW_MOUSE_BUTTON_1,
            Button2 = GLFW_MOUSE_BUTTON_2,
            Button3 = GLFW_MOUSE_BUTTON_3,
            Button4 = GLFW_MOUSE_BUTTON_4,
            Button5 = GLFW_MOUSE_BUTTON_5,
            Button6 = GLFW_MOUSE_BUTTON_6,
            Button7 = GLFW_MOUSE_BUTTON_7,
            Button8 = GLFW_MOUSE_BUTTON_8,
            Left = Button1,
            Middle = Button3,
            Right = Button2,
            Count = Button8 + 1,
        };

        enum class CursorMode : std::int8_t {
            Normal, Hided
        };

        inline bool TestKey(const Key &l, const Key &r) noexcept {
            return static_cast<int>(l) == static_cast<int>(r);
        }

        inline bool TestKeyState(const KeyState &l, const KeyState &r) noexcept {
            return static_cast<int>(l) == static_cast<int>(r);
        }

        constexpr size_t NUM_OF_KEYS = static_cast<size_t>(Key::Count);
        constexpr size_t NUM_OF_MOUSE_BUTTONS = static_cast<size_t>(MouseButton::Count);

    } // namespace InputUtils
} // namespace Leprechaun

#endif // LEPRECHAUN_INPUTUTILS_H