#include "TimeController.h"

#include <windows.h>

#include <iostream>

namespace
{
  HHOOK g_hook;
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
//
// main
//
HWND hwnd = ::GetConsoleWindow();
HANDLE thread;
ThreadData shared_data(hwnd);

int main()
{

  g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, CallbackFunc, NULL, 0);
  thread = CreateThread(0, 0,
                        (LPTHREAD_START_ROUTINE)DisplayRunning,
                        (LPVOID)(&shared_data), 0, NULL);

  //
  //  message loop
  //
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0) != 0)
  {
    TranslateMessage(&msg);
    DispatchMessageW(&msg);
  }

  //
  // close
  //
  if (g_hook)
    UnhookWindowsHookEx(g_hook);

  return TRUE;
}

LRESULT _stdcall CallbackFunc(int code, WPARAM w_par, LPARAM l_par)
{
  const PKBDLLHOOKSTRUCT hook = (PKBDLLHOOKSTRUCT)l_par;

  if (w_par != WM_KEYDOWN or code != HC_ACTION)
    return CallNextHookEx(NULL, code, w_par, l_par);

  const DWORD key = hook->vkCode;

  if (key == VK_RETURN)
  {
    //     idis.Notify();
  }
  else
  {
    std::cout << "undef key input " << std::endl;
  }

  return CallNextHookEx(NULL, code, w_par, l_par);
}
