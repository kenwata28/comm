#ifndef LOG_KEY_INPUT_H_
#define LOG_KEY_INPUT_H_

#include <FileLogger.h>
#include <Windows.h>

#include <array>
#include <iostream>
#include <string>
class KeyInputLogger {
 public:
  KeyInputLogger() : flog_{FileLogger(".")} {}

  void LogKeyInput(const WPARAM w_par, const DWORD key);

 private:
  //
  //  修飾子 を取り扱うために KindOfModifiers と StatusOfModifier を用意
  //
  enum KindOfModifiers { kAlt = 0, kWin, kCtrl, kShift, kNumOfModifiers };
  class StatusOfModifier {
   public:
    StatusOfModifier() {
      for (auto& p : pressed) p = false;
      for (auto& p : pressed_with_key) p = false;
    }
    std::array<bool, kNumOfModifiers> pressed;
    // This is for the case of only modifier key input
    std::array<bool, kNumOfModifiers> pressed_with_key;
  };

 private:
  StatusOfModifier st_;
  FileLogger flog_;

  std::string StringOfKeyAppendedModifiers(const StatusOfModifier& st,
                                           const DWORD key) const;
};
#endif  // LOG_KEY_INPUT__