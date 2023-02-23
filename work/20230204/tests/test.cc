#include "test.h"

#include <windows.h>

#include <iostream>

namespace {
HHOOK g_hook;
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par);

class IconDisplayer {
 public:
  IconDisplayer(HWND hwnd) : hwnd_{hwnd} {
    LPCSTR fname = "./neko.ico";
    std::cout << fname << std::endl;
    ZeroMemory(&data_, sizeof(NOTIFYICONDATA));
    data_.cbSize = sizeof(NOTIFYICONDATA);
    data_.hWnd = hwnd_;
    data_.uID = 1;
    HICON hIcon = (HICON)LoadImage(NULL, fname, IMAGE_ICON, 16, 16,
                                   LR_LOADFROMFILE | LR_SHARED);
    if (hIcon == nullptr) puts("false");
    data_.hIcon = hIcon;
    data_.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    lstrcpy(data_.szTip, TEXT("nyan !"));

    BOOL ret = Shell_NotifyIcon(NIM_ADD, &data_);
    if (hIcon) DestroyIcon(hIcon);
  }

  BOOL LoadIconFromFile(LPCSTR fname = "./neko.ico") {
    std::cout << fname << std::endl;
    ZeroMemory(&data_, sizeof(NOTIFYICONDATA));
    data_.cbSize = sizeof(NOTIFYICONDATA);
    data_.hWnd = hwnd_;
    data_.uID = 1;
    HICON hIcon = (HICON)LoadImage(NULL, fname, IMAGE_ICON, 16, 16,
                                   LR_LOADFROMFILE | LR_SHARED);
    if (hIcon == nullptr) puts("false");
    data_.hIcon = hIcon;
    data_.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
    lstrcpy(data_.szTip, TEXT("nyan !"));

    BOOL ret = Shell_NotifyIcon(NIM_MODIFY, &data_);
    if (hIcon) DestroyIcon(hIcon);
    return ret;
  }

  BOOL Notify() {
    static int i = 0;
    LPCSTR fname[] = {"./neko.ico", "./a.ico"};
    BOOL ret = LoadIconFromFile(fname[i]);
    i++;
    i %= 2;
    return ret;
  }

 private:
  HWND hwnd_;
  NOTIFYICONDATA data_;
};

//
// main
//
HWND hwnd = ::GetConsoleWindow();
IconDisplayer idis(hwnd);
int main() {
  g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, CallbackFunc, NULL, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) != 0) {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  if (g_hook) UnhookWindowsHookEx(g_hook);

  return TRUE;
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par) {
  const PKBDLLHOOKSTRUCT hook = (PKBDLLHOOKSTRUCT)l_par;

  if (w_par != WM_KEYDOWN or code != HC_ACTION)
    return CallNextHookEx(NULL, code, w_par, l_par);
  const DWORD key = hook->vkCode;
  if (key == VK_RETURN) {
    puts("enter pressed");
    idis.Notify();
  } else if (65 <= key && key <= 90) {
    std::cout << char(key) << " pressed" << std::endl;
  } else {
    std::cout << "undef key input ; " << g_str_key[int(key)] << std::endl;
  }

  return CallNextHookEx(NULL, code, w_par, l_par);
}
