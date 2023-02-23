#include <windows.h>

#include <iostream>

int main() {
  while (true) {
    if (GetAsyncKeyState('S') & 0x8000 && GetAsyncKeyState(VK_SHIFT) & 0x8000 &&
        GetAsyncKeyState(VK_CONTROL) & 0x8000) {
      std::cout << "Ctrl + Shift + S was pressed" << std::endl;
      Sleep(
          500);  // プログラムがショートカットキーを一度だけ認識するように遅延を入れる
    }
  }
  return 0;
}
