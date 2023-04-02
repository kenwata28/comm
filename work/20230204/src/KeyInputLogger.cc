#include "KeyInputLogger.h"

#include "KeyNames.h"
// Return string of shortcut based on key and status of
// modifier(StatusOfModifier) e.g.
// - Ctrl + v
// - Alt + space
// - Win + Shift + space
std::string KeyInputLogger::StringOfKeyAppendedModifiers(
    const StatusOfModifier& st, const DWORD key) const {
  std::string ans;
  if (st.pressed[kAlt]) ans += "Alt + ";
  if (st.pressed[kWin]) ans += "Win + ";
  if (st.pressed[kCtrl]) ans += "Ctrl + ";
  if (st.pressed[kShift]) ans += "Shift + ";
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
void KeyInputLogger::LogKeyInput(const WPARAM w_par, const DWORD key) {
  // Case of key down and key up
  if (w_par == WM_KEYDOWN || w_par == WM_SYSKEYDOWN) {
    // key down
    if (key == VK_LCONTROL or key == VK_RCONTROL) {  // Control
      st_.pressed[kCtrl] = true;
      st_.pressed_with_key[kCtrl] = false;
    } else if (key == VK_LMENU or key == VK_RMENU) {  // Alt
      st_.pressed[kAlt] = true;
      st_.pressed_with_key[kAlt] = false;
    } else if (key == VK_LSHIFT or key == VK_RSHIFT) {  // Shift
      st_.pressed[kShift] = true;
      st_.pressed_with_key[kShift] = false;
    } else if (key == VK_LWIN or key == VK_RWIN) {  // Windows key
      st_.pressed[kWin] = true;
      st_.pressed_with_key[kWin] = false;
    } else {
      std::string str = StringOfKeyAppendedModifiers(st_, key);
      flog_.AppendWithTime(str.c_str());
      // char txt[256];
      // sprintf(txt, "key: 0x%x, int(%d)", key, int(key));
      // flog_.Append(txt);
      for (auto& p : st_.pressed_with_key) p = true;
    }
  } else {  // when (w_par == WM_KEYUP || w_par == WM_SYSKEYUP)
    // Key up
    if (key == VK_LCONTROL or key == VK_RCONTROL) {
      st_.pressed[kCtrl] = false;
      if (not st_.pressed_with_key[kCtrl]) flog_.AppendWithTime("Ctrl");
    } else if (key == VK_LMENU or key == VK_RMENU) {
      st_.pressed[kAlt] = false;
      if (not st_.pressed_with_key[kAlt]) flog_.AppendWithTime("Alt");
    } else if (key == VK_LSHIFT or key == VK_RSHIFT) {  // Shift
      st_.pressed[kShift] = false;
      if (not st_.pressed_with_key[kShift]) flog_.AppendWithTime("Shift");
    } else if (key == VK_LWIN or key == VK_RWIN) {
      st_.pressed[kWin] = false;
      if (not st_.pressed_with_key[kWin]) flog_.AppendWithTime("Win");
    }
  }
}
