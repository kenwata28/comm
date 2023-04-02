#ifndef THREAD_DATA_H_
#define THREAD_DATA_H_

#include <memory>

#include "IconDisplayer.h"
#include "RunningLevel.h"

//
//
// Thread 間で共有するデータ
//
//
class ThreadData {
 public:
  ThreadData() {}
  void Init(HWND hwnd) {
    idis = new IconDisplayer(hwnd);
    level = new RunningLevel(hwnd);
  }
  //  std::unique_ptr<IconDisplayer> idis;
  //  std::unique_ptr<RunningLevel> level;
  IconDisplayer* idis;
  RunningLevel* level;

 private:
};

#endif  // THREAD_DATA_H_