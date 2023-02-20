#include <Windows.h>

#include <iostream>
#include <vector>

struct Shortcut {
  std::vector<UINT> key_codes;
  bool ctrl = false;
  bool alt = false;
  bool shift = false;
  std::string description;
};

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int main() {
  std::vector<Shortcut> shortcuts{
      {{'K'}, true, false, false, "Ctrl + K"},
      {{'F'}, false, true, false, "Alt + F"},
      {{'A'}, true, true, true, "Ctrl + Alt + Shift + A"}
      // Add more shortcuts as needed
  };

  HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hKeyboardHook);

  return 0;
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  static bool ctrl_pressed = false;
  static bool alt_pressed = false;
  static bool shift_pressed = false;

  if (nCode >= 0) {
    KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
      if (kb->vkCode == VK_CONTROL)
        ctrl_pressed = true;
      else if (kb->vkCode == VK_MENU)
        alt_pressed = true;
      else if (kb->vkCode == VK_SHIFT)
        shift_pressed = true;
      else {
        for (const auto& shortcut : shortcuts) {
          bool match = true;
          for (const auto& key_code : shortcut.key_codes) {
            if (GetAsyncKeyState(key_code) >= 0) {
              match = false;
              break;
            }
          }
          if (match && shortcut.ctrl == ctrl_pressed &&
              shortcut.alt == alt_pressed && shortcut.shift == shift_pressed) {
            std::cout << shortcut.description << std::endl;
            break;
          }
        }
      }
    } else if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
      if (kb->vkCode == VK_CONTROL)
        ctrl_pressed = false;
      else if (kb->vkCode == VK_MENU)
        alt_pressed = false;
      else if (kb->vkCode == VK_SHIFT)
        shift_pressed = false;
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}
