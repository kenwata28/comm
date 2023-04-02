// #ifndef TIMER_FOR_PACEDOWN_H_
// #define TIMER_FOR_PACEDOWN_H_

// #include "RunningLevel.h"
// #include "windows.h"

// namespace timer_for_pacedown {
// RunningLevel* level;
// IconDisplayer* icon_displayer;

// inline void Init(RunningLevel* lv, IconDisplayer* id) {
//   level = lv;
//   icon_displayer = id;
// }

// inline void PaseDown() {
//   level->PaceDown();

//   wchar_t txt[100];
//   wsprintf(txt, L"interval : %d, level : %d", level->TimeInterval(),
//            level->Level());
//   icon_displayer->SetCmt(std::wstring(txt));
// }

// };  // namespace timer_for_pacedown

// #endif
