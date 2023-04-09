// #ifndef FILE_LOGGER_H_
// #define FILE_LOGGER_H_
#pragma once

#include <windows.h>

#include <cstdio>
#include <ctime>
#include <string>

class FileLogger {
 public:
  enum {
    kMaxSizeOfFilePath = 256,
    kMaxSizeOfLine = 256  // one line !
  };

 public:
  static FileLogger* GetInstance();

  // ファイルにtxtを追記する.
  void Append(const char* txt);

  // ファイルに時刻とともにtxtを追記する。
  void AppendWithTime(const char* txt);

 private:
  void SetFileName(const char* dirname);

 private:
  FileLogger() {}
  static FileLogger* g_file_logger;
  std::string filename_;
};

// #endif  // FILE_LOGGER_H_
