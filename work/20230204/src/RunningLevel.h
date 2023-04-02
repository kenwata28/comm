#ifndef RUNNING_LEVEL_H_
#define RUNNING_LEVEL_H_

#include <windows.h>
const int kLevelMax = 10;
const int kLevelMin = 0;

class RunningLevel {
  // enum {
  // };

 public:
  RunningLevel() : level_{0} {}
  RunningLevel(HWND hwnd) : level_{0} {
    // MessageBox(hwnd, L"open runnning level", L"running level", 0);
  }
  // getter
  int Level() const { return level_; }

  /// @brief 現在より高い level なら、その level になる。
  inline void PaceUpTo(int level);
  inline void PaceDown();

 private:
  int level_;
};

inline void RunningLevel::PaceUpTo(int level) {
  if (level > level_) {
    level_ = level;
  }
}

inline void RunningLevel::PaceDown() {
  // いつ Interval() が呼ばれるかわからないので、まず if
  if (level_ - 1 < kLevelMin) {
    level_ = kLevelMin;
  } else {
    level_--;
  }
}

#endif  // RUNNING_LEVLE_H_
