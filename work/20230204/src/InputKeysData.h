#ifndef INPUT_KEYS_DATA_H_
#define INPUT_KEYS_DATA_H_

#include <windows.h>

#include <array>

#include "RunningLevel.h"

class InputKeysData {
  enum { kMaxIndex = 30 };

 public:
  InputKeysData() { Clear(); }
  int Level() {
    int n = NumOfValidTyping();
    constexpr int kUpperRangeLevel[kLevelMax]  // ここで level を決定する。
        = {4, 6, 7, 8, 10, 12, 14, 16, 20, 24};
    for (int lv = 0; lv < kLevelMax; lv++) {
      if (n <= kUpperRangeLevel[lv]) return lv;
    }
    return kLevelMax;
  }

  void Clear() {
    index = 0;
    for (auto& key : keys) key = 0;
  }

  std::vector<int> DeletedKeys(int idx) {
    std::vector<int> dest(keys, keys + idx);
    return dest;
  }

  int IndexOfBackSpace() const {
    for (int i = 0; i < index; i++) {
      if (keys[i] == VK_BACK) return i;
    }
    return -1;
  }

  void SetKey(DWORD key) {
    keys[index] = key;
    index++;
  }

 private:
  int NumOfValidTyping() const {
    int ans = 0;
    for (int i = 2; i < index; i++) {  // NOTE : max index
      const int& k0 = keys[i - 2];
      const int& k1 = keys[i - 1];
      const int& k2 = keys[i];
      if (k0 != k1 or k1 != k2) ans++;
    }
    return ans;
  }

  DWORD keys[kMaxIndex];
  int index;
};

class InputKeysDatas {
 public:
  InputKeysDatas() : index_{0} {}

  void ToggleData() { index_ = (index_ + 1) % 2; }
  InputKeysData* Data() { return &(datas_[index_]); }

 private:
  int index_;
  std::array<InputKeysData, 2> datas_;
};

#endif  // INPUT_KEYS_DATA_H_
