#include "FileLogger.h"

FileLogger* FileLogger::GetInstance() {
  if (g_file_logger == nullptr) {
    g_file_logger = new FileLogger();
    g_file_logger->SetFileName("level");
  }
  return g_file_logger;
}

void FileLogger::SetFileName(const char* dirname = ".") {
  // make name of file :"level\\230401.log"
  std::time_t time = std::time(nullptr);
  std::tm* now = std::localtime(&time);
  char t[kMaxSizeOfLine];
  std::strftime(t, sizeof(t), "%y%m%d.log", now);
  char filename[kMaxSizeOfFilePath];
  std::snprintf(filename, sizeof(filename), "%s\\%s", dirname, t);

  // check open file with the filename
  std::FILE* fp = std::fopen(filename, "w");
  if (fp == nullptr) {
    char cmt[MAX_PATH];
    std::snprintf(cmt, sizeof(cmt), "Can't find log file : %s", filename);
    ::OutputDebugStringA(cmt);
    exit(1);
  }
  std::fclose(fp);

  // set the filename as a member
  filename_ = filename;
}

void FileLogger::AppendWithTime(const char* txt) {
  std::time_t time = std::time(nullptr);
  std::tm* now = std::localtime(&time);
  char header[kMaxSizeOfLine];
  std::strftime(header, sizeof(header), "%H:%M:%S : ", now);
  char t[kMaxSizeOfLine];
  std::snprintf(t, sizeof(t), "%s%s", header, txt);
  Append(t);
}

void FileLogger::Append(const char* txt) {
  std::FILE* fp = std::fopen(filename_.c_str(), "a");
  std::fputs(txt, fp);
  std::fputs("\n", fp);
  std::fclose(fp);
}

FileLogger* FileLogger::g_file_logger = nullptr;
