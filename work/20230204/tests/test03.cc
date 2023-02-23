#include <Windows.h>

#include <iostream>

// WinEventProc関数
void CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd,
                           LONG idObject, LONG idChild, DWORD dwEventThread,
                           DWORD dwmsEventTime) {
  if (event ==
      EVENT_SYSTEM_FOREGROUND)  // アクティブなウィンドウの変更を監視する
  {
    char windowTitle[256];  // ウィンドウタイトルを格納するバッファ
    GetWindowText(hwnd, windowTitle,
                  sizeof(windowTitle));  // ウィンドウタイトルを取得
    std::cout << "Active Window Title: " << windowTitle
              << std::endl;  // タイトルをコンソールに出力
  }
}

int main() {
  // ウィンドウイベントを監視する
  HWINEVENTHOOK hWinEventHook =
      SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, NULL,
                      WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT);

  // メッセージループを開始する
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // ウィンドウイベントのフックを解除する
  UnhookWinEvent(hWinEventHook);

  return 0;
}
