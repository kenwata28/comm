#ifndef FILE_LOGGER_H_
#define FILE_LOGGER_H_

#include <windows.h>

#include <cstdio>
#include <ctime>
class FileLogger {
 public:
  enum {
    kMaxSizeOfFilePath = 256,
    kMaxSizeOfLine = 256  // one line !
  };

 public:
  FileLogger() {}
  FileLogger(const char* dirname) { SetFileName(dirname); }

  void Append(const char* txt);
  void AppendWithTime(const char* txt);

 private:
  void SetFileName(const char* dirname);

 private:
  char filename_[kMaxSizeOfFilePath];
};

#endif  // FILE_LOGGER_H_
