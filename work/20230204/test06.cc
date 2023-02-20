#include <Windows.h>

#include <iostream>

// プロシージャ関数の宣言
LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

// グローバル変数
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nShowCmd) {
  // グローバル変数にインスタンスを設定
  hInst = hInstance;

  // フックを設定
  HHOOK hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);

  // メッセージループを開始
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  // フックを解除
  UnhookWindowsHookEx(hMouseHook);

  return 0;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode >= 0) {
    // マウスのイベントを処理
    switch (wParam) {
      case WM_LBUTTONDOWN:
        std::cout << "Left Click at (" << LOWORD(lParam) << ", "
                  << HIWORD(lParam) << ")" << std::endl;
        break;
      case WM_RBUTTONDOWN:
        std::cout << "Right Click at (" << LOWORD(lParam) << ", "
                  << HIWORD(lParam) << ")" << std::endl;
        break;
      case WM_LBUTTONDBLCLK:
        std::cout << "Left Double Click at (" << LOWORD(lParam) << ", "
                  << HIWORD(lParam) << ")" << std::endl;
        break;
      case WM_RBUTTONDBLCLK:
        std::cout << "Right Double Click at (" << LOWORD(lParam) << ", "
                  << HIWORD(lParam) << ")" << std::endl;
        break;
      default:
        break;
    }
  }

  // 次のフックプロシージャに処理を渡す
  return CallNextHookEx(NULL, nCode, wParam, lParam);
}

#include <Windows.h>

#include <iostream>

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam);

int main() {
  HHOOK hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, NULL, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hMouseHook);

  return 0;
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
  if (nCode >= 0) {
    switch (wParam) {
      case WM_LBUTTONDOWN:
        std::cout << "Left Click" << std::endl;
        break;
      case WM_RBUTTONDOWN:
        std::cout << "Right Click" << std::endl;
        break;
      case WM_LBUTTONDBLCLK:
        std::cout << "Left Double Click" << std::endl;
        break;
      case WM_RBUTTONDBLCLK:
        std::cout << "Right Double Click" << std::endl;
        break;
      default:
        break;
    }
  }

  return CallNextHookEx(NULL, nCode, wParam, lParam);
}
