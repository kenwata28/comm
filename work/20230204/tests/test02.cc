#include <windows.h>

#include <iostream>

HHOOK hHook;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode == HC_ACTION) {
    KBDLLHOOKSTRUCT *p = (KBDLLHOOKSTRUCT *)lParam;
    std::cout << "Key " << p->vkCode << " is pressed\n";
  }
  return CallNextHookEx(hHook, nCode, wParam, lParam);
}

int main() {
  hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);
  if (hHook == NULL) {
    std::cout << "Failed to install hook\n";
    return 1;
  }

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hHook);
  return 0;
}
