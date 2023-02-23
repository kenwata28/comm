#include <Windows.h>

#include <iostream>

using namespace std;

// ショートカットキーのキーコードを定義する
#define VK_A 0x41
#define VK_K 0x4B

// キーが押されたときのコールバック関数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  // キーイベントの構造体を取得する
  KBDLLHOOKSTRUCT* pKeyboard = (KBDLLHOOKSTRUCT*)lParam;

  if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
    // ショートカットキーの判定
    if (GetAsyncKeyState(VK_CONTROL) & 0x8000 && pKeyboard->vkCode == VK_A) {
      // 現在アクティブなウィンドウのタイトルを取得する
      HWND hwnd = GetForegroundWindow();
      char window_title[256];
      GetWindowText(hwnd, window_title, sizeof(window_title));

      // ショートカットキーとウィンドウタイトルを出力する
      cout << "Ctrl+A"
           << " " << window_title << endl;
    } else if (GetAsyncKeyState(VK_CONTROL) & 0x8000 &&
               GetAsyncKeyState(VK_MENU) & 0x8000 &&
               pKeyboard->vkCode == VK_K) {
      // 現在アクティブなウィンドウのタイトルを取得する
      HWND hwnd = GetForegroundWindow();
      char window_title[256];
      GetWindowText(hwnd, window_title, sizeof(window_title));

      // ショートカットキーとウィンドウタイトルを出力する
      cout << "Ctrl+Alt+K"
           << " " << window_title << endl;
    }
  }

  // 次のフックプロシージャに処理を渡す
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
  // キーボードフックを設定する
  HHOOK hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

  // メッセージループを開始する
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // フックを解除する
  UnhookWindowsHookEx(hook);

  return 0;
}
