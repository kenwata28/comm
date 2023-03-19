#include <windows.h>

#include "IconDisplayer.h"
#include "TimeController.h"
// #include <iostream>

namespace {
HHOOK g_hook;
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
// //
// // main
// //
// HWND hwnd = ::GetConsoleWindow();
HWND hwnd;
HANDLE thread;
ThreadData shared_data;
HINSTANCE hinst;
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void OpenPopupMenu(HWND hwnd, LPARAM lpar);

IconDisplayer idis;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  ::hinst = hInstance;
  // ウィンドウクラスの登録
  WNDCLASS wc;
  ZeroMemory(&wc, sizeof(wc));
  wc.lpfnWndProc = WndProc;
  wc.hInstance = hInstance;
  wc.lpszClassName = TEXT("MyWindowClass");
  RegisterClass(&wc);

  // ウィンドウの作成
  ::hwnd = CreateWindow(TEXT("MyWindowClass"), NULL, WS_OVERLAPPEDWINDOW,
                        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                        CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, CallbackFunc, NULL, 0);
  // メッセージループ
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if (g_hook) UnhookWindowsHookEx(g_hook);

  return (int)msg.wParam;
}

void Creat(HWND hwnd) {
  if (not idis.Init(hwnd)) {
    MessageBox(hwnd, L"Error", L"ERROR in init", 0);
  }

  shared_data.idis = &idis;

  thread = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DisplayRunning,
                        (LPVOID)(&shared_data), 0, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CREATE:
      Creat(hwnd);
      break;

    case IDM_TRAY:
      OpenPopupMenu(hwnd, lParam);
      break;

    case WM_COMMAND:
      // ポップアップメニューのコマンド処理
      if (LOWORD(wParam) == 1) {
        DestroyWindow(hwnd);
      }
      break;

    case WM_DESTROY:
      // MessageBox(hwnd, L"Exit has pushed", L"aa", 0);
      idis.Close();
      PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hwnd, msg, wParam, lParam);
  }
  return 0;
}
HWND CreateEdit(HWND hwndOwner,    // Dialog box handle.
                int x, int y,      // Location.
                HINSTANCE hinst);  // Application or DLL instance.

void OpenPopupMenu(HWND hwnd, LPARAM lpar) {
  switch (lpar) {
    case WM_RBUTTONDOWN: {
      HMENU hPopupMenu = CreatePopupMenu();
      AppendMenu(hPopupMenu, MF_STRING, 1, TEXT("Exit"));
      POINT pt;
      GetCursorPos(&pt);
      TrackPopupMenu(hPopupMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, hwnd, NULL);
      DestroyMenu(hPopupMenu);
    } break;
    case WM_LBUTTONDOWN: {
      POINT pt;
      GetCursorPos(&pt);
      HWND wnd = CreateEdit(hwnd,        // Dialog box handle.
                            pt.x, pt.y,  // Location.
                            ::hinst      // Application or DLL instance.
      );
      if (wnd == NULL) MessageBox(hwnd, L"Error", L"ERROR in init", 0);
      // ShowWindow(wnd, SW_SHOW);

    } break;
  }
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par) {
  const PKBDLLHOOKSTRUCT hook = (PKBDLLHOOKSTRUCT)l_par;

  if (w_par != WM_KEYDOWN or code != HC_ACTION)
    return CallNextHookEx(NULL, code, w_par, l_par);

  const DWORD key = hook->vkCode;

  // if (key == VK_RETURN) {
  if (key == VK_RSHIFT) {
    static int i = 0;
    i = (i + 1) % 3;
    int interval = 100 * i + 50;
    shared_data.interval = interval;
    wchar_t txt[100];
    wsprintf(txt, L"100 x %d + 50 = %d", i, interval);
    idis.SetCmt(std::wstring(txt));
  }

  return CallNextHookEx(NULL, code, w_par, l_par);
}

LRESULT CALLBACK DialogProc(HWND, UINT, WPARAM, LPARAM);

HWND CreateEdit(HWND hwndOwner,   // Dialog box handle.
                int x, int y,     // Location.
                HINSTANCE hinst)  // Application or DLL instance.
{
  // DialogBox(hinst, L"", hwndOwner, (DLGPROC)DialogProc);

  HWND hwndEdit = CreateWindowEx(
      0, TEXT("EDIT"), TEXT("Type here"),
      // ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER |
      // WS_TABSTOP, x, y, ES_MULTILINE | WS_VISIBLE | WS_BORDER
      ES_MULTILINE | WS_VISIBLE | WS_DLGFRAME | WS_CAPTION | WS_SYSMENU, x, y,
      200, 100, hwndOwner, NULL, hinst, NULL);

  MessageBox(hwnd, L"Error", L"ERROR in init", 0);

  return hwndEdit;
}

LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_CLOSE:
      EndDialog(hWnd, IDOK);
      return TRUE;
  }
  return FALSE;
}