#include <Windows.h>

#include <iostream>

// ウィンドウプロシージャ
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam,
                            LPARAM lParam) {
  if (uMsg == WM_COMMAND)  // WM_COMMANDメッセージが発生した場合
  {
    int wmId = LOWORD(wParam);
    if (HIWORD(wParam) == 1)  // キーが押された場合
    {
      std::string shortcutKey = "";

      if (GetKeyState(VK_CONTROL) < 0)  // Ctrlキーが押された場合
      {
        shortcutKey += "Ctrl+";
      }

      if (GetKeyState(VK_SHIFT) < 0)  // Shiftキーが押された場合
      {
        shortcutKey += "Shift+";
      }

      if (GetKeyState(VK_MENU) < 0)  // Altキーが押された場合
      {
        shortcutKey += "Alt+";
      }

      shortcutKey += char(wmId);

      std::cout << "Shortcut key or accelerator key pressed: " << shortcutKey
                << std::endl;
    }
  } else {
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
  }

  return 0;
}

// WinMain関数
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  // ウィンドウクラスの登録
  WNDCLASSEX wc = {};
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = CS_HREDRAW | CS_VREDRAW;
  wc.lpfnWndProc = WindowProc;
  wc.hInstance = hInstance;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.lpszClassName = "MyWindowClass";
  RegisterClassEx(&wc);

  // ウィンドウの作成
  HWND hwnd = CreateWindowEx(0, "MyWindowClass", "My Window",
                             WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
                             800, 600, NULL, NULL, hInstance, NULL);

  // メニューの作成
  HMENU hMenu = CreateMenu();
  HMENU hFileMenu = CreateMenu();
  AppendMenu(hFileMenu, MF_STRING, 'a', "Ctrl+A");
  AppendMenu(hFileMenu, MF_STRING, 'k', "Alt+Ctrl+K");
  AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, "File");
  SetMenu(hwnd, hMenu);

  // ウィンドウの表示
  ShowWindow(hwnd, nCmdShow);

  // メッセージループを開始する
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}
