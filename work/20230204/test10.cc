#include <Windows.h>

#include <iostream>
#include <vector>

struct Shortcut {
  bool ctrl;
  bool alt;
  bool shift;
  bool win;
  int key;
};

std::vector<Shortcut> shortcuts;

void addShortcut(bool ctrl, bool alt, bool shift, bool win, int key) {
  Shortcut shortcut = {ctrl, alt, shift, win, key};
  shortcuts.push_back(shortcut);
}

bool checkShortcut(const Shortcut& shortcut) {
  return (GetKeyState(VK_CONTROL) & 0x8000 ? true : false) == shortcut.ctrl &&
         (GetKeyState(VK_MENU) & 0x8000 ? true : false) == shortcut.alt &&
         (GetKeyState(VK_SHIFT) & 0x8000 ? true : false) == shortcut.shift &&
         (GetKeyState(VK_LWIN) & 0x8000 || GetKeyState(VK_RWIN) & 0x8000
              ? true
              : false) == shortcut.win &&
         (GetAsyncKeyState(shortcut.key) & 0x8000 ? true : false);
}

void handleShortcut(const Shortcut& shortcut) {
  std::cout << "Shortcut detected: ";
  if (shortcut.ctrl) std::cout << "Ctrl+";
  if (shortcut.alt) std::cout << "Alt+";
  if (shortcut.shift) std::cout << "Shift+";
  if (shortcut.win) std::cout << "Win+";
  std::cout << char(shortcut.key) << std::endl;
}

int main() {
  // Add some sample shortcuts
  addShortcut(true, false, false, false, 'A');
  addShortcut(false, true, false, false, 'B');
  addShortcut(true, true, false, false, 'C');
  addShortcut(false, false, true, false, 'D');
  addShortcut(false, false, false, true, 'E');
  addShortcut(true, false, false, true, 'F');
  addShortcut(false, true, false, true, 'G');
  addShortcut(true, true, true, false, 'H');
  addShortcut(false, false, true, true, 'I');
  addShortcut(true, false, true, true, 'J');
  addShortcut(true, true, true, true, 'K');

  // Enter the message loop
  MSG msg = {0};
  while (GetMessage(&msg, NULL, 0, 0)) {
    if (msg.message == WM_HOTKEY) {
      int id = (int)msg.wParam;
      handleShortcut(shortcuts[id]);
    }
  }

  return 0;
}
