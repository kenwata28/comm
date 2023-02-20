#include <Windows.h>

HHOOK g_keyboardHook = NULL;

// キーボード入力を変換する関数
LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode == HC_ACTION) {
    // キーイベントの情報を取得
    KBDLLHOOKSTRUCT* pKeyInfo = (KBDLLHOOKSTRUCT*)lParam;

    // Ctrl + S が入力された場合
    if (pKeyInfo->vkCode == 'S' && GetAsyncKeyState(VK_CONTROL) < 0) {
      // Alt + Tab を送信
      keybd_event(VK_MENU, 0, 0, 0);
      keybd_event(VK_TAB, 0, 0, 0);
      keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);
      keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
      return 1;
    }
  }

  // 次のフックプロシージャに処理を渡す
  return CallNextHookEx(g_keyboardHook, nCode, wParam, lParam);
}

int main() {
  // キーボードフックを設定
  g_keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

  // メッセージループを開始
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // フックを解除
  UnhookWindowsHookEx(g_keyboardHook);

  return 0;
}
