#ifndef ICON_DISPLAYER_H_
#define ICON_DISPLAYER_H_

#include <windows.h>

#include <string>
#include <vector>

const int IDM_TRAY = 100;

class IconDisplayer {
 public:
  IconDisplayer(){};
  IconDisplayer(HWND hwnd){
      // MessageBox(hwnd, L"open icon display", L"icon display", 0);
  };
  ~IconDisplayer(){};

  inline BOOL Init(HWND hwnd);
  inline BOOL Close();
  inline BOOL SwitchFrame();
  void SetCmt(const std::wstring& txt) { lstrcpy(data_.szTip, txt.c_str()); }

 private:
  inline BOOL ModifyIconFromFile(int index);

  /// @brief 引数 dir に ある ico file の名前を返す。
  /// @example { L"./figs/01.ico", L"./figs/02.ico", L"./figs/03.ico"} を返す。
  std::vector<std::wstring> LoadIcoFileNames(std::wstring dir) const;

  HWND hwnd_;
  std::vector<HICON> icons_;
  NOTIFYICONDATA data_;
};

// 今は直接ファイル名を指定しているけど、そのうち dir にある ico
// ファイルを自動で取得するようにする。
inline std::vector<std::wstring> IconDisplayer::LoadIcoFileNames(
    std::wstring dir) const {
  std::vector<std::wstring> fnames = {L"01.ico", L"02.ico", L"03.ico",
                                      L"04.ico", L"05.ico", L"06.ico",
                                      L"07.ico", L"08.ico", L"09.ico"};
  for (auto& fname : fnames) fname = dir + fname;
  return fnames;
}

inline BOOL IconDisplayer::Close() {
  Shell_NotifyIcon(NIM_DELETE, &data_);
  for (auto& icon : icons_) {
    DestroyIcon(icon);
  }
  return TRUE;
}

inline BOOL IconDisplayer::Init(HWND hwnd) {
  hwnd_ = hwnd;
  // Set icons
  auto fnames = LoadIcoFileNames(L"./neko/");
  for (auto fname : fnames) {
    HICON h_icon = (HICON)LoadImage(NULL, fname.c_str(), IMAGE_ICON, 16, 16,
                                    LR_LOADFROMFILE | LR_SHARED);
    if (h_icon == nullptr) MessageBox(hwnd_, L"Error", L"Error", 0);

    icons_.push_back(h_icon);
  }

  // set NotifyIconData
  ZeroMemory(&data_, sizeof(NOTIFYICONDATA));
  data_.cbSize = sizeof(NOTIFYICONDATA);
  data_.hWnd = hwnd_;
  data_.uID = 1;
  data_.uCallbackMessage = IDM_TRAY;
  data_.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE;
  lstrcpy(data_.szTip, L"nyan");
  data_.hIcon = icons_.front();

  return Shell_NotifyIcon(NIM_ADD, &data_);
}

inline BOOL IconDisplayer::ModifyIconFromFile(int index) {
  data_.hIcon = icons_[index];
  // lstrcpy(data_.szTip, cmt_.c_str());
  BOOL ret = Shell_NotifyIcon(NIM_MODIFY, &data_);
  return ret;
}

inline BOOL IconDisplayer::SwitchFrame() {
  static int index = 0;

  BOOL ret = ModifyIconFromFile(index);
  index++;
  index %= icons_.size();
  return ret;
}
#endif  // ICON_DISPLAYER_H_