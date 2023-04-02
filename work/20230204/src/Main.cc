#include <windows.h>

#include <iostream>

#include "Global.h"
#include "InputKeysData.h"
#include "KeyInputLogger.h"
#include "MemoryMappedFile.h"
#include "PopupMenu.h"
#include "TimerForPacedown.h"

namespace {
HHOOK g_hook;
HANDLE thread;
HINSTANCE hinst;
HWND g_hwnd;
ThreadData shared_data;
InputKeysDatas g_type_data_buffer;
KeyInputLogger g_input_key_log;
FileLogger g_level_logger;
// key_type_counting::CountData* g_counter = nullptr;
//  typing_counter::DataBuf g_typing_counter;
}  // namespace

LRESULT _stdcall KeyboardInputProc(int code, WPARAM w_par, LPARAM l_par);
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
DWORD WINAPI DisplayRunning(LPVOID input_data);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  {  // ウィンドウクラスの登録
    WNDCLASS wc;
    ZeroMemory(&wc, sizeof(wc));
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = TEXT("MyWindowClass");
    RegisterClass(&wc);
  }

  // ウィンドウの作成
  ::g_hwnd = CreateWindow(TEXT("MyWindowClass"), NULL, WS_OVERLAPPEDWINDOW,
                          CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                          CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

  ::g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardInputProc, NULL, 0);

  // メッセージループ
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  if (::g_hook) UnhookWindowsHookEx(::g_hook);

  return (int)msg.wParam;
}

const UINT_PTR ID_TIMER_2sec = 99;
const UINT_PTR ID_TIMER_30sec = 111;

void Create(HWND hwnd) {
  // MessageBox(hwnd, L"create", L"create", 0);
  ::shared_data.Init(hwnd);

  if (not ::shared_data.idis->Init(hwnd)) {
    MessageBox(hwnd, L"Error", L"ERROR in init", 0);
  }

  ::thread = ::CreateThread(0, 0, (LPTHREAD_START_ROUTINE)DisplayRunning,
                            (LPVOID)(&::shared_data), 0, NULL);

  ::g_input_key_log = KeyInputLogger();
  ::g_level_logger = FileLogger("level");

  // set timer
  ::SetTimer(hwnd, ID_TIMER_2sec, 2 * 1000, NULL);
  ::SetTimer(hwnd, ID_TIMER_30sec, 30 * 1000, NULL);
}

void PaceDown(ThreadData* share) {
  auto lv = share->level;
  lv->PaceDown();
  // comment
  wchar_t txt[100];
  wsprintf(txt, L"level : %d", lv->Level());
  share->idis->SetCmt(std::wstring(txt));
}

void PaceUpTo(ThreadData* share, int level) {
  auto lv = share->level;
  lv->PaceUpTo(level);
  // comment
  wchar_t txt[100];
  wsprintf(txt, L"level : %d", lv->Level());
  share->idis->SetCmt(std::wstring(txt));
}

// g_type_data の 切り替え機能を入れたい。
int FuncEach2s() {
  InputKeysData* dat = g_type_data_buffer.Data();

  g_type_data_buffer.ToggleData();

  int idx_of_BS = dat->IndexOfBackSpace();
  if (idx_of_BS >= 0) {
    for (int i : dat->DeletedKeys(idx_of_BS)) {
      auto inst = key_type_counting::CountData::GetInstance();
      inst->CountUpMiss(i);
    }
    PaceDown(&shared_data);
    dat->Clear();
    return -1;
  };

  // pace up
  const int lv = dat->Level();
  PaceUpTo(&shared_data, lv);
  dat->Clear();

  return lv;
}

int FuncEach30s(int level) {
  PaceDown(&shared_data);

  // LoggerData
  char line[FileLogger::kMaxSizeOfLine];
  sprintf(line, "%d", level);
  g_level_logger.AppendWithTime(line);

  return 0;
}

void TimerFunc(WPARAM w_par) {
  static int buf_level = 0;
  switch (w_par) {
    case ID_TIMER_2sec:
      // modify buf_level
      {
        int lv = FuncEach2s();
        if (lv > buf_level) buf_level = lv;
        return;
      }

    case ID_TIMER_30sec:
      FuncEach30s(buf_level);
      buf_level = 0;  // reset level
      return;

    default:
      return;
  }
}

void DestroyPopupMenu(HWND hwnd) {
  HMENU hm = GetMenu(hwnd);
  ::DestroyMenu(hm);
  SetMenu(hwnd, NULL);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM w_par, LPARAM l_par) {
  static int max_level = 0;
  switch (msg) {
    case WM_CREATE:
      Create(hwnd);
      break;

    case IDM_TRAY:
      popup_menu::Open(hwnd, l_par);
      break;

    case WM_TIMER:
      TimerFunc(w_par);
      break;

    case WM_COMMAND:
      // MessageBox(hwnd, L"test", L"test", 0);
      break;

    case WM_DESTROY:
      shared_data.idis->Close();
      ::PostQuitMessage(0);
      break;

    default:
      return DefWindowProc(hwnd, msg, w_par, l_par);
  }
  return 0;
}

inline bool KeyDownOrUp(WPARAM w_par) {
  return ((w_par == WM_KEYDOWN || w_par == WM_SYSKEYDOWN) or
          (w_par == WM_KEYUP || w_par == WM_SYSKEYUP));
}

LRESULT _stdcall KeyboardInputProc(int code, WPARAM w_par, LPARAM l_par) {
  // if (w_par != WM_KEYDOWN or code != HC_ACTION)
  // return ::CallNextHookEx(NULL, code, w_par, l_par);

  const PKBDLLHOOKSTRUCT hook = (PKBDLLHOOKSTRUCT)l_par;
  const DWORD key = hook->vkCode;

  if (code >= 0) {
    if (KeyDownOrUp(w_par)) {
      g_input_key_log.LogKeyInput(w_par, key);
    }
    if (w_par == WM_KEYDOWN) {
      auto inst = key_type_counting::CountData::GetInstance();
      inst->CountUpTotal(key);
      InputKeysData* dat = g_type_data_buffer.Data();
      dat->SetKey(key);
    }
  }
  return CallNextHookEx(NULL, code, w_par, l_par);
}

DWORD WINAPI DisplayRunning(LPVOID input_data) {
  auto data = static_cast<ThreadData*>(input_data);

  while (true) {
    data->idis->SwitchFrame();

    // レベルによって表示の間隔を変更.
    const int& lv = data->level->Level();
    const double unit = 15;  // in [msec]
    const double min = 10;   // in [msec]
    const double time_interval = (kLevelMax - lv) * unit + min;
    Sleep(time_interval);
  }
}
