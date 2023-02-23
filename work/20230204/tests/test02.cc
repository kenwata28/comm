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

windows OS で動くプログラムを作ってください。 プログラミング言語は c++ で win32 API
    を使ってください。 それは、バックグラウンドで動くアプリです。 仕様は以下の通りです。 SetWindowsHookEx()
        を使用して、バックグラウンドでも動く。 キーボード入力されたキーを解析し、標準出力する。 ショートカットキーや、アクセラレータキーの入力のようにキー入力が同時に行われた場合、 それがわかるような標準出力になる。 日本語のキーボードレイアウトに対応して、標準出力をおこなう。

    例えば日本語キーボードの