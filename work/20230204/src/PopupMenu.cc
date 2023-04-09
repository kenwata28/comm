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

#include <fstream>
void OutputStatData() {
  // 統計情報を stat.dat に書き出す.
  auto inst = key_type_counting::CountData::GetInstance();
  auto vect = inst->AllStructTypingData();
  std::ofstream ofs("stat.dat");
  ofs << "#key   vk#   total_count   miss_count   miss_rate" << std::endl;
  for (const auto& st : vect) {
    char t[256];
    sprintf(t, "%s  %x  %lld  %lld  %lf\n", g_str_key[st.vkey].c_str(), st.vkey,
            st.total_count, st.miss_count, st.miss_rate);
    ofs << t;
  }
  ofs.close();

  // gunplot を起動。
  system("gnuplot .\\mk_graph\\test.plt");
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
  snprintf(t, sizeof(t),
           "You are likely to make mistakes with the keys \n%s, %s and %s",
           txt[0], txt[1], txt[2]);
  MessageBoxA(hwnd, t, "Display", MB_ICONINFORMATION);
}

void popup_menu::LeftButtonAction(HWND hwnd) {
  POINT pt;
  ::GetCursorPos(&pt);

  Disp(hwnd);
}

void popup_menu::RightButtonAction(HWND hwnd) {
  HMENU hpm = ::CreatePopupMenu();
  AppendMenu(hpm, MF_STRING, ID_OUTPUT_STAT, TEXT("統計情報を出力(&S)"));
  AppendMenu(hpm, MF_STRING, ID_DISP,
             TEXT("ミスタイプしやすいKEYを教えて(&T)"));
  AppendMenu(hpm, MF_SEPARATOR, 0, NULL);
  AppendMenu(hpm, MF_STRING, ID_CLOSE, TEXT("閉じる(&Q)"));
  AppendMenu(hpm, MF_SEPARATOR, 0, NULL);
  AppendMenu(hpm, MF_STRING, ID_EXIT, TEXT("トレイを閉じる。"));
  POINT pt;
  ::GetCursorPos(&pt);
  ::SetForegroundWindow(hwnd);  // ほかの場所クリックやescで popup を閉じるため.
  int cmd = ::TrackPopupMenu(hpm, TPM_RETURNCMD | TPM_RIGHTBUTTON, pt.x, pt.y,
                             0, hwnd, NULL);

  switch (cmd) {
    case (ID_CLOSE):
      ::PostMessage(hwnd, WM_CLOSE, 0, 0);
      break;
    case (ID_EXIT):
      ::SendMessage(hwnd, WM_CANCELMODE, 0, 0);
      break;
    case (ID_OUTPUT_STAT):
      OutputStatData();
      break;
    case (ID_DISP):
      Disp(hwnd);
      break;
    default:
      break;
  }

  ::DestroyMenu(hpm);
}
