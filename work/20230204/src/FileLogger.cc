#include "FileLogger.h"

void FileLogger::SetFileName(const char* dirname = ".") {
  std::time_t time = std::time(nullptr);
  std::tm* now = std::localtime(&time);
  char t[kMaxSizeOfLine];
  std::strftime(t, sizeof(t), "%y%m%d.log", now);
  sprintf(filename_, "%s\\%s", dirname, t);

  std::FILE* fp = std::fopen(filename_, "w");
  if (fp == nullptr) {
    MessageBoxA(NULL, filename_, "Can't find log file", 0);
    exit(1);
  }
  std::fputs(filename_, fp);
  std::fputs("\n", fp);
  std::fclose(fp);
}

void FileLogger::AppendWithTime(const char* txt) {
  std::time_t time = std::time(nullptr);
  std::tm* now = std::localtime(&time);
  char header[kMaxSizeOfLine];

  std::strftime(header, sizeof(header), "%H:%M:%S : ", now);
  char t[kMaxSizeOfLine];
  std::sprintf(t, "%s%s", header, txt);
  Append(t);
}

void FileLogger::Append(const char* txt) {
  std::FILE* fp = std::fopen(filename_, "a");
  std::fputs(txt, fp);
  std::fputs("\n", fp);
  std::fclose(fp);
}
