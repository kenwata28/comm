#ifndef POPUP_MUNU_H_
#define POPUP_MUNU_H_

#include "Global.h"
#include "windows.h"

namespace popup_menu {

enum { ID_EXIT = 1000, ID_CLOSE };
void Open(HWND hwnd, LPARAM lpar);
void RightButtonAction(HWND hwnd);
void LeftButtonAction(HWND hwnd);
void Cmd(HWND hwnd, WPARAM wpar);

// HWND CreateEdit(HWND hwndOwner,    // Dialog box handle.
//                 int x, int y,      // Location.
//                 HINSTANCE hinst);  // Application or DLL instance.
// MessageBox(hwnd, L"Exit has pushed", L"aa", 0);

}  // namespace popup_menu

#endif  // POPUP_MUNU_H_
