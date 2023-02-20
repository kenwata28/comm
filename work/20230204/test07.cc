#include <Windows.h>

#include <iostream>

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int main() {
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
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)lParam;
    if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
      if (kb->vkCode == VK_CONTROL)
        ctrl_pressed = true;
      else if (kb->vkCode == VK_MENU)
        alt_pressed = true;
      else if (kb->vkCode == VK_SHIFT)
        shift_pressed = true;
      else if (ctrl_pressed && kb->vkCode == 'K')
        std::cout << "Ctrl + K" << std::endl;
      else if (alt_pressed && kb->vkCode == 'F')
        std::cout << "Alt + F" << std::endl;
      else if (ctrl_pressed && alt_pressed && shift_pressed &&
               kb->vkCode == 'A')
        std::cout << "Ctrl + Alt + Shift + A" << std::endl;
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
