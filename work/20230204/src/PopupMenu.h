#ifndef POPUP_MUNU_H_
#define POPUP_MUNU_H_

#include "windows.h"

namespace popup_menu {

enum { ID_EXIT = 1000, ID_CLOSE, ID_OUTPUT_STAT, ID_DISP };
void Open(HWND hwnd, LPARAM lpar);
void RightButtonAction(HWND hwnd);
void LeftButtonAction(HWND hwnd);
void Cmd(HWND hwnd, WPARAM wpar);

}  // namespace popup_menu

#endif  // POPUP_MUNU_H_
