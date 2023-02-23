#include <Windows.h>

#include <iostream>

#include "log_key_input.h"

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);

int main() {
  HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, NULL, 0);

  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0)) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  UnhookWindowsHookEx(hKeyboardHook);

  return 0;
}

inline bool KeyDownOrUp(WPARAM w_par) {
  return ((w_par == WM_KEYDOWN || w_par == WM_SYSKEYDOWN) or
          (w_par == WM_KEYUP || w_par == WM_SYSKEYUP));
}

LRESULT CALLBACK KeyboardProc(int code, WPARAM w_par, LPARAM l_par) {
  if (code >= 0) {
    KBDLLHOOKSTRUCT *kb = (KBDLLHOOKSTRUCT *)l_par;
    if (KeyDownOrUp(w_par)) {
      const auto key = kb->vkCode;
      log_key_input::LogKeyInput(w_par, key);
    }
  }

  return CallNextHookEx(NULL, nCode, w_par, l_par);
}

namespace log_key_input {

class StatusOfModifier {
 public:
  StatusOfModifier()
      : pressed_ctrl(false),
        pressed_alt(false),
        pressed_shift(false),
        pressed_win(false),
        pressed_ctrl_with_key(false),
        pressed_alt_with_key(false),
        pressed_shift_with_key(false),
        pressed_win_with_key(false) {}

  bool pressed_ctrl;
  bool pressed_alt;
  bool pressed_shift;
  bool pressed_win;

  // This is for the case of only modifier key input
  bool pressed_ctrl_with_key;
  bool pressed_alt_with_key;
  bool pressed_shift_with_key;
  bool pressed_win_with_key;
};

// Return string of shortcut based on key and status of
// modifier(StatusOfModifier) e.g.
// - Ctrl + v
// - Alt + space
// - Win + Shift + space
std::string StringOfKeyAppendedModifiers(const StatusOfModifier &st,
                                         const DWORD key) {
  std::string ans;
  if (st.pressed_alt) ans += "Alt + ";
  if (st.pressed_win) ans += "Win + ";
  if (st.pressed_ctrl) ans += "Ctrl + ";
  if (st.pressed_shift) ans += "Shift + ";
  ans += g_str_key[int(key)];
  return ans;
}

// This func assume KeyDownOrUp(w_par) is True.
//
// # 外観
// "A" やら "^" やら、修飾キーを伴う "Ctrl + C" やらをログに出力する。
//
// # 詳細
// ctrl + C のような修飾キーを伴うキー入力に対応するため、
// key が押されてから離されるまで(down - up)の期間 true になる pressed_xxx
// を用意する。(xxxはctrlなど) そして、通常key が押下されたときに、pressed_xxx
// の状態をみて、 (Alt + )(Win + )(Ctrl + )(Shift + )key
// をログに出力(*1)する。(*2) 例えば Alt + tab や、Win + Shift + s などである。
//
// また、Alt, Win　などの修飾キー単体入力の場合に対応するために、
// pressed_xxx_with_key がある。
// 修飾キーが押されて離されるまでの期間に通常キーが入力されたかどうかを判断するフラグである。
// 修飾キーが離されるタイミングで、このフラグが偽の場合は、単体入力だと判断し、ログに出力(*1)する。(*2)
//
//
// # 注意点
// (*1)
// ここではログに出力というのは、
// 正確には "ctrl + C" のような string を Log の関数に渡すという意味。
// Log の関数では、時間を append したり、
// 速度の観点から string を貯めて一気にファイルに追記するかも。。
//
// (*2)
// 実装の方法のために
// 修飾キー単体入力のタイミングと、その他のキー入力のログの出力タイミングは異なる。
// 前者が 離されるタイミングなのに対し、後者は押下のタイミングである。
// どうでもいいんじゃないかなぁ
//
//
// # 問題点
// Alt + win とか、Alt + win + Shift
// とか、修飾キーのみを組み合わせるだけのキー入力には対応していない。
// 使わないとおもうので、無視。
//
void LogKeyInput(const WPARAM w_par, const DWORD key) {
  static StatusOfModifier st;
  // Case of key down and key up
  if (w_par == WM_KEYDOWN || w_par == WM_SYSKEYDOWN) {
    // key down
    if (key == VK_CONTROL) {  // Control
      st.pressed_ctrl = true;
      st.pressed_ctrl_with_key = false;
    } else if (key == VK_MENU) {  // Alt
      st.pressed_alt = true;
      st.pressed_alt_with_key = false;
    } else if (key == VK_SHIFT) {  // Shift
      st.pressed_shift = true;
      st.pressed_shift_with_key = false;
    } else if (key == VK_LWIN or key == VK_RWIN) {  // Windows key
      st.pressed_win = true;
      st.pressed_win_with_key = false;
    } else {
      st.pressed_ctrl_with_key = true;
      st.pressed_alt_with_key = true;
      st.pressed_shift_with_key = true;
      st.pressed_win_with_key = true;
      std::string str = StringOfKeyAppendedModifiers(st, key);
      std::cout << str << std::endl;
    }
  } else {  // when (w_par == WM_KEYUP || w_par == WM_SYSKEYUP)
    // Key up
    if (key == VK_CONTROL) {
      st.pressed_ctrl = false;
      if (not st.pressed_ctrl_with_key) std::cout << "Only Ctrl" << std::endl;
    } else if (key == VK_MENU) {
      st.pressed_alt = false;
      if (not st.pressed_alt_with_key) std::cout << "Only Alt" << std::endl;
    } else if (key == VK_SHIFT) {
      st.pressed_shift = false;
      if (not st.pressed_shift_with_key) std::cout << "Only Shift" << std::endl;
    } else if (key == VK_LWIN or key == VK_RWIN) {
      st.pressed_win = false;
      if (not st.pressed_win_with_key) std::cout << "Only Win" << std::endl;
    }
  }
}
}  // namespace log_key_input
