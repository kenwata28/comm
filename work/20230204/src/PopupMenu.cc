#include "PopupMenu.h"

#include "KeyNames.h"
#include "MemoryMappedFile.h"
// using namespace popup_menu;

void popup_menu::Open(HWND hwnd, LPARAM lpar) {
  switch (lpar) {
    case WM_RBUTTONDOWN:
      RightButtonAction(hwnd);
      break;
    case WM_LBUTTONDOWN:
      LeftButtonAction(hwnd);
      break;
    default:
      break;
  }
}

// void popup_menu::Cmd(HWND hwnd, WPARAM wpar) {
// }

void popup_menu::RightButtonAction(HWND hwnd) {
  HMENU hpm = ::CreatePopupMenu();
  AppendMenu(hpm, MF_STRING, ID_CLOSE, TEXT("Close"));
  AppendMenu(hpm, MF_STRING, ID_EXIT, TEXT("Quit"));
  POINT pt;
  ::GetCursorPos(&pt);
  SetForegroundWindow(hwnd);  // ほかの場所クリックやescで popup を閉じるため.
  int cmd = ::TrackPopupMenu(hpm, TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y,
                             0, hwnd, NULL);

  switch (cmd) {
    case (ID_CLOSE):
      ::PostMessage(hwnd, WM_CLOSE, 0, 0);
      break;
    case (ID_EXIT):
      ::SendMessage(hwnd, WM_CANCELMODE, 0, 0);
      break;
    default:
      break;
  }

  ::DestroyMenu(hpm);
}

void Disp(HWND hwnd) {
  auto a = key_type_counting::CountData::GetInstance();
  char txt[3][256];
  for (int i = 0; i < 3; i++) {
    double rate;
    long long total_count, miss_count;
    int key = 0;
    if (a == nullptr) {
      MessageBoxA(hwnd, "Error in disp()", "Error", MB_ICONINFORMATION);
      exit(1);
    }
    key = a->TopMissKey(i, &rate, &total_count, &miss_count);
    //    sprintf(txt[i],
    //            "ranking %d : key(%d) = %s; rate : %.2lf, totol: %lld, miss:
    //            %lld", i + 1, key, g_str_key[key].c_str(), rate, total_count,
    //            miss_count);
    sprintf(txt[i], "%s", g_str_key[key].c_str());
  }
  char t[1024];
  sprintf(t, "The keys with the most mistakes are\n%s, %s and %s", txt[0],
          txt[1], txt[2]);
  MessageBoxA(hwnd, t, "miss", MB_ICONINFORMATION);
}

void popup_menu::LeftButtonAction(HWND hwnd) {
  POINT pt;
  ::GetCursorPos(&pt);

  Disp(hwnd);
}

// HWND CreateEdit(HWND hwndOwner,   // Dialog box handle.
//                 int x, int y,     // Location.
//                 HINSTANCE hinst)  // Application or DLL instance.
// {
//   // DialogBox(hinst, L"", hwndOwner, (DLGPROC)DialogProc);
//   HWND hwndEdit = CreateWindowEx(
//       0, TEXT("EDIT"), TEXT("Type here"),
//       // ES_MULTILINE | WS_VISIBLE | WS_CHILD | WS_BORDER |
//       // WS_TABSTOP, x, y, ES_MULTILINE | WS_VISIBLE | WS_BORDER
//       ES_MULTILINE | WS_VISIBLE | WS_DLGFRAME | WS_CAPTION | WS_SYSMENU, x,
//       y, 200, 100, hwndOwner, NULL, hinst, NULL);
//   return hwndEdit;
// }

// LRESULT CALLBACK DialogProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM
// lParam) {
//   switch (msg) {
//     case WM_CLOSE:
//       ::EndDialog(hWnd, IDOK);
//       return TRUE;
//   }
//   return FALSE;
// }