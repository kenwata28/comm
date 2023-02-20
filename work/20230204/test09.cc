#include <Windows.h>

#include <iostream>
#include <unordered_map>

// ショートカットキーを表す構造体
struct ShortcutKey {
  bool ctrl;
  bool alt;
  bool shift;
  int vk;
};

// ハッシュ関数
struct ShortcutKeyHash {
  std::size_t operator()(const ShortcutKey& key) const {
    std::size_t hash = 0;
    if (key.ctrl) {
      hash ^= 0x1;
    }
    if (key.alt) {
      hash ^= 0x2;
    }
    if (key.shift) {
      hash ^= 0x4;
    }
    hash ^= key.vk;
    return hash;
  }
};

// ホットキー処理関数
void handleHotkey(ShortcutKey key) {
  // ショートカットキーが押された時の処理をここに書く
  std::cout << "Shortcut key pressed: ";
  if (key.ctrl) {
    std::cout << "Ctrl + ";
  }
  if (key.alt) {
    std::cout << "Alt + ";
  }
  if (key.shift) {
    std::cout << "Shift + ";
  }
  std::cout << key.vk << std::endl;
}

int main() {
  // ショートカットキーと処理関数のマップ
  std::unordered_map<ShortcutKey, std::function<void()>, ShortcutKeyHash>
      hotkeys;

  // ショートカットキーと処理関数のマップにショートカットキーを追加する
  hotkeys[{true, false, false, 'A'}] = []() {
    handleHotkey({true, false, false, 'A'});
  };
  hotkeys[{false, true, false, 'B'}] = []() {
    handleHotkey({false, true, false, 'B'});
  };
  hotkeys[{true, true, false, 'C'}] = []() {
    handleHotkey({true, true, false, 'C'});
  };
  hotkeys[{true, false, true, VK_SPACE}] = []() {
    handleHotkey({true, false, true, VK_SPACE});
  };
  hotkeys[{false, true, true, VK_F1}] = []() {
    handleHotkey({false, true, true, VK_F1});
  };
  hotkeys[{true, true, true, VK_ESCAPE}] = []() {
    handleHotkey({true, true, true, VK_ESCAPE});
  };

  // ホットキーを登録する
  for (auto& [key, func] : hotkeys) {
    // MOD_NOREPEAT を指定することで、連打による複数回のイベントを回避する
    RegisterHotKey(nullptr, reinterpret_cast<int>(&key),
                   (key.ctrl ? MOD_CONTROL : 0) | (key.alt ? MOD_ALT : 0) |
                       (key.shift ? MOD_SHIFT : 0) | MOD_NOREPEAT,
                   key.vk);
